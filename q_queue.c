//
// Created by xjz on 2022/5/16.
//

#include "q_queue.h"

q_queue_att q_queue_run_obj = {
        .obj = NULL,
        .push = object_push,
        .pop = pop,
        .front = front,
        .empty = empty,
        .real = real,
        .clear = clear
};

static Variable front()
{
    if(q_queue_run_obj.obj->number == 0) return NULL;
    Queue_Node *node = q_queue_run_obj.obj->data.next;
    return node->data+(q_queue_run_obj.obj->type_size*q_queue_run_obj.obj->index)+Q_QUEUE_NODE_SIZE;
}

static void pop()
{
    if (q_queue_run_obj.obj->data.next==NULL) return;
    q_queue_run_obj.obj->index++;
    if (--q_queue_run_obj.obj->number==0) q_queue_run_obj.obj->tail = &q_queue_run_obj.obj->data;
    if (q_queue_run_obj.obj->index==Q_Buffer|| q_queue_run_obj.obj->number==0)
    {
        Queue_Node *node = q_queue_run_obj.obj->data.next;
        q_queue_run_obj.obj->data.next = node->next;
        free(node);
        q_queue_run_obj.obj->index = 0;
    }
}

static void object_push(Variable_const value)
{
    Size_t type_size = q_queue_run_obj.obj->type_size;
    if (q_queue_run_obj.obj->number%Q_Buffer==0)
    {
        Queue_Node* data = q_queue_run_obj.obj->tail;
        Queue_Node *node = malloc((type_size*Q_Buffer)+Q_QUEUE_NODE_SIZE);
        node->next = NULL;
        data->next = node;
        q_queue_run_obj.obj->tail = node;
    }
    Queue_Node* data = q_queue_run_obj.obj->tail;
    memcpy(data->data+ ((q_queue_run_obj.obj->number%Q_Buffer)* q_queue_run_obj.obj->type_size)+Q_QUEUE_NODE_SIZE,
           value, q_queue_run_obj.obj->type_size);
    q_queue_run_obj.obj->number++;
}

static Variable real()
{
    q_queue *obj = q_queue_run_obj.obj;
    Queue_Node *data = obj->data.next;
    Variable res = malloc(obj->number*obj->type_size);
    Local local = 0;
    Size_t offset = Q_Buffer*obj->type_size;
    while (data!=obj->tail)
    {
        memcpy(res+local,data->data+ Q_QUEUE_NODE_SIZE,offset);
        local+=offset;
        data = data->next;
    }
    offset = obj->number%Q_Buffer;
    offset = offset*obj->type_size;
    if(offset)
    {
        memcpy(res+local,obj->tail->data+Q_QUEUE_NODE_SIZE,offset);
    } else
    {
        offset = Q_Buffer*obj->type_size;
        memcpy(res+local,obj->tail->data+Q_QUEUE_NODE_SIZE,offset);
    }
    return res;
}

static void clear()
{
    Queue_Node *data = q_queue_run_obj.obj->data.next;
    while (data)
    {
        Queue_Node *node = data;
        data = data->next;
        free(node);
    }
    q_queue_run_obj.obj->number = 0;
    q_queue_run_obj.obj->index = 0;
    q_queue_run_obj.obj->data.next = NULL;
    q_queue_run_obj.obj->tail = &q_queue_run_obj.obj->data;
}

static _Bool empty()
{
    return q_queue_run_obj.obj->number ? FALSE:TRUE;
}