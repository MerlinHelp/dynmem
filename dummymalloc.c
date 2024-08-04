// Dummy malloc (you can't free or realloc so memory can't be returned)
#include <sys/types.h>
#include <unistd.h>

void* malloc(size_t size)
{
    void* p;
    p = sbrk(0);

    if (sbrk(size) == (void*)-1) {
        return NULL;
    }

    return p;
}
