//
// Created by xjz on 2022/4/16.
//

#ifndef OBJECT_STACK_H
#define OBJECT_STACK_H

#include "used.h"
#define STACK_NODE_SIZE LIST_NODE_SIZE
#define stack_run(object) ({stack_run_obj.obj = &object;&stack_run_obj;})
#define NewStack(varname,size_) stack varname = {.number=0,.type_size = size_}; \
    varname.data.next = NULL;
#define stack(type,varname) NewStack(varname,sizeof(type))
typedef struct __attribute__((packed))
{
    Stack_Node data;
    Number_t number;
    Size_t type_size;
}stack;

typedef struct __attribute__((packed)){
    stack *obj;
    Real real;
    Clear clear;
    Empty empty;
    Object_Push push;
    Pop pop;
    Top top;
}stack_att;
extern stack_att stack_run_obj;


#endif //OBJECT_STACK_H
