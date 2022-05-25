//
// Created by xjz on 2022/4/18.
//

#include "link.h"

link_att link_run_obj = {
    .obj = NULL,
    .clear = clear,
    .push = object_push,
    .pop = pop,
    .tail = tail,
    .head = head,
    .insert = object_insert,
    .delete = delete,
    .empty = empty
};


static _Bool empty(){
    return link_run_obj.obj->number ? FALSE:TRUE;
}

static void pop(){
    if (&link_run_obj.obj->data == link_run_obj.obj->pointer_tail) return;
    Link_Node *node = link_run_obj.obj->data.next;
    link_run_obj.obj->data.next = node->next;
    free(node);
    if (--link_run_obj.obj->number==0) link_run_obj.obj->pointer_tail = &link_run_obj.obj->data;
}
static void object_push(Variable_const value){
    Link_Node * data = link_run_obj.obj->pointer_tail;
    Link_Node *node = malloc(LINK_NODE_SIZE);
    node->next = &link_run_obj.obj->data;
    node->data = (char*)value;
    data->next = node;
    link_run_obj.obj->pointer_tail = node;
    link_run_obj.obj->number++;
}
static void object_insert(Index_t id,Variable_const value){
    Link_Node *data = &link_run_obj.obj->data;
    for (int i = 0; i < id; ++i) {
        data = data->next;
    }
    Link_Node *node = malloc(LINK_NODE_SIZE);
    node->data = (char *)value;
    node->next = data->next;
    data->next = node;
    link_run_obj.obj->number++;
}
static Variable delete(Index_t id)
{
    if (link_run_obj.obj->number==0) return NULL;
    Link_Node *data = &link_run_obj.obj->data;
    for (int i = 0; i < id; ++i) {
        data = data->next;
    }
    Link_Node *node = data->next;
    Variable value = node->data;
    data->next = node->next;
    free(node);
    link_run_obj.obj->number--;
    return value;
}
static Variable head()
{
    if (link_run_obj.obj->number==0) return NULL;
    return link_run_obj.obj->data.next->data;
}
static Variable tail()
{
    if (link_run_obj.obj->number==0) return NULL;
    return link_run_obj.obj->pointer_tail->data;
}

static void clear()
{
    Link_Node *data = link_run_obj.obj->data.next;
    while (data!= &link_run_obj.obj->data)
    {
        Link_Node *node = data;
        data = data->next;
        free(node);
    }
    link_run_obj.obj->number = 0;
    link_run_obj.obj->data.next = NULL;
    link_run_obj.obj->pointer_tail = &link_run_obj.obj->data;
}