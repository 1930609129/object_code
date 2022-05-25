//
// Created by xjz on 2022/4/19.
//

#ifndef OBJECT_DLINK_H
#define OBJECT_DLINK_H

#include "used.h"

#define DLink(varname) DLink varname = {.number = 0}; \
    varname.data.front = &varname.data;               \
    varname.data.next = &varname.data

#define DLINK_NODE_SIZE TWO_NODE_SIZE
#define DLink_run(object) ({DLink_run_obj.obj = &object;&DLink_run_obj;})

typedef struct __attribute__((packed)) DLink{
    DLink_Node data;
    Number_t number;
}DLink;

typedef struct __attribute__((packed)) {
    DLink *obj;
    Clear clear;
    Delete delete;
    Object_Insert insert;
    Empty empty;
    Object_Push push;
    Pop pop;
    Head head;
    Tail tail;
    Reverse reverse;
    Get get;
}DLink_att;

extern DLink_att DLink_run_obj;
#endif //OBJECT_DLINK_H
