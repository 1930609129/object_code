//
// Created by xjz on 2022/5/8.
//

#ifndef OBJECT_SET_H
#define OBJECT_SET_H

#include "used.h"
#include "hash.h"
#define SET_EXPAND 256
#define NewSet(varname,size_) set varname = { \
        .number = 0,.expand = 0,              \
        .type_size = size_,.data = NULL,      \
        .fill = NULL};
#define set(type,varname) NewSet(varname,sizeof(type))
#define set_run(object) ({set_run_obj.obj = &object;&set_run_obj;})
typedef struct __attribute__((packed)) set
{
    Variable data;
    bit8u *fill;
    Number_t number;
    Number_t expand;
    Size_t type_size;
}set;

typedef struct __attribute__((packed))
{
    set *obj;
    Object_Push push;
    Real real;
    Remove remove;
    Find_Value find;
    InitSpace space;
    Clear clear;
}set_att;
extern set_att set_run_obj;

#endif //OBJECT_SET_H

