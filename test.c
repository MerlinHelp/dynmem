#include <stdio.h>
#include <stdlib.h>

#include "global.h"
void *base = NULL;

int main(void)
{
    size_t number = 10;
    size_t size = 8;
    size_t s8 = align8(number * size) << 3;

    size_t *arr = calloc(10, sizeof(*arr));
    size_t *i = arr;
    for (i; i < i + 8; ++i) {
        printf("%p ", &i);
    }


    free(arr);

    return EXIT_SUCCESS;
}
