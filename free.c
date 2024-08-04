#include <sys/types.h>
#include <unistd.h>

#include "global.h"

t_block fusion(t_block b)
{
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next) {
            b->next->prev = b;
        }
    }

    return (b);
}

t_block get_block(void *p)
{
    char *tmp;
    tmp = p;
    
    /* Equiv to (p = (tmp = (tmp - BLOCK_SIZE))) */
    /* Returns tmp - BLOCK_SIZE aka p - BLOCK_SIZE, since rtrn value of
     * expressions is R_VALUE */
    return (p = tmp -= BLOCK_SIZE);
}

/* Check address if valid for free */
int valid_address(void *p)
{
    /* If any malloc has been made */
    if (base) {
        /* if pointer to check is after beginning of heap but before the
         * last break and no man's land */
         
        if (p > base && p < sbrk(0)) {
            return (p == (get_block(p)->ptr));
        }
    }

    return (0);
}

void free(void *p)
{
    t_block b;

    /* If p is valid ptr to data[1] field, get the block and start freeing */
    if (valid_address(p)) {
        b = get_block(p);
        b->free = 1;

        /* If prev exists and is free, fuse it with current b */
        if (b->prev && b->prev->free) {
            b = fusion(b->prev);
        }

        /* If next exists, call fusion function as it checks for next->free */
        /* Else, check if prev exists, and if does, unlink current block from
         * double linked list, if it doesnt then we reached beginning of heap,
         * so set base to NULL; */
        if (b->next) {
            b = fusion(b);
        } else {
            if (b->prev) {
                b->prev->next = NULL;
            } else {
                base = NULL;
            }

            /* Move break to address pointed at by b. */
            brk(b);
        }
    }
}
