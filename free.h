#ifndef FREE_H
#define FREE_H

#ifndef INCLUDE_GLOBAL_H
#define INCLUDE_GLOBAL_H

#include "global.h"

#endif

#ifndef FREE_FUNC
#define FREE_FUNC

t_block fusion(t_block);
t_block get_block(void*);
int valid_address(void*);
void free(void*);

#endif

#endif
