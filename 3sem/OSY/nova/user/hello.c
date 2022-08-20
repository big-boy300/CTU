#include "stdio.h"
#include "mem_alloc.h"
#include "string.h"

unsigned syscall2(unsigned w0, unsigned w1)
{
    asm volatile (
        "   mov %%esp, %%ecx    ;"
        "   mov $1f, %%edx      ;"
        "   sysenter            ;"
        "1:                     ;"
        : "+a" (w0) : "S" (w1) : "ecx", "edx", "memory");
    return w0;
}

void *nbrk(void *address)
{
    return (void*)syscall2(3, (unsigned)address);
}

int uninitialized_var;
int initialized_var = 42;

int main ()
{
    printf("Hello world!\n");

    // printf("Variables test: uninitialized_var=%d initialized_var=%d\n",
    //        uninitialized_var, initialized_var);

    // void *b = nbrk(0);
    // printf("current break: %p\n", b);
    // nbrk((void*)(10*0x1000));
    // b = nbrk(0);
    // printf("new break: %p\n", b);

    // int addr = 0x4001;
    // printf("NEW_ADDRESS: hex: %x dec: %d\n", addr, addr);
    // nbrk((void*)0x4001);

    // nbrk((void *) (0x0));
    // nbrk((void *) (0x4000));
    // nbrk((void *) (0x5000));
    // nbrk((void *) (0x4001));
    // nbrk((void *) (0x4005));
    // nbrk((void *) (0x6000));
    // nbrk((void *) (0x15000));
    
    nbrk((void*)0x1f222);
    nbrk((void*)0x2000000);

    // nbrk((void*)0xd000); 
    // nbrk((void*)0x1d000); 

    while (1) ;
}
