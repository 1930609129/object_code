//
// Created by xjz on 2022/4/13.
//

#include "list.h"

list_att list_run_obj = {
        .obj = NULL,
        .clear = clear,
        .empty = empty,
        .insert = object_insert,
        .delete = delete,
        .back_insert = object_back_insert,
        .pop = pop,
        .push = object_push,
        .front_insert = object_front_insert,
        .head = head,
        .tail = tail,
        .get = get,
        .areal = areal,
        .real = real,
        .iterator_insert = object_iterator_insert
};

static void clear(){
    BLOCK *data = list_run_obj.obj->data.next;
    while (data!= &list_run_obj.obj->data)
    {
        BLOCK *node = data;
        data = data->next;
        free(node);
    }
    list_run_obj.obj->data.front = &list_run_obj.obj->data;
    list_run_obj.obj->data.next =  &list_run_obj.obj->data;
    list_run_obj.obj->number = 0;
}

static _Bool empty(){
    if (list_run_obj.obj->number==0) return TRUE;
    return FALSE;
}

static void object_insert(Index_t id,Variable_const value){
    BLOCK *data = NULL;
    Size_t all_size = 0;
    Size_t type_size = list_run_obj.obj->type_size;
    if (id< list_run_obj.obj->number/2)
    {
        data = list_run_obj.obj->data.front;
        while (data!= &list_run_obj.obj->data)
        {
            all_size+=data->size;
            if (all_size>=id)
                break;
            data = data->front;
        }
        if (data==NULL) return;
        id = id -(all_size-data->size);
    }
    else
    {
        data = list_run_obj.obj->data.next;
        while (data!= &list_run_obj.obj->data)
        {
            all_size+=data->size;
            if (all_size>= list_run_obj.obj->number-id)
                break;
            data = data->next;
        }
        if (data==&list_run_obj.obj->data) return;
        id = id-(list_run_obj.obj->number-all_size);
    }

    if (data->size>=Buffer)
    {
        BLOCK *front = data->front;
        BLOCK *next = data->next;
        data = realloc(data,type_size*(data->size+1)+BLOCK_NODE_SIZE);
        front->next = data;
        next->front = data;
    }

    Number_t number = data->size-id;
    for (Index_t i = 0; i < number; ++i) {
        Size_t size = (data->size-i)*type_size;
        memcpy(data->data+size+BLOCK_NODE_SIZE,
               data->data+size-type_size+BLOCK_NODE_SIZE,type_size);
    }
    memcpy(data->data+(id*type_size)+BLOCK_NODE_SIZE,value,type_size);
    data->size++;
    list_run_obj.obj->number++;
}

static Variable get(Index_t id)
{
    BLOCK *data = list_run_obj.obj->data.front;
    Size_t all_size = 0;
    while (data!= &list_run_obj.obj->data)
    {
        all_size+=data->size;
        if (all_size>id)
            break;
        data = data->front;
    }
    if (data==&list_run_obj.obj->data) return FALSE;
    id = id -(all_size-data->size);
    return data->data+(id* list_run_obj.obj->type_size)+BLOCK_NODE_SIZE;
}

static Variable delete(Index_t id){
    BLOCK *data = list_run_obj.obj->data.front;
    if (data==&list_run_obj.obj->data) return FALSE;
    Size_t type_size = list_run_obj.obj->type_size;
    Size_t all_size = 0;
    while (data!= &list_run_obj.obj->data)
    {
        all_size+=data->size;
        if (all_size>id)
            break;
        data = data->front;
    }
    id = id -(all_size-data->size);
    Variable value = malloc(type_size);
    memcpy(value,data->data+(id*type_size)+BLOCK_NODE_SIZE,type_size);
    data->size--;
    for (unsigned int i = id; i<data->size; i++) {
        memcpy(data->data+(i*type_size)+BLOCK_NODE_SIZE,data->data+(i+1)*type_size+BLOCK_NODE_SIZE,type_size);
    }

    if (data->size==0)
    {
        data->front->next = data->next;
        data->next->front = data->front;
        free(data);
    }
    list_run_obj.obj->number--;
    return value;
}

static _Bool object_front_insert(Variable_const value){
    BLOCK *data = list_run_obj.obj->data.front;
    Size_t type_size = list_run_obj.obj->type_size;
    if (data==&list_run_obj.obj->data) return FALSE;
    BLOCK *front = data->front;
    BLOCK *next = data->next;

    Size_t all_size = type_size*data->size;
    data->size++;
    BLOCK *node = malloc(all_size+type_size+BLOCK_NODE_SIZE);
    memcpy(node,data,BLOCK_NODE_SIZE);
    memcpy(node->data+BLOCK_NODE_SIZE+type_size,
           data->data+BLOCK_NODE_SIZE,all_size);
    memcpy(node->data+BLOCK_NODE_SIZE,value,type_size);
    free(data);
    list_run_obj.obj->data.front = node;
    front->next = list_run_obj.obj->data.front;
    next->front = list_run_obj.obj->data.front;
    list_run_obj.obj->number++;
    return TRUE;
}
static _Bool object_back_insert(Variable_const value){
    BLOCK *data = list_run_obj.obj->data.next;
    Size_t type_size = list_run_obj.obj->type_size;
    if (data==&list_run_obj.obj->data) return FALSE;

    if (data->size>=Buffer)
    {
        BLOCK *front = data->front;
        BLOCK *next = data->next;
        list_run_obj.obj->data.next = realloc(list_run_obj.obj->data.next,(type_size*(data->size+1))+BLOCK_NODE_SIZE);
        front->next = list_run_obj.obj->data.next;
        next->front = list_run_obj.obj->data.next;
    }
    data = list_run_obj.obj->data.next;
    memcpy(data->data+(data->size*type_size)+BLOCK_NODE_SIZE,value,type_size);
    data->size++;
    list_run_obj.obj->number++;
    return TRUE;
}
static void pop(){
    BLOCK *data = list_run_obj.obj->data.next;
    if (data==&list_run_obj.obj->data) {
        return;
    }
    data->size--;
    if (data->size==0)
    {
        list_run_obj.obj->data.next = data->next;
        data->next->front = &list_run_obj.obj->data;
        free(data);
    }
    list_run_obj.obj->number--;
}

static void object_push(Variable_const value){

    BLOCK *data = &list_run_obj.obj->data;
    Size_t type_size = list_run_obj.obj->type_size;
    if (data->size>=Buffer)
    {
        BLOCK *node = malloc(type_size*Buffer+BLOCK_NODE_SIZE);
        node->size = 0;
        node->next = data->next;
        node->next->front = node;
        node->front = &list_run_obj.obj->data;
        list_run_obj.obj->data.next = node;
    }
    data = list_run_obj.obj->data.next;
    memcpy(data->data+(data->size*type_size)+BLOCK_NODE_SIZE,value,type_size);
    data->size++;
    list_run_obj.obj->data.size = data->size;
    list_run_obj.obj->number++;

}

static void object_iterator_insert(Variable iterator,Variable_const value)
{
    BLOCK *data = iterator;
    Size_t type_size = list_run_obj.obj->type_size;
    if (data==&list_run_obj.obj->data) return;
    if (data->size>=Buffer)
    {
        BLOCK *front = data->front;
        BLOCK *next = data->next;
        iterator = realloc(iterator,type_size*(data->size+1)+BLOCK_NODE_SIZE);
        front->next = iterator;
        next->front = iterator;
    }
    data = iterator;
    memcpy(data->data+(data->size*type_size)+BLOCK_NODE_SIZE,value,type_size);
    data->size++;
    list_run_obj.obj->number++;
}

static PVariable areal()
{
    BLOCK *data = list_run_obj.obj->data.front;
    PVariable res;
    Index_t id = 0;
    while (data!=&list_run_obj.obj->data)
    {
        id++;
        data = data->front;
    }
    res = malloc(id*8);
    id = 0;
    while (data!= &list_run_obj.obj->data)
    {
        res[id++] = data->data+BLOCK_NODE_SIZE;
        data = data->front;
    }
    return res;
}

static Variable real()
{
    list *obj = list_run_obj.obj;
    Variable res = malloc(obj->number*obj->type_size);
    BLOCK *data = obj->data.front;
    Current_t current = 0;
    Local offset;
    while(data!=&obj->data)
    {
        offset = data->size*obj->type_size;
        memcpy(res+current,data->data+BLOCK_NODE_SIZE,offset);
        current+=offset;
        data = data->front;
    }
    return res;
}

static Variable head(){
    return list_run_obj.obj->data.front->data+BLOCK_NODE_SIZE;
}
static Variable tail(){
    return list_run_obj.obj->data.next->data+(list_run_obj.obj->data.next->size-1)* list_run_obj.obj->type_size+BLOCK_NODE_SIZE;
}
