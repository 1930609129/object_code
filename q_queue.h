//
// Created by xjz on 2022/5/16.
//

#ifndef OBJECT_Q_QUEUE_H
#define OBJECT_Q_QUEUE_H
#include "used.h"
#define Q_QUEUE_NODE_SIZE LIST_NODE_SIZE

#define Q_NewQueue(varname,size_)  \
    q_queue varname = {.number = 0,.type_size = size_,.index = 0}; \
    varname.data.next = NULL;                                           \
    varname.tail = &varname.data;
#define q_queue_run(object) ({q_queue_run_obj.obj = &object;&q_queue_run_obj;})
#define q_queue(type,varname) Q_NewQueue(varname,sizeof(type))

typedef struct __attribute__((packed)) q_queue
{
    Queue_Node data;
    Queue_Node *tail;
    Number_t index;
    Number_t number;
    Size_t type_size;
}q_queue;

typedef struct __attribute__((packed))
{
    q_queue *obj;
    Real real;
    Empty empty;
    Clear clear;
    Object_Push push;
    Pop pop;
    Top front;
}q_queue_att;
extern q_queue_att q_queue_run_obj;
#endif //OBJECT_Q_QUEUE_H
