#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr = malloc(sizeof(*arr) * 10);
    *(arr + 0) = 10;
    printf("%d", arr[0]);
    printf("%d", arr[11]);
    free(arr);
    return 0;
}
