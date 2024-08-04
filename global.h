#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef GLOBAL_VARS
#define GLOBAL_VARS

extern void *base;

#endif

#ifndef GLOBAL_STRUCTS
#define GLOBAL_STRUCTS

typedef struct s_block *t_block;
struct s_block {
    size_t size;
    t_block next;
    t_block prev; 
    long free;
    void *ptr;
    /* A pointer to allocated block */
    char data[1];
};

#endif

#ifndef GLOBAL_MACROS
#define GLOBAL_MACROS

#define align8(x) ((((((x)-1))>>3)<<3)+8)
#define BLOCK_SIZE 40

#endif

#endif
