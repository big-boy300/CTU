#include "ec.h"
#include "ptab.h"
#include "string.h"

typedef enum {
    sys_print = 1,
    sys_sum = 2,
    sys_break = 3,
    sys_thr_create = 4,
    sys_thr_yield = 5,
} Syscall_numbers;

mword prev_adress = 0;

void Ec::syscall_handler(uint8 a) {
    // Get access to registers stored during entering the system - see
    // entry_sysenter in entry.S
    Sys_regs* r = current->sys_regs();
    Syscall_numbers number = static_cast<Syscall_numbers>(a);

    switch (number) {
        case sys_print: {
            char* data = reinterpret_cast<char*>(r->esi);
            unsigned len = r->edi;
            for (unsigned i = 0; i < len; i++)
                printf("%c", data[i]);
            break;
        }
        case sys_sum: {
            // Naprosto nepotřebné systémové volání na sečtení dvou čísel
            int first_number = r->esi;
            int second_number = r->edi;
            r->eax = first_number + second_number;
            break;
        }
        case sys_break: {
            //my implementation of sys_break - HW10
            if (prev_adress == 0) {
                prev_adress = Ec::break_min;
            }

            mword current_break = Ec::break_current;
            mword new_address = r->esi;

            if (new_address == 0) {
                r->eax = prev_adress;
                break;
            }

            if (new_address > 0xBFFFF000 || new_address < Ec::break_min) {
                r->eax = 0;
                break;
            }

            //find offset and fill it with 0
            mword offset = prev_adress % PAGE_SIZE;
            if(offset != 0){
                void* page = Kalloc::phys2virt(Ptab::get_mapping(current_break - PAGE_SIZE) & ~PAGE_MASK);
                memset(reinterpret_cast<void*>(reinterpret_cast<mword>(page) + offset), 0, PAGE_SIZE - offset);
            }

            if (new_address > current_break) {
                //1. Compute how many pages should be allocated
                mword bytes_num = new_address - current_break;
                mword pages_num;

                if (bytes_num % PAGE_SIZE == 0) {
                    pages_num = bytes_num / PAGE_SIZE;
                } else {
                    pages_num = (bytes_num / PAGE_SIZE) + 1;
                }
                
                //2. Allocate and map pages - one by one
                for (mword i = 0; i < pages_num; ++i) {
                    void* page = Kalloc::allocator.alloc_page(1, Kalloc::FILL_0);
                    if (page == NULL) {
                        printf("PAGE ALLOCATION FAILURE!\n");
                        //delete mapping that was already done, deallocate pages which were allocated and decrement current_break
                        for (mword j = 0; j < i; ++j) {
                            current_break -= PAGE_SIZE;
                            Ptab::insert_mapping(current_break, Ptab::get_mapping(current_break), 0);
                            void* page_to_free = Kalloc::phys2virt(Ptab::get_mapping(current_break) & ~PAGE_MASK);
                            Kalloc::allocator.free_page(page_to_free);
                        }
                        r->eax = 0;
                        break;
                    }

                    //3. Get physical address of allocated page
                    mword phys_addr = Kalloc::virt2phys(page);

                    //4. Map that page
                    if (!Ptab::insert_mapping(current_break, phys_addr, Ptab::PRESENT | Ptab::RW | Ptab::USER)) {
                        printf("MAPPING FAILURE!\n");
                        //delete mapping that was already done, deallocate pages which were allocated and decrement current_break
                        for (mword j = 0; j < i; ++j) {
                            current_break -= PAGE_SIZE;
                            Ptab::insert_mapping(current_break, Ptab::get_mapping(current_break), 0);
                            void* page_to_free = Kalloc::phys2virt(Ptab::get_mapping(current_break) & ~PAGE_MASK);
                            Kalloc::allocator.free_page(page_to_free);
                        }
                        r->eax = 0;
                        break;
                    }

                    current_break += PAGE_SIZE;
                }

            } else if (new_address < current_break) {
                //1. Compute how many pages should be deallocated
                mword bytes_num = current_break - new_address;

                mword pages_num = bytes_num / PAGE_SIZE;

                for (mword i = 0; i < pages_num; ++i) {
                    current_break -= PAGE_SIZE;

                    //2. Delete mapping
                    if (!Ptab::insert_mapping(current_break, Ptab::get_mapping(current_break), 0)) {
                        //increment current break
                        for (mword j = 0; j < i; ++j) {
                            current_break += PAGE_SIZE;
                        }
                        r->eax = 0;
                        break;
                    }

                    //3. Deallocate pages
                    void* page_to_free = Kalloc::phys2virt(Ptab::get_mapping(current_break) & ~PAGE_MASK);
                    Kalloc::allocator.free_page(page_to_free);
                }
            }
            
            if (!r->eax) {
                break;
            }
            
            if (new_address % PAGE_SIZE == 0) {
                Ec::break_current = new_address;
            } else {
                Ec::break_current = new_address - (new_address % PAGE_SIZE) + PAGE_SIZE;
            }
            
            r->eax = prev_adress;
            prev_adress = new_address;
            break;
        }
        default:
            printf("unknown syscall %d\n", number);
            break;
    };

    ret_user_sysexit();
}
