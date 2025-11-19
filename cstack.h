#ifndef CSTACK_H
#define CSTACK_H
#include "____internal__cvector.h"
#define bring_cstack(type)\
    ___internal_bring_cvector(type);\
    typedef struct cstack_##type\
    {\
        __internal_cvector(type) vec;\
    }cstack_##type;
#define cstack_push(cstack,type,value) __internal_cvec_push((cstack).vec,type,value)
#define cstack_pop(cstack,type) __internal_cvec_pop(((cstack).vec),type)
#define cstack_peek(cstack) __internal_cvec_last(((cstack).vec))
#define cstack_empty(cstack) __internal_cvec_size(((cstack).vec))?0:1
#define cstack_clear(cstack,type) __internal_cvec_clear(((cstack).vec),type)
#define cstack_size(cstack) __internal_cvec_size((cstack).vec)
#define cstack_pop_many(cstack, type, num) __internal_cvec_erase(((cstack).vec),type,(__internal_cvec_size(((cstack).vec)) - (num)),(__internal_cvec_size(((cstack).vec)) - 1))
#define cstack_print(cstack,fmt) __internal_cvec_print((cstack).vec,fmt)
#define cstack(type) cstack_##type 
#define new_cstack(type) (cstack_##type){.vec=__internal_new_cvector(type)}
#endif 
