//
// Created by xjz on 2022/5/12.
//

#include "vector.h"

vector_att vector_run_obj = {
    .obj = NULL,
    .space = space,
    .push = object_push,
    .clear = clear
};

static void object_push(Variable_const value)
{
    vector *obj = vector_run_obj.obj;
    memcpy(obj->data+obj->number*obj->type_size,value,obj->type_size);
    obj->number++;
}

static void space(Number_t num)
{
    vector *obj = vector_run_obj.obj;
    obj->data = realloc(obj->data,num*obj->type_size);
}

static void clear()
{
    vector *obj = vector_run_obj.obj;
    free(obj->data);
}