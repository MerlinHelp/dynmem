#include <sys/types.h>
#include <unistd.h>

#include "global.h"
#include "malloc.h"

void *calloc(size_t number, size_t size)
{
    char *new;
    size_t uprlmt, i;
    new = malloc(number * size);
    if (new) {
        uprlmt = align8(number * size);

        for (i = 0; i < uprlmt; i += size) {
            new[i] = 0;
        }
    }

    return (new);
}
