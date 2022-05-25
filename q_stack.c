//
// Created by xjz on 2022/5/16.
//

#include "q_stack.h"
q_stack_att q_stack_run_obj = {
    .obj = NULL,
    .real=real,
    .clear=clear,
    .empty=empty,
    .push=object_push,
    .pop=pop,
    .top=top
};

static Variable top()
{
    if (q_stack_run_obj.obj->number==0) return NULL;
    Stack_Node *node = q_stack_run_obj.obj->data.next;
    if(node)
    {

        return node->data+(((q_stack_run_obj.obj->number-1)%Q_Buffer)* q_stack_run_obj.obj->type_size)+Q_STACK_NODE_SIZE;
    }
    return NULL;
}

static void pop()
{
    if(q_stack_run_obj.obj->number == 0) return;
    q_stack_run_obj.obj->number--;
    if (q_stack_run_obj.obj->number%Q_Buffer==0)
    {
        Stack_Node *node = q_stack_run_obj.obj->data.next;
        q_stack_run_obj.obj->data.next = node->next;
        free(node);
    }
}

static void object_push(Variable_const value)
{
    Size_t type_size = q_stack_run_obj.obj->type_size;
    if (q_stack_run_obj.obj->number%Q_Buffer==0)
    {
        Stack_Node *node = malloc((type_size*Q_Buffer)+Q_STACK_NODE_SIZE);
        node->next = q_stack_run_obj.obj->data.next;
        q_stack_run_obj.obj->data.next = node;
    }
    memcpy(q_stack_run_obj.obj->data.next->data+((q_stack_run_obj.obj->number%Q_Buffer)*type_size)+Q_STACK_NODE_SIZE,
           value,type_size);
    q_stack_run_obj.obj->number++;
}

static Variable real()
{
    q_stack *obj = q_stack_run_obj.obj;
    Variable res = malloc(obj->number*obj->type_size);
    Stack_Node *data = obj->data.next;
    Size_t offset = obj->number%Q_Buffer;
    Local local = 0;
    Size_t size;
    if(offset)
    {
        offset--;
        size = offset*obj->type_size;
        offset+=1;
        for (Index_t i = 0; i < offset; i++) {
            memcpy(res+local,data->data+Q_STACK_NODE_SIZE+size,obj->type_size);
            size-=obj->type_size;
            local+=obj->type_size;
        }
        data = data->next;
    }
    offset = Q_Buffer;
    Size_t temp = (offset-1)*obj->type_size;
    while (data)
    {
        size = temp;
        for (Index_t i = 0; i < offset; i++) {
            memcpy(res+local,data->data+Q_STACK_NODE_SIZE+size,obj->type_size);
            size-=obj->type_size;
            local+=obj->type_size;
        }
        data = data->next;
    }
    return res;
}

static _Bool empty()
{
    return q_stack_run_obj.obj->number ? FALSE:TRUE;
}

static void clear()
{
    Stack_Node *data = q_stack_run_obj.obj->data.next;
    while (data)
    {
        Stack_Node *node = data;
        data = data->next;
        free(node);
    }
    q_stack_run_obj.obj->data.next = NULL;
    q_stack_run_obj.obj->number = 0;
}