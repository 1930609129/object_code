//
// Created by xjz on 2022/4/18.
//

#ifndef OBJECT_LINK_H
#define OBJECT_LINK_H
#include "used.h"

#define link(varname) link varname = {.number = 0}; \
    varname.pointer_tail = &varname.data;          \
    varname.data.next = NULL

#define link_run(object) ({link_run_obj.obj = &object;&link_run_obj;})
#define LINK_NODE_SIZE ONE_NODE_SIZE

typedef struct __attribute__((packed)) link{
    Link_Node data;
    Link_Node *pointer_tail;
    Number_t number;
}link;

typedef struct __attribute__((packed)){
    link *obj;
    Delete delete;
    Object_Insert insert;
    Empty empty;
    Clear clear;
    Object_Push push;
    Pop pop;
    Head head;
    Tail tail;
}link_att;

extern link_att link_run_obj;

#endif //OBJECT_LINK_H
