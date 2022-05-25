//
// Created by xjz on 2022/4/30.
//

#include "dict.h"

#define dict_mut 0.75
#define init_mut 0.6666666666666666

dict_att dict_run_obj ={
        .obj = NULL,
        .get = find,
        .push = add,
        .pop = find_remove,
        .value = value,
        .key = key,
        .item = item,
        .space = space,
        .clear = clear,
};


static inline hash_id hash(char *key)
{
    hash_key id = unique_hash_t(key,dict_run_obj.obj->k_size);
    return id% dict_run_obj.obj->expand;
}

static Variable find(Variable key)
{
    dict *obj = dict_run_obj.obj;
    hash_id id = hash(key);
    Size_t offset = obj->k_size+obj->v_size;
    Current_t current;

    while (id!=obj->expand&&obj->fill[id])
    {
        current = id*offset;
        if(obj->fill[id]!=-1&&memcmp(obj->data+current,key,obj->k_size)==0)
            return obj->data+current+obj->k_size;
        id++;
    }
    if(id == obj->expand)
    {
        id = 0;
        while (obj->fill[id])
        {
            current = id*offset;
            if(obj->fill[id]!=-1&&memcmp(obj->data+current,key,obj->k_size)==0)
                return obj->data+current+obj->k_size;
            id++;
        }
    }
    return NULL;
}

static inline void add(pair_tuple data)
{
    dict *obj = dict_run_obj.obj;
    Size_t offset = obj->k_size+obj->v_size;
    Current_t current;
    Number_t num = obj->expand*dict_mut;
    hash_id key;
    if(num == obj->number)
    {
        Number_t old_expand = obj->expand;
        obj->expand+=num*dict_mut;
        obj->expand=(1+(obj->expand/EXPAND))*EXPAND;
        Variable new_data = malloc(obj->expand*offset);
        Variable local = NULL;
        bit8u *new_fill = calloc(obj->expand,1);
        for (Number_t i = 0; i < old_expand; ++i) {
            if(obj->fill[i]==1)
            {
                local = obj->data+i*offset;
                key = hash(local);
                while (key!=obj->expand&&new_fill[key])
                {
                    key++;
                }
                if(key==obj->expand)
                {
                    key = 0;
                    while (new_fill[key])
                        key++;
                }
                current = key*offset;
                memcpy(new_data+current,local,offset);
                new_fill[key] = 1;
            }
        }

        free(obj->data);
        free(obj->fill);
        obj->data = new_data;
        obj->fill = new_fill;
    }

    key = hash(data.key);
    current = key*offset;
    if(obj->fill[key]==1)
    {
        if (memcmp(obj->data + current, data.key, obj->k_size) == 0)
        {
            memcpy(obj->data + current + obj->k_size, data.value, obj->v_size);
            return;
        }
        key++;
        while (key!=obj->expand&& obj->fill[key]==1)
        {
            current = offset*key;
            if(memcmp(obj->data+current,data.key,obj->k_size)==0)
            {
                memcpy(obj->data+current+obj->k_size,data.value,obj->v_size);
                return;
            }
            key++;
        }
        if(key==obj->expand)
        {
            key = 0;
            while (obj->fill[key]==1)
            {
                current = key*offset;
                if(memcmp(obj->data+current,data.key,obj->k_size)==0)
                {
                    memcpy(obj->data+current+obj->k_size,data.value,obj->v_size);
                    return;
                }
                key++;
            }
        }
    }
    current = key*offset;
    memcpy(obj->data+current,data.key,obj->k_size);
    memcpy(obj->data+current+obj->k_size,data.value,obj->v_size);
    obj->fill[key] = 1;
    obj->number++;
}

static void space(Number_t num)
{
    dict *obj = dict_run_obj.obj;
    Size_t offset = obj->k_size+obj->v_size;
    obj->expand = num*(1+init_mut);
    obj->data = malloc(obj->expand*offset);
    obj->fill = calloc(obj->expand,1);
}

static void find_remove(Variable key)
{
    dict *obj = dict_run_obj.obj;
    hash_id id = hash(key);
    Size_t offset = obj->k_size+obj->v_size;
    Current_t current;
    while (id!=obj->expand&&obj->fill[id])
    {
        current = id*offset;
        if(obj->fill[id]!=-1&&memcmp(obj->data+current,key,obj->k_size)==0)
        {
            obj->fill[id] = -1;
            obj->number--;
        }
        id++;
    }
    if(id == obj->expand)
    {
        id = 0;
        while (obj->fill[id])
        {
            current = id*offset;
            if(obj->fill[id]!=-1&&memcmp(obj->data+current,key,obj->k_size)==0)
            {
                obj->fill[id] = -1;
                obj->number--;
            }
            id++;
        }
    }

}
static Variable key()
{
    dict *obj = dict_run_obj.obj;
    Size_t offset = obj->k_size+obj->v_size;
    Variable res = malloc(obj->k_size*obj->number);
    Current_t current;
    Current_t move = 0;
    for (int i = 0; i < obj->expand; ++i) {
        if(obj->fill[i]==1)
        {
            current = i*offset;
            memcpy(res+move,obj->data+current,obj->k_size);
            move+=obj->k_size;
        }
    }
    return res;
}
static Variable value()
{
    dict *obj = dict_run_obj.obj;
    Size_t offset = obj->k_size+obj->v_size;
    Variable res = malloc(obj->v_size*obj->number);
    Current_t current;
    Current_t move = 0;
    for (int i = 0; i < obj->expand; ++i) {
        if(obj->fill[i]==1)
        {
            current = i*offset;
            memcpy(res+move,obj->data+current+obj->k_size,obj->v_size);
            move+=obj->v_size;
        }
    }
    return res;
}

static Variable item()
{
    dict *obj = dict_run_obj.obj;
    Size_t offset = obj->k_size+obj->v_size;
    Variable res = malloc(offset*obj->number);
    Current_t current;
    Current_t move = 0;
    for (int i = 0; i < obj->expand; ++i) {
        if(obj->fill[i]==1)
        {
            current = i*offset;
            memcpy(res+move,obj->data+current,offset);
            move+=offset;
        }
    }
    return res;
}
static void clear()
{
    if(dict_run_obj.obj->number==0)return;
    free(dict_run_obj.obj->data);
    free(dict_run_obj.obj->fill);
    dict_run_obj.obj->expand = 0;
    dict_run_obj.obj->number = 0;
    dict_run_obj.obj->data = NULL;
    dict_run_obj.obj->fill = NULL;
}