#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#define cvector(type) \
    typedef struct cvector_##type \
    { \
        type* data; \
        size_t size; \
        size_t capacity;\
        type front;\
        type last;\
    }cvector_##type; \
    static inline void cvec_##type##_push(cvector_##type *v,type value)\
    {\
        if(v->size==v->capacity)\
        {\
            v->capacity=v->capacity?v->capacity*2:1;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        if(v->size==0)\
        {\
            v->front=value;\
            v->last=value;\
        }\
        else\
        {\
            v->last=value;\
        }\
        v->data[v->size++]=value;\
    }\
    static inline type cvec_##type##_pop(cvector_##type *v)\
    {\
        v->last=v->data[(v->size)-2];\
        return v->data[--v->size];\
    }\
    static inline void cvec_##type##_remove(cvector_##type *v,int idx)\
    {\
        for(int _i=idx;_i<(v->size)-1;_i++)\
        {\
            v->data[_i]=v->data[_i+1];\
        }\
        if(idx==0) v->front=v->data[0];\
        v->size--;\
    }\
    static inline void cvec_##type##_insert(cvector_##type *v,type value,int idx,int copies)\
    {\
        if(!(((v->size)+copies)<=v->capacity))\
        {\
            v->capacity*=2;\
            v->data=realloc(v->data,v->capacity*sizeof(type));\
        }\
        int str_cp=copies,str_idx=idx;\
        v->size+=copies;\
        while(copies>0)\
        {\
            for(int _i=v->size-1;_i>=idx;_i--)\
            {\
                v->data[_i+1]=v->data[_i];\
            }\
            idx++;\
            copies--;\
        }\
        for(int _i=0;_i<str_cp;_i++)\
        {\
            v->data[str_idx++]=value;\
        }\
    }

#define iterate_byref(v,_i_te__rat_or,type)\
    for(size_t i=0;i<v.size;i++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type* _i_te__rat_or=&(v.data[i]); __o_n_c_e_;__o_n_c_e_=0)

#define iterate_byval(v,i_t__e__r_a_t_or,type)\
    for(size_t i=0;i<v.size;i++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type i_t__e__r_a_t_or=(v.data[i]);__o_n_c_e_;__o_n_c_e_=0)

#define cvec_print(v,fmt)\
    do\
    {\
        printf("[");\
        for(int i=0;i<v.size;i++)\
        {\
            printf(fmt,v.data[i]);\
            if(i<v.size-1)\
            {\
                printf(",");\
            }\
        }\
        printf("]\n");\
    }while(0);

#define init_cvector(type) (cvector_##type){.data=NULL,.size=0,.capacity=0} 

#endif