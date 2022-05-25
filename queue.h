//
// Created by xjz on 2022/4/18.
//

#ifndef OBJECT_QUEUE_H
#define OBJECT_QUEUE_H
#include "used.h"
#define QUEUE_NODE_SIZE LIST_NODE_SIZE
#define NewQueue(varname,size_)  \
    queue varname = {.number = 0,.type_size = size_,.index = 0}; \
    varname.data.next = NULL;                                           \
    varname.tail = &varname.data;
#define queue_run(object) ({queue_run_obj.obj = &object;&queue_run_obj;})
#define queue(type,varname) NewQueue(varname,sizeof(type))

typedef struct __attribute__((packed)) queue
{
    Queue_Node data;
    Queue_Node *tail;
    Number_t index;
    Number_t number;
    Size_t type_size;
}queue;

typedef struct __attribute__((packed))
{
    queue *obj;
    Real real;
    Empty empty;
    Clear clear;
    Object_Push push;
    Pop pop;
    Top front;
}queue_att;
extern queue_att queue_run_obj;

#endif //OBJECT_QUEUE_H
