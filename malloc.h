#ifndef MALLOC_H
#define MALLOC_H

#include "global.h"

#ifndef MALLOC_FUNCS
#define MALLOC_FUNCS

t_block find_block(t_block*, size_t);
t_block extend_heap(t_block, size_t);
void split_block(t_block, size_t);
void* malloc(size_t);

#endif

#endif
