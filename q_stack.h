//
// Created by xjz on 2022/5/16.
//

#ifndef OBJECT_Q_STACK_H
#define OBJECT_Q_STACK_H
#include "used.h"
#define Q_STACK_NODE_SIZE LIST_NODE_SIZE
#define q_stack_run(object) ({q_stack_run_obj.obj = &object;&q_stack_run_obj;})
#define Q_NewStack(varname,size_) q_stack varname = {.number=0,.type_size = size_}; \
    varname.data.next = NULL;

#define q_stack(type,varname) Q_NewStack(varname,sizeof(type))
typedef struct __attribute__((packed))
{
    Stack_Node data;
    Number_t number;
    Size_t type_size;
}q_stack;

typedef struct __attribute__((packed)){
    q_stack *obj;
    Real real;
    Clear clear;
    Empty empty;
    Object_Push push;
    Pop pop;
    Top top;
}q_stack_att;
extern q_stack_att q_stack_run_obj;
#endif //OBJECT_Q_STACK_H
