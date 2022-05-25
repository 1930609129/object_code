//
// Created by xjz on 2022/4/18.
//

#include "queue.h"

queue_att queue_run_obj = {
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
    if(queue_run_obj.obj->number == 0) return NULL;
    Queue_Node *node = queue_run_obj.obj->data.next;
    return node->data+(queue_run_obj.obj->type_size*queue_run_obj.obj->index)+QUEUE_NODE_SIZE;
}

static void pop()
{
    if (queue_run_obj.obj->data.next==NULL) return;
    queue_run_obj.obj->index++;
    if (--queue_run_obj.obj->number==0) queue_run_obj.obj->tail = &queue_run_obj.obj->data;
    if (queue_run_obj.obj->index==Buffer|| queue_run_obj.obj->number==0)
    {
        Queue_Node *node = queue_run_obj.obj->data.next;
        queue_run_obj.obj->data.next = node->next;
        free(node);
        queue_run_obj.obj->index = 0;
    }
}

static void object_push(Variable_const value)
{
    Size_t type_size = queue_run_obj.obj->type_size;
    if (queue_run_obj.obj->number%Buffer==0)
    {
        Queue_Node* data = queue_run_obj.obj->tail;
        Queue_Node *node = malloc((type_size*Buffer)+QUEUE_NODE_SIZE);
        node->next = NULL;
        data->next = node;
        queue_run_obj.obj->tail = node;
    }
    Queue_Node* data = queue_run_obj.obj->tail;
    memcpy(data->data+ ((queue_run_obj.obj->number%Buffer)* queue_run_obj.obj->type_size)+QUEUE_NODE_SIZE,
           value, queue_run_obj.obj->type_size);
    queue_run_obj.obj->number++;
}

static Variable real()
{
    queue *obj = queue_run_obj.obj;
    Queue_Node *data = obj->data.next;
    Variable res = malloc(obj->number*obj->type_size);
    Local local = 0;
    Size_t offset = Buffer*obj->type_size;
    while (data!=obj->tail)
    {
        memcpy(res+local,data->data+ QUEUE_NODE_SIZE,offset);
        local+=offset;
        data = data->next;
    }
    offset = obj->number%Buffer;
    offset = offset*obj->type_size;
    if(offset)
    {
        memcpy(res+local,obj->tail->data+QUEUE_NODE_SIZE,offset);
    } else
    {
        offset = Buffer*obj->type_size;
        memcpy(res+local,obj->tail->data+QUEUE_NODE_SIZE,offset);
    }
    return res;
}

static void clear()
{
    Queue_Node *data = queue_run_obj.obj->data.next;
    while (data)
    {
        Queue_Node *node = data;
        data = data->next;
        free(node);
    }
    queue_run_obj.obj->number = 0;
    queue_run_obj.obj->index = 0;
    queue_run_obj.obj->data.next = NULL;
    queue_run_obj.obj->tail = &queue_run_obj.obj->data;
}

static _Bool empty()
{
    return queue_run_obj.obj->number ? FALSE:TRUE;
}
