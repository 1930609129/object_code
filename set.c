//
// Created by xjz on 2022/5/8.
//

#include "set.h"
#define set_mut 0.75
#define init_mut_set 0.6666666666666666
set_att set_run_obj = {
    .obj = NULL,
    .remove = remove_value,
    .push = object_push,
    .real = real,
    .clear = clear,
    .space = space,
    .find = find_value
};

static inline hash_id hash(char *key)
{
    hash_key id = unique_hash_t(key,set_run_obj.obj->type_size);
    return id%set_run_obj.obj->expand;
}

static void object_push(Variable_const value)
{
    set *obj = set_run_obj.obj;
    hash_id id;
    Current_t current;
    Number_t num = obj->expand*set_mut;
    if(obj->number == num)
    {
        Variable local;
        Number_t old_expand = obj->expand;
        obj->expand += obj->number*set_mut;
        obj->expand = (1+obj->expand/SET_EXPAND)*SET_EXPAND;
        Variable new_set = malloc(obj->expand*obj->type_size);
        bit8u *new_fill = calloc(obj->expand,1);

        for (Number_t i = 0; i < old_expand; ++i) {
            if(obj->fill[i]==1)
            {
                local = obj->data+i*obj->type_size;
                id = hash(local);
                if(new_fill[id])
                {
                    id++;
                    while (id!=obj->expand&&new_fill[id])
                        id++;
                }
                if(id==obj->expand)
                {
                    id = 0;
                    while (new_fill[id])
                        id++;
                }
                current = id*obj->type_size;
                memcpy(new_set+current,local,obj->type_size);
                new_fill[id] = 1;
            }
        }

        free(obj->fill);
        free(obj->data);
        obj->data = new_set;
        obj->fill = new_fill;
    }
    id = hash((char*)value);
    current = id*obj->type_size;
    if(obj->fill[id]==1)
    {
        if(memcmp(obj->data+current,value,obj->type_size)==0)
            return;
        else
        {
            id++;
            while (id!=obj->expand&&obj->fill[id]==1)
            {
                current = id*obj->type_size;
                if(memcmp(obj->data+current,value,obj->type_size)==0)
                    return;
                id++;
            }
            if(id == obj->expand)
            {
                id = 0;
                while (obj->fill[id]==1)
                {
                    current = id* obj->type_size;
                    if(memcmp(obj->data+current,value,obj->type_size)==0)
                        return;
                    id++;
                }
            }
        }
    }
    obj->fill[id] = 1;
    memcpy(obj->data+id*obj->type_size,value,obj->type_size);
    obj->number++;
}

static Variable find_value(Variable value)
{
    set *obj = set_run_obj.obj;
    hash_id id = hash(value);
    Current_t current;
    while (id!=obj->expand&&obj->fill[id])
    {
        current = id *obj->type_size;
        if(obj->fill[id]!=-1&&memcmp(obj->data+current,value,obj->type_size)==0)
            return obj->data+current;
        id++;
    }
    if(id==obj->expand)
    {
        id = 0;
        while (obj->fill[id])
        {
            current = id *obj->type_size;
            if(obj->fill[id]!=-1&&memcmp(obj->data+current,value,obj->type_size)==0)
                return obj->data+current;
            id++;
        }
    }
    return NULL;
}

static void remove_value(Variable value)
{
    set *obj = set_run_obj.obj;
    hash_id id = hash(value);
    Current_t current;
    while (id!=obj->expand&&obj->fill[id])
    {
        current = id *obj->type_size;
        if(obj->fill[id]!=-1&&memcmp(obj->data+current,value,obj->type_size)==0)
        {
            obj->number--;
            obj->fill[id] = -1;
        }
        id++;
    }
    if(id==obj->expand)
    {
        id = 0;
        while (obj->fill[id])
        {
            current = id *obj->type_size;
            if(obj->fill[id]!=-1&&memcmp(obj->data+current,value,obj->type_size)==0)
            {
                obj->number--;
                obj->fill[id] = -1;
            }
            id++;
        }
    }
}

static void space(Number_t num)
{
    set *obj = set_run_obj.obj;
    obj->expand = num*(1+init_mut_set);
    obj->data = malloc(obj->type_size*obj->expand);
    obj->fill = calloc(obj->expand,1);
}

static Variable real()
{
    set *obj = set_run_obj.obj;
    Current_t current = 0;
    Variable res = malloc(obj->type_size*obj->number);
    for (Number_t i = 0; i < obj->expand; ++i) {
        if(obj->fill[i]==1)
        {
            memcpy(res+current,obj->data+i*obj->type_size,obj->type_size);
            current+=obj->type_size;
        }
    }
    return res;
}

static void clear()
{
    free(set_run_obj.obj->data);
    free(set_run_obj.obj->fill);
    set_run_obj.obj->expand = 0;
    set_run_obj.obj->number = 0;
}