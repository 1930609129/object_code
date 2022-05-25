//
// Created by xjz on 2022/4/19.
//

#include "DLink.h"

DLink_att DLink_run_obj = {
    .obj = NULL,
    .push = object_push,
    .pop = pop,
    .tail = tail,
    .head = head,
    .insert = object_insert,
    .delete = delete,
    .empty = empty,
    .clear = clear,
    .reverse = reverse,
    .get = get
};

static _Bool empty(){
    return DLink_run_obj.obj->number ? FALSE:TRUE;
}

static void pop(){
    if (DLink_run_obj.obj->data.next == &DLink_run_obj.obj->data) return;
    DLink_Node *node = DLink_run_obj.obj->data.next;
    DLink_run_obj.obj->data.next = node->next;
    node->next->front = &DLink_run_obj.obj->data;
    free(node);
    DLink_run_obj.obj->number--;
}

static void object_push(Variable_const value){
    DLink_Node * data = DLink_run_obj.obj->data.front;
    DLink_Node *node = malloc(DLINK_NODE_SIZE);
    node->data = (char*)value;
    data->next = node;
    node->front = data;
    node->next = &DLink_run_obj.obj->data;
    DLink_run_obj.obj->data.front = node;
    DLink_run_obj.obj->number++;
}

static void object_insert(Index_t id,Variable_const value) {
    DLink_Node *data = &DLink_run_obj.obj->data;
    DLink_Node *node = malloc(DLINK_NODE_SIZE);
    node->data = (char *) value;
    if (id <= DLink_run_obj.obj->number / 2) {
        for (int i = 0; i < id; ++i) {
            data = data->next;
        }
        node->next = data->next;
        data->next->front = node;
        node->front = data;
        data->next = node;
    } else
    {
        for (unsigned int i = id; i < DLink_run_obj.obj->number; ++i) {
            data = data->front;
        }
        node->next = data;
        data->front->next = node;
        node->front = data->front;
        data->front = node;
    }

    DLink_run_obj.obj->number++;
}
static Variable delete(Index_t id)
{
    if (DLink_run_obj.obj->number==0) return NULL;
    DLink_Node *data = &DLink_run_obj.obj->data;
    DLink_Node *node = NULL;
    if (id<=DLink_run_obj.obj->number/2)
    {
        for (int i = 0; i < id; ++i) {
            data = data->next;
        }
        node = data->next;
        data->next = node->next;
        node->next->front = data;
    } else
    {
        int num = DLink_run_obj.obj->number-1-id;
        for (int i = 0; i < num; ++i) {
            data = data->front;
        }
        node = data->front;
        node->front->next = node->next;
        node->next->front = node->front;
    }
    Variable value = node->data;

    free(node);
    DLink_run_obj.obj->number--;
    return value;
}
static Variable head()
{
    if (DLink_run_obj.obj->number==0) return NULL;
    return DLink_run_obj.obj->data.next->data;
}
static Variable tail()
{
    if (DLink_run_obj.obj->number==0) return NULL;
    return DLink_run_obj.obj->data.front->data;
}

static void clear()
{

    DLink_Node *data = DLink_run_obj.obj->data.next;
    while (data!= &DLink_run_obj.obj->data)
    {
        DLink_Node *node = data;
        data = data->next;
        free(node);
    }
    DLink_run_obj.obj->data.front = &DLink_run_obj.obj->data;
    DLink_run_obj.obj->data.next =  &DLink_run_obj.obj->data;
    DLink_run_obj.obj->number = 0;
}

static Variable get(Index_t id)
{
    DLink_Node *data = NULL;
    if (data== &DLink_run_obj.obj->data) return NULL;
    if (id<= DLink_run_obj.obj->number/2)
    {
        data = DLink_run_obj.obj->data.next;
        for (int i = 0; i < id; ++i) {
            data = data->next;
        }
        return data->data;
    } else
    {
        data = DLink_run_obj.obj->data.front;
        int num = DLink_run_obj.obj->number-1-id;
        for (int i = 0; i < num; ++i) {
            data = data->front;
        }
        return data->data;
    }
}

static void reverse(Index_t id)
{
    if (id==0) return;
    DLink_Node *data = DLink_run_obj.obj->data.next;
    DLink_Node *head = data;
    while (id!=0)
    {
        swap(data->next,data->front);
        data = data->front;
        id--;
    }
    head->next = data->next;
    data->next->front = head;
    data->next = data->front;
    DLink_run_obj.obj->data.next = data;
    data->front = &DLink_run_obj.obj->data;
}