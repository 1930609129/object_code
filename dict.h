//
// Created by xjz on 2022/4/30.
//

#ifndef OBJECT_DICT_H
#define OBJECT_DICT_H
#include "used.h"
#include "hash.h"

#define EXPAND 256
#define NewDict(varname,KSize,VSize) dict varname = { \
    .number = 0,                            \
    .data = NULL,                           \
    .fill = NULL,                           \
    .k_size = KSize,                                    \
    .v_size = VSize,                                    \
    .expand = 0}
#define dict(KType,VType,varname) NewDict(varname,sizeof(KType),sizeof(VType))
#define dict_run(object)  ({dict_run_obj.obj = &object;&dict_run_obj;})
typedef struct __attribute__((packed)) dict{
    Variable data;
    bit8u *fill;
    uint16d k_size;
    uint16d v_size;
    Size_t expand;
    Number_t number;
}dict;

typedef struct __attribute__((packed)){
    dict *obj;
    Find get;
    Add push;
    Find_Remove pop;
    Key key;
    Value value;
    Item item;
    InitSpace space;
    Clear clear;
}dict_att;

extern dict_att dict_run_obj;
#endif //OBJECT_DICT_H
