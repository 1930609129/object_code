//
// Created by xjz on 2022/5/4.
//

#include "CString.h"

CString_att CString_run_obj = {
    .obj = NULL,
    .replace = replace,
    .find = find_str,
    .insert = insert,
    .back_insert = back_insert,
    .front_insert = front_insert,
    .split = split,
    .push = object_push,
    .clear = clear,
    .real = real
};

static void insert(StrIndex index,cstring str)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;
    StrLen all_size = 0;
    String *front = &obj->data;
    while (data)
    {
        all_size+=data->current;
        if(all_size>=index)
            break;
        front = data;
        data = data->next;
    }
    if(data)
    {
        StrLen len = strlen(str);
        index = index-(all_size-data->current);
        str_block offset = data->current-index;
        Variable temp = malloc(offset);
        memcpy(temp,data->data+STRING_SIZE+index,offset);
        if(data->current+len>=STR_BUFFER)
        {
            data = realloc(data,data->current+STRING_SIZE+len+1);
            memcpy(data->data+STRING_SIZE+index,str,len);
            memcpy(data->data+STRING_SIZE+index+len,temp,offset);
            memset(data->data+STRING_SIZE+index+len+offset,0,1);
            data->current+=len;
            front->next = data;
            obj->len+=len;
        } else
        {
            memcpy(data->data+STRING_SIZE+index,str,len);
            memcpy(data->data+STRING_SIZE+index+len,temp,offset);
            data->current+=len;
            obj->len+=len;
        }
        free(temp);
    }
}
static void front_insert(cstring str)
{

    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;
    if(data)
    {
        StrLen len = strlen(str);
        Variable temp = malloc(data->current);
        memcpy(temp,data->data+STRING_SIZE,data->current);
        if(data->current+len>=STR_BUFFER)
        {
            data = realloc(data,data->current+STRING_SIZE+len+1);
            memcpy(data->data+STRING_SIZE,str,len);
            memcpy(data->data+STRING_SIZE+len,temp,data->current);
            data->current+=len;
            obj->data.next = data;
            obj->len+=len;
        } else
        {
            memcpy(data->data+STRING_SIZE,str,len);
            memcpy(data->data+STRING_SIZE+len,temp,data->current);
            data->current+=len;
            obj->len+=len;
        }
        free(temp);
    }
}
static void back_insert(cstring str)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->tail;
    if(data!=&obj->data)
    {
        StrLen len = strlen(str);
        if(data->current+len>=STR_BUFFER)
        {
            data = realloc(data,data->current+STRING_SIZE+len+1);
            memcpy(data->data+STRING_SIZE+data->current,str,len);
            data->current+=len;
            obj->len+=len;
            obj->str_front->next = data;
        } else
        {
            memcpy(data->data+STRING_SIZE+data->current,str,len);
            data->current+=len;
            obj->len+=len;
        }
    }
}

static void object_push(Variable_const value)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->tail;
    String *node;
    StrLen len = strlen(value);
    if(obj->str_front)
    {
        if(data->current+len<STR_BUFFER)
        {
            memcpy(data->data+data->current+STRING_SIZE,value,len);
            data->current+=len;
            obj->len+=len;
        } else
        {
            data = realloc(data,data->current+STRING_SIZE+len+1);
            memcpy(data->data+data->current+STRING_SIZE,value,len);
            data->current+=len;
            obj->len+=len;
            obj->str_front->next = data;
            obj->str_front = data;
            node = calloc(STR_BUFFER+STRING_SIZE,1);
            data->next = node;
            obj->tail = node;
        }
    } else
    {
        if(len<STR_BUFFER)
        {
            node = calloc(STR_BUFFER+STRING_SIZE,1);
            node->current = len;
            obj->len+=len;
        } else
        {
            node = malloc(len+STRING_SIZE+1);
            node->current = len;
            obj->len+=len;
        }
        memcpy(node->data+STRING_SIZE,value,len);
        obj->str_front = data;
        node->next = NULL;
        data->next = node;
        obj->tail = node;
    }
}

static cstring find_str(cstring str)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;

    while (data)
    {
        cstring local;
        if((local = strstr(data->data+STRING_SIZE,str)))
        {
            return local;
        }
        data = data->next;
    }
    return NULL;
}
static LString split(cstring delimiter)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;
    StrLen len = strlen(delimiter);
    Index_t id = 0;
    LString res = {NULL,NULL};
    cstring temp;
    LString *node;
    LString *tail = &res;
    while (data)
    {
        static unsigned short str_buf =  STR_A_BUF*8;
        cstring local = data->data+STRING_SIZE;
        cstring str;
        while ((str= strstr(local,delimiter)))
        {
            temp = calloc(str-local+1,1);
            memcpy(temp,local,str-local);
            local = str+len;
            if(id%STR_A_BUF==0)
            {
                node = malloc(LSTRING_SIZE);
                node->data = calloc(str_buf,1);
                node->next = NULL;
                tail->next = node;
                tail = node;
                id = 0;
            }
            tail->data[id++] = temp;
        }
        data = data->next;
        if(data==NULL)
        {
            if(local)
            {
                len = strlen(local);
                temp = calloc(len+1,1);
                memcpy(temp,local,len);
                if(id%STR_A_BUF==0)
                {
                    node = malloc(LSTRING_SIZE);
                    node->data = calloc(str_buf,1);
                    node->next = NULL;
                    tail->next = node;
                    tail = node;
                    id = 0;
                }
                tail->data[id++] = temp;
            }
        }
    }
    return res;
}
static String replace(cstring str,cstring resp,unsigned int num)
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;
    String res = {.current=0,.next=NULL};
    String *tail = &res;
    String *node;
    unsigned short Slen = strlen(str);
    unsigned short Rlen = strlen(resp);
    short dev = Rlen-Slen;
    Index_t id = 0;
    char flag = -1;
    if(num)
    {
        flag = 1;
    }
    while (data)
    {
        cstring local = data->data+STRING_SIZE;
        cstring cstr;
        unsigned short *offset = malloc(data->current*2);
        while ((cstr = strstr(local,str)))
        {
            offset[id++] = cstr-(void*)(data->data+STRING_SIZE);
            if(flag==1&&!--num)
            {
                flag = 0;
                break;
            }
            local = cstr+Slen;
        }
        if(id)
        {
            local = data->data+STRING_SIZE;
            str_block current = (dev)*id+data->current;
            node = calloc(current+STRING_SIZE+1,1);
            node->current = offset[0];
            for (int i = 0; i < id; ++i) {
                node->current = offset[i]+(i*dev);
                strcpy((char *)(node->data+STRING_SIZE+node->current),resp);
            }
            id-=1;
            node->current = offset[0];
            for (int i = 0; i < id; ++i) {
                node->current = offset[i]+(i*dev);
                memcpy(node->data+STRING_SIZE+node->current+Rlen,
                       local+offset[i]+Slen,offset[i+1]-offset[i]-Slen);
            }
            if(offset[0]!=0)
            {
                memcpy(node->data+STRING_SIZE,
                       local,offset[0]);
            }
            if(offset[id]+Slen!=data->current)
            {
                node->current = offset[id]+(id*dev);
                memcpy(node->data+STRING_SIZE+node->current+Rlen,
                       local+offset[id]+Slen,data->current-offset[id]-Slen);
            }
            tail->next = node;
            tail = node;

        } else
        {
            node = malloc(data->current+1+STRING_SIZE);
            memcpy(node->data+STRING_SIZE,local,data->current);
            node->next = NULL;
            node->current = data->current;
            tail->next = node;
            tail = node;
        }
        id = 0;
        free(offset);
        if(flag==0)
            break;
        data = data->next;
    }
    return res;
}

static Variable real()
{
    CString *obj = CString_run_obj.obj;
    Variable res = malloc(obj->len+1);
    String *data = obj->data.next;
    StrLen current = 0;
    while (data)
    {
        memcpy(res+current,data->data+STRING_SIZE,data->current);
        current+=data->current;
        data = data->next;
    }
    return res;
}

static void clear()
{
    CString *obj = CString_run_obj.obj;
    String *data = obj->data.next;
    while (data)
    {
        String *node = data;
        data = data->next;
        free(node);
    }
    obj->len = 0;
    obj->data.next = NULL;
    obj->tail = &obj->data;
    obj->str_front = NULL;
}