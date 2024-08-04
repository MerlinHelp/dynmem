#include <sys/types.h>
#include <unistd.h>

#include "global.h"

void *base = NULL;

t_block find_block(t_block *last, size_t size)
{
    t_block b = base;
    while (b && !(b->free && b->size >= size)) {
        /*Although *last = b does not affect whether you find the correct
          t_block that is free and has enough space, it helps when you are
          going to expand the heap and you dereference the pointer to the last
          t_block and write to it directly with the one before the free one.*/
        *last = b;
        b = b->next;
    }
    
    return (b);
}

t_block extend_heap(t_block last, size_t sz)
{
    t_block b;
    b = sbrk(0);

    if (sbrk(BLOCK_SIZE + sz) == (void*)-1) {
        return (NULL);
    }
    b->size = sz;
    b->next = NULL;
    if (last) {
        last->next = b;
    }
    b->free = 0;
    return (b);
}

void split_block(t_block b, size_t s)
{
    t_block new;
    new = (t_block) (b->data + s);
    new->size = b->size - s - BLOCK_SIZE;
    new->next = b->next;
    new->free = 1;
    b->size = s;
    b->next = new;
}

void *malloc(size_t size) {
    t_block b, last;
    size_t s;
    s = align8(size);

    if (base) {
        /* First find a block */
        last = base;
        b = find_block(&last, s);
        
        if (b) {
            if ((b->size - s) >= (BLOCK_SIZE + 8)) {
                split_block(b, s);
            }

            b->free = 0;
        } else {
            /* No fitting block found, extend the heap */
            b = extend_heap(last, s);
            if (!b) {
                return (NULL);
            }
        }
    } else {
        b = extend_heap(NULL, s);
        if (!b) {
            return (NULL);
        }
        base = b;
    }

    b->ptr = b->data;
    return (b->data);
}
