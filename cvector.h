#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>
#define cvector(type) \
    typedef struct cvector_##type \
    { \
        type* data; \
        size_t size; \
        size_t capacity;\
    }cvector_##type; \
\
    static inline void init_##type(cvector_##type *v)\
    { \
        v->data=NULL;\
        v->size=0;\
        v->capacity=0;\
    }\
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
        for(int _i=idx;_i<v->size;_i++)\
        {\
            v->data[idx]=v->data[idx+1];\
        } \
        (v->size)--;\
    }

#define iterate_byref(v,_i_te__rat_or,type)\
    for(size_t i=0;i<v.size;i++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type* _i_te__rat_or=&(v.data[i]); __o_n_c_e_;__o_n_c_e_=0)

#define iterate_byval(v,i_t__e__r_a_t_or,type)\
    for(size_t i=0;i<v.size;i++) \
        for(int  __o_n_c_e_=1; __o_n_c_e_; __o_n_c_e_=0)\
            for(type i_t__e__r_a_t_or=(v.data[i]);__o_n_c_e_;__o_n_c_e_=0)
        




#define init_cvec(type,name)\
    cvector_##type name;\
    init_##type(&name);

#endif