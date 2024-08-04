#include <stdio.h>

#include "global.h"
#include "malloc.h"

int main(void)
{
    char *p = malloc(2 * 4);
    size_t i, size, s4;
    size = 4;
    s4 = align8(2 * 4);
    for (i = 0; i < s4; i += size) {
        printf("%p ", &p[i]);
    }

    printf("%lu ", s4 / 4);
    printf("%i", (int) (&p[s4] - &p[0]));

    return 0;
}
