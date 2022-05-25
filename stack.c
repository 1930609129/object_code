//
// Created by xjz on 2022/4/16.
//

#include "stack.h"

stack_att stack_run_obj = {
        .obj = NULL,
        .real=real,
        .clear=clear,
        .empty=empty,
        .push=object_push,
        .pop=pop,
        .top=top};

static Variable top()
{
    if (stack_run_obj.obj->number==0) return NULL;
    Stack_Node *node = stack_run_obj.obj->data.next;
    if(node)
    {

        return node->data+(((stack_run_obj.obj->number-1)%Buffer)* stack_run_obj.obj->type_size)+STACK_NODE_SIZE;
    }
    return NULL;
}

static void pop()
{
    if(stack_run_obj.obj->number == 0) return;
    stack_run_obj.obj->number--;
    if (stack_run_obj.obj->number%Buffer==0)
    {
        Stack_Node *node = stack_run_obj.obj->data.next;
        stack_run_obj.obj->data.next = node->next;
        free(node);
    }
}

static void object_push(Variable_const value)
{
    Size_t type_size = stack_run_obj.obj->type_size;
    if (stack_run_obj.obj->number%Buffer==0)
    {
        Stack_Node *node = malloc((type_size*Buffer)+STACK_NODE_SIZE);
        node->next = stack_run_obj.obj->data.next;
        stack_run_obj.obj->data.next = node;
    }
    memcpy(stack_run_obj.obj->data.next->data+((stack_run_obj.obj->number%Buffer)*type_size)+STACK_NODE_SIZE,
           value,type_size);
    stack_run_obj.obj->number++;
}

static Variable real()
{
    stack *obj = stack_run_obj.obj;
    Variable res = malloc(obj->number*obj->type_size);
    Stack_Node *data = obj->data.next;
    Size_t offset = obj->number%Buffer;
    Local local = 0;
    Size_t size;
    if(offset)
    {
        offset--;
        size = offset*obj->type_size;
        offset+=1;
        for (Index_t i = 0; i < offset; i++) {
            memcpy(res+local,data->data+STACK_NODE_SIZE+size,obj->type_size);
            size-=obj->type_size;
            local+=obj->type_size;
        }
        data = data->next;
    }
    offset = Buffer;
    Size_t temp = (offset-1)*obj->type_size;
    while (data)
    {
        size = temp;
        for (Index_t i = 0; i < offset; i++) {
            memcpy(res+local,data->data+STACK_NODE_SIZE+size,obj->type_size);
            size-=obj->type_size;
            local+=obj->type_size;
        }
        data = data->next;
    }
    return res;
}

static _Bool empty()
{
    return stack_run_obj.obj->number ? FALSE:TRUE;
}

static void clear()
{
    Stack_Node *data = stack_run_obj.obj->data.next;
    while (data)
    {
        Stack_Node *node = data;
        data = data->next;
        free(node);
    }
    stack_run_obj.obj->data.next = NULL;
    stack_run_obj.obj->number = 0;
}