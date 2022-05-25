//
// Created by xjz on 2022/5/12.
//

#ifndef OBJECT_VECTOR_H
#define OBJECT_VECTOR_H

#include "used.h"
#define NewVector(varname,size_) vector varname = {.type_size = size_,.number = 0,.data = NULL};
#define vector(type,varname) NewVector(varname,sizeof(type))
#define vector_run(object) ({vector_run_obj.obj = &object;&vector_run_obj;})
typedef struct __attribute__((packed)) vector
{
    Variable data;
    Number_t number;
    Size_t type_size;
}vector;

typedef struct __attribute__((packed))
{
    vector *obj;
    Object_Push push;
    InitSpace space;
    Clear clear;
}vector_att;

extern vector_att vector_run_obj;

//typedef struct __attribute__((packed)) vector
//{
//    Variable data;
//    Init init;
//    Object_Push push;
//    InitSpace space;
//    Number_t number;
//    Clear clear;
//    Size_t type_size;
//}vector;

#endif //OBJECT_VECTOR_H
