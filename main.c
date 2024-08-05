#ifndef FEATURE_TEST_MACROS
#define FEATURE_TEST_MACROS

#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#endif

#include <stdio.h>
#include <unistd.h>

#include "calloc.h"
#include "free.h"
#include "global.h"
#include "malloc.h"
#include "realloc.h"

#define NUM_ELEMS 4

int dump_long_arr(long *p, int size)
{
    long *ptr = p;
    

    for (int i = 0; i < size; ++i) {
        ssize_t nbytes = snprintf(NULL, 0, "%ld", *ptr) + 1;
        char buf[nbytes];
        snprintf(buf, nbytes, "%ld", *ptr);
        ++ptr;
        if ((write(STDOUT_FILENO, buf, nbytes)) != nbytes) {
            free(p);
            return -1;
        }
    }
    if ((write(STDOUT_FILENO, "\n", 1)) != 1) {
        return -1;
    }

    return 0;
}

int main(void)
{
    // long *arr = calloc(NUM_ELEMS, sizeof(*arr));
    long *arr;

    if ((arr = calloc(NUM_ELEMS, sizeof(*arr))) == NULL) {
        write(STDOUT_FILENO, "Fa", 2);
        return -1;
    }

    size_t itr;

    for (itr = 0; itr < NUM_ELEMS; ++itr) {
        *(arr + itr) = (int) itr;
    }

    dump_long_arr(arr, NUM_ELEMS);

    long *arr2;

    if ((arr2 = malloc(NUM_ELEMS * sizeof(*arr2))) == NULL) {
        write(STDOUT_FILENO, "Fa", 2);
        free(arr);
        return -1;
    }

    for (itr = 0; itr < NUM_ELEMS; ++itr) {
        *(arr + itr) = ((int) itr) * 2;
    }

    dump_long_arr(arr, NUM_ELEMS);

    if ((arr2 = realloc(arr, (NUM_ELEMS + 1) * sizeof(*arr2))) == NULL) {
        free(arr);
        return -1;
    }

    dump_long_arr(arr, NUM_ELEMS);
    dump_long_arr(arr2, NUM_ELEMS + 1);

    *(arr2 + NUM_ELEMS) = 1;
    
    dump_long_arr(arr2, NUM_ELEMS + 1);

    free(arr);
    free(arr2);

    return 0;
}
