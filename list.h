//
// Created by xjz on 2022/4/13.
//

#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
#include "used.h"
#define NewList(varname,size_) list varname = {.number=0,.type_size = size_}; \
    varname.data.next = &varname.data;                                          \
    varname.data.front = &varname.data;                                         \
    varname.data.size = Buffer;
#define list(type,varname) NewList(varname,sizeof(type))
#define list_run(object) ({list_run_obj.obj = &object;&list_run_obj;})

typedef struct __attribute__((packed)) list{
    BLOCK data;
    Number_t number;
    Size_t type_size;
}list;

typedef struct __attribute__((packed))
{
    list *obj;
    Clear clear;
    Get get;
    Areal areal;
    Real real;
    Empty empty;
    Object_Insert insert;
    Delete delete;
    Object_Iterator_Insert iterator_insert;
    Object_Back_Insert back_insert;
    Pop pop;
    Object_Push push;
    Object_Front_Insert front_insert;
    Head head;
    Tail tail;
}list_att;

extern list_att list_run_obj;

#endif //OBJECT_LIST_H
