#ifndef REALLOC_H
#define REALLOC_H

#include "global.h"

#ifndef REALLOC_FUNCS
#define REALLOC_FUNCS

void copy_block(t_block, t_block);
void *realloc(void*, size_t);

#endif

#endif
