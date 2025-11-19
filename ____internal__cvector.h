#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#define ___internal_bring_cvector(type) \
    typedef struct __internal_cvector_##type \
    { \
        type* data; \
        size_t size; \
        size_t capacity;\
    }__internal_cvector_##type; \
    static inline void __internal_cvec_##type##_push(__internal_cvector_##type *v,type value)\
    {\
        if(v->size==v->capacity)\
        {\
            v->capacity=v->capacity?v->capacity*2:1;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        v->data[v->size++]=value;\
    }\
    static inline type __internal_cvec_##type##_pop(__internal_cvector_##type *v)\
    {\
        return v->data[--v->size];\
    }\
    static inline void __internal_cvec_##type##_remove(__internal_cvector_##type *v,int idx)\
    {\
        for(size_t _i=idx;_i<(v->size)-1;_i++)\
        {\
            v->data[_i]=v->data[_i+1];\
        }\
        v->size--;\
    }\
    static inline void __internal_cvec_##type##_insert(__internal_cvector_##type *v,type value,int idx,int copies)\
    {\
        if((((v->size)+copies)>=v->capacity))\
        {\
            size_t needed=v->size+copies;\
            if(v->capacity)\
            {\
                v->capacity=needed+1;\
            }\
            else\
            {\
                while(v->capacity<=needed)\
                {\
                    v->capacity=v->capacity*2;\
                }\
            }\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        for(int _i=v->size-1;_i>=idx;_i--)\
        {\
            v->data[_i+copies]=v->data[_i];\
        }\
        for(int _i=0;_i<copies;_i++)\
        {\
            v->data[idx+_i]=value;\
        }\
        v->size+=copies;\
    }\
    static inline void __internal_cvec_##type##_erase(__internal_cvector_##type *v, int start, int end)\
    {\
        size_t count = (end - start) + 1;\
        for (size_t i = end + 1; i < v->size; i++)\
        {\
            v->data[i - count] = v->data[i];\
        }\
        v->size -= count;\
    }\
    static inline void __internal_cvec_##type##_clear(__internal_cvector_##type *v)\
    {\
        free(v->data);\
        v->data=NULL;\
        v->size=0;\
        v->capacity=0;\
    }\
    static inline void __internal_cvec_##type##_stf(__internal_cvector_##type *v)\
    {\
        if(v->size<v->capacity)\
        {\
            v->data=realloc(v->data,v->size*sizeof(type));\
            v->capacity=v->size;\
        }\
    }\
    static inline size_t __internal__cvec_##type##_find(__internal_cvector_##type *v,type value)\
    {\
        for(size_t i=0;i<v->size;i++)\
        {\
            if(value==v->data[i])\
            {\
                return i;\
            }\
        }\
        return (size_t)-1;\
    }\
    static inline void __internal_cvec_##type##_resize(__internal_cvector_##type *v,size_t value)\
    {\
        if(value>v->capacity)\
        {\
            v->capacity=value;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        v->size=value;\
    }\
    static inline void __internal_cvec_##type##_reserve(__internal_cvector_##type *v,size_t value)\
    {\
        if(value>v->capacity)\
        {\
            v->capacity=value;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
    }
    
#define __internal_iterate_byref(v,_i_te__rat_or,type)\
    for(size_t __io___=0;__io___<v.size;__io___++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type* _i_te__rat_or=&(v.data[__io___]); __o_n_c_e_;__o_n_c_e_=0)

#define __internal_iterate_byval(v,i_t__e__r_a_t_or,type)\
    for(size_t __io___=0;__io___<v.size;__io___++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type i_t__e__r_a_t_or=(v.data[__io___]);__o_n_c_e_;__o_n_c_e_=0)

#define __internal_cvec_print(v,fmt)\
    do\
    {\
        if(v.size==0)\
        {\
            printf("[ ]\n");\
        }\
        else\
        {\
            printf("[");\
            for(int i=0;i<v.size;i++)\
            {\
                printf(fmt,v.data[i]);\
                if(i<v.size-1)\
                {\
                    printf(", ");\
                }\
            }\
            printf("]\n");\
        }\
    }while(0);

#define __internal_cvec_push(cvector,type,value) __internal_cvec_##type##_push(&(cvector),value)
#define __internal_cvec_pop(cvector,type) __internal_cvec_##type##_pop(&(cvector))
#define __internal_cvec_remove(cvector,type,idx) __internal_cvec_##type##_remove(&(cvector),idx)
#define __internal_cvec_erase(cvector,type,start,end) __internal_cvec_##type##_erase(&(cvector),start,end)
#define __internal_cvec_clear(cvector,type) __internal_cvec_##type##_clear(&(cvector))
#define __internal_cvec_find(cvector,type,value) __internal_cvec_##type##_find(&(cvector),value)
#define __internal_cvec_insert(cvector,type,value,idx,copies) __internal_cvec_##type##_insert(&(cvector),value,idx,copies)
#define __internal_cvec_resize(cvector,type,value) __internal_cvec_##type##_resize(&(cvector),value)
#define __internal_cvec_reserve(cvector,type,value) __internal_cvec_##type##_reserve(&(cvector),value)
#define __internal_cvec_shrink_to_fit(cvector,type) __internal_cvec_##type##_stf(&(cvector))
#define __internal_cvec_get(cvector,idx) (cvector).data[idx]
#define __internal_cvec_last(cvector) (cvector).data[(cvector).size-1]
#define __internal_cvec_first(cvector) (cvector).data[0]
#define __internal_cvec_size(cvector) (cvector).size
#define __internal_cvec_capacity(cvector) (cvector).capacity
#define __internal_new_cvector(type) (__internal_cvector_##type){.data=NULL,.size=0,.capacity=0} 
#define __internal_cvector(type) __internal_cvector_##type 
#endif