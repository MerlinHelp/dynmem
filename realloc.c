#include <sys/types.h>
#include <unistd.h>

#include "free.h"
#include "global.h"
#include "malloc.h"
#include "realloc.h"

void copy_block(t_block src, t_block dest)
{
    char *sdata, *ddata;
    size_t i;
    sdata = src->data;
    ddata = dest->data;

    for (i = 0; i < src->size; ++i) {
        *(ddata + i) = sdata[i];
    }
}

void *realloc(void *oldp, size_t size)
{
    size_t s;
    t_block b, new;
    void *newp;

    if (!oldp) {
        return (malloc(size));
    }

    if (valid_address(oldp)) {
        b = get_block(oldp);
        s = align8(size);

        if (b->size >= s) {
            if (b->size - s >= (BLOCK_SIZE + 8)) {
                split_block(b, s);
            }
        } else {
            if ((b->next && b->next->free)
                         && (BLOCK_SIZE + b->size + b->next->size) >= s) {
                fusion(b);
                if (b->size - s >= (BLOCK_SIZE + 8)) {
                    split_block(b, s);
                }
            } else {
                newp = malloc(s);

                if (!oldp || !valid_address(newp)) {
                    return (NULL);
                }

                new = get_block(newp);

                copy_block(b, new);

                /* Since oldp is not related to newp, we can free oldp */
                free(oldp);

                return (newp);
            }
        }
        return (oldp);
    }
    return (NULL);
}
