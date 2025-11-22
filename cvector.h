#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#define bring_cvector(type) \
    typedef struct cvector_##type \
    { \
        type* data; \
        size_t size; \
        size_t capacity;\
    }cvector_##type; \
    static inline void cvec_##type##_push(cvector_##type *v,type value)\
    {\
        if(v->size==v->capacity)\
        {\
            v->capacity=v->capacity?v->capacity*2:1;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        v->data[v->size++]=value;\
    }\
    static inline type cvec_##type##_pop(cvector_##type *v)\
    {\
        return v->data[--v->size];\
    }\
    static inline void cvec_##type##_remove(cvector_##type *v,int idx)\
    {\
        for(size_t _i=idx;_i<(v->size)-1;_i++)\
        {\
            v->data[_i]=v->data[_i+1];\
        }\
        v->size--;\
    }\
    static inline void cvec_##type##_insert(cvector_##type *v,type value,int idx,int copies)\
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
    static inline void cvec_##type##_erase(cvector_##type *v, int start, int end)\
    {\
        size_t count = (end - start) + 1;\
        for (size_t i = end + 1; i < v->size; i++)\
        {\
            v->data[i - count] = v->data[i];\
        }\
        v->size -= count;\
    }\
    static inline void cvec_##type##_clear(cvector_##type *v)\
    {\
        free(v->data);\
        v->data=NULL;\
        v->size=0;\
        v->capacity=0;\
    }\
    static inline void cvec_##type##_stf(cvector_##type *v)\
    {\
        if(v->size<v->capacity)\
        {\
            v->data=realloc(v->data,v->size*sizeof(type));\
            v->capacity=v->size;\
        }\
    }\
    static inline size_t cvec_##type##_find(cvector_##type *v,type value)\
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
    static inline void cvec_##type##_resize(cvector_##type *v,size_t value)\
    {\
        if(value>v->capacity)\
        {\
            v->capacity=value;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        v->size=value;\
    }\
    static inline void cvec_##type##_reserve(cvector_##type *v,size_t value)\
    {\
        if(value>v->capacity)\
        {\
            v->capacity=value;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
    }
    
#define iterate_byref(v,_i_te__rat_or,type)\
    for(size_t __io___=0;__io___<v.size;__io___++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type* _i_te__rat_or=&(v.data[__io___]); __o_n_c_e_;__o_n_c_e_=0)

#define iterate_byval(v,i_t__e__r_a_t_or,type)\
    for(size_t __io___=0;__io___<v.size;__io___++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type i_t__e__r_a_t_or=(v.data[__io___]);__o_n_c_e_;__o_n_c_e_=0)

#define cvec_print(v,fmt)\
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

#define cvector_push(cvector,type,value) cvec_##type##_push(&(cvector),value)
#define cvector_pop(cvector,type) cvec_##type##_pop(&(cvector))
#define cvector_remove(cvector,type,idx) cvec_##type##_remove(&(cvector),idx)
#define cvector_erase(cvector,type,start,end) cvec_##type##_erase(&(cvector),start,end)
#define cvector_clear(cvector,type) cvec_##type_##clear(&(cvector))
#define cvector_find(cvector,type,value) cvec_##type##_find(&(cvector),value)
#define cvector_insert(cvector,type,value,idx,copies) cvec_##type##_insert(&(cvector),value,idx,copies)
#define cvector_resize(cvector,type,value) cvec_##type##_resize(&(cvector),value)
#define cvector_reserve(cvector,type,value) cvec_##type##_reserve(&(cvector),value)
#define cvector_shrink_to_fit(cvector,type) cvec_##type##_stf(&(cvector))
#define cvector_get(cvector,idx) (cvector).data[idx]
#define cvector_last(cvector) (cvector).data[(cvector).size-1]
#define cvector_first(cvector) (cvector).data[0]
#define cvector_len(cvector) (cvector).size
#define cvector_capacity(cvector) (cvector).capacity
#define new_cvector(type) (cvector_##type){.data=NULL,.size=0,.capacity=0} 
#define cvector(type) cvector_##type 
#endif