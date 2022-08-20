#include "mem_alloc.h"

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define NULL ((void *)0)

/*
 * Logic and implementation inspired by https://arjunsreedharan.org/post/148675821737/write-a-simple-memory-allocator
 */

static inline void *nbrk(void *address);

#ifdef NOVA

/**********************************/
/* nbrk() implementation for NOVA */
/**********************************/

static inline unsigned syscall2(unsigned w0, unsigned w1) {
    asm volatile(
        "   mov %%esp, %%ecx    ;"
        "   mov $1f, %%edx      ;"
        "   sysenter            ;"
        "1:                     ;"
        : "+a"(w0)
        : "S"(w1)
        : "ecx", "edx", "memory");
    return w0;
}

static void *nbrk(void *address) {
    return (void *)syscall2(3, (unsigned)address);
}
#else

/***********************************/
/* nbrk() implementation for Linux */
/***********************************/

#include <unistd.h>

static void *nbrk(void *address) {
    void *current_brk = sbrk(0);
    if (address != NULL) {
        int ret = brk(address);
        if (ret == -1)
            return NULL;
    }
    return current_brk;
}

#endif

typedef struct header {
    unsigned long size;
    _Bool is_free;
    struct header *next;
} header_t;

header_t *head = NULL, *tail = NULL;

void join_free_blocks(unsigned long size);

// find free block and check if i can fit there block of required size
header_t *get_free_block(unsigned long size) {
    _Bool find_flag = FALSE;
    header_t *ret = NULL;
    header_t *cursor = head;
    while (cursor) {
        if (cursor->is_free && cursor->size >= size) {
            find_flag = TRUE;
            ret = cursor;
            break;
        }
        cursor = cursor->next;
    }

    if (find_flag == FALSE) {
        join_free_blocks(size);
        cursor = head;
        while (cursor) {
            if (cursor->is_free && cursor->size >= size) {
                ret = cursor;
                break;
            }
            cursor = cursor->next;
        }
    }

    return ret;
}

void *brk_min = NULL;

void *my_malloc(unsigned long size) {
    if (brk_min == NULL) {
        brk_min = nbrk(NULL);
    }

    if (size == 0) {
        return NULL;
    }

    header_t *header = get_free_block(size);
    if (header) {
        header->is_free = FALSE;
        return (void *)(header + 1);
    }

    void *cur_brk = nbrk(NULL);
    unsigned long alloc_size = sizeof(header_t) + size;
    void *new_block_size = (void *)((unsigned long)cur_brk + alloc_size);
    void *new_block = nbrk(new_block_size);
    if (new_block == NULL) {
        return NULL;
    }

    header = new_block;
    header->size = size;
    header->is_free = FALSE;
    header->next = NULL;

    if (head == NULL) {
        head = header;
    }

    if (tail) {
        tail->next = header;
    }

    tail = header;

    return (void *)(header + 1);
}

/*
 * Traverse LL, check if address of the current element in list is the same as address in parameters,
 * if true then make this block free.
 */
int my_free(void *address) {
    if (address == NULL) {
        return -1;
    }

    if (head == NULL) {
        return -2;
    }

    header_t *cursor = head;
    header_t *addr_to_free = (header_t *)address - 1;

    if (address >= brk_min) {
        while (cursor) {
            if (cursor == addr_to_free && cursor->is_free == FALSE) {
                cursor->is_free = TRUE;
                return 0;
            }
            cursor = cursor->next;
        }
    }

    return -3;
}

// join smaller neighbouring free blocks
void join_free_blocks(unsigned long size) {
    _Bool join_flag = FALSE;
    header_t *cursor = head;
    while (cursor) {
        if (cursor->size >= size && cursor->is_free) {
            break;
        }
        if (cursor->is_free && cursor->next && cursor->next->is_free) {
            cursor->size += cursor->next->size;
            cursor->next = cursor->next->next;
            join_flag = TRUE;
        }
        if (join_flag == TRUE) {
            cursor = head;
            join_flag = FALSE;
        } else {
            cursor = cursor->next;
        }
    }
}
