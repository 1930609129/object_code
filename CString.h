//
// Created by xjz on 2022/5/4.
//

#ifndef OBJECT_CSTRING_H
#define OBJECT_CSTRING_H
#include "used.h"
#define STR_BUFFER 256
#define STR_A_BUF 64
#define CString(varname) CString varname = {.len = 0,.str_front = NULL};\
    varname.data.next = NULL;                                          \
    varname.data.current = 0;                                          \
    varname.tail = &varname.data

#define CString_run(object) ({CString_run_obj.obj = &object;&CString_run_obj;})
typedef unsigned long long StrIndex;
typedef struct String String;
typedef void *cstring;
typedef unsigned int str_block;
#define STRING_SIZE 12
struct __attribute__((packed)) String
{
    var data;
    str_block current;
    String *next;
};

#define LSTRING_SIZE 16
typedef struct __attribute__((packed)) LString{
    cstring *data;
    struct LString *next;
} LString;

#define LString_free(obj) do{ \
    LString *data = obj.next; \
    LString *node;                          \
    while(data)               \
    {                         \
        node = data;\
        data = data->next;                      \
        for(int i=0;i<STR_A_BUF;i++)        \
            free(node->data[i]);\
        free(node->data);     \
        free(node);\
    }                         \
    obj.next = NULL;\
}while(0)

#define String_free(obj) do{ \
    String *data = obj.next; \
    String *node;            \
    while(data)              \
    {                        \
        node = data;         \
        data = data->next;   \
        free(node);\
    }\
}while(0)

typedef unsigned long long StrLen;
typedef struct CString CString;
typedef void (*CString_Object)(CString *address);
void CString_init(CString *address);
typedef void (*Insert)(StrIndex index,cstring str);
typedef void (*Front_Insert)(cstring str);
typedef void (*Back_Insert)(cstring str);
typedef LString (*Split)(cstring delimiter);
typedef String (*Replace)(cstring str,cstring resp,unsigned int num);
typedef cstring (*Find_Str)(cstring str);
static void insert(StrIndex index,cstring str);
static void front_insert(cstring str);
static void back_insert(cstring str);
static cstring find_str(cstring str);
static LString split(cstring delimiter);
static String replace(cstring str,cstring resp,unsigned int num);


struct __attribute__((packed)) CString {
    String data;
    String *tail;
    String *str_front;
    StrLen len;
};

typedef struct __attribute__((packed)) {
    CString *obj;
    Insert insert;
    Object_Push push;
    Front_Insert front_insert;
    Back_Insert back_insert;
    Split split;
    Replace replace;
    Find_Str find;
    Real real;
    Clear clear;
}CString_att;

extern CString_att CString_run_obj;

#endif //OBJECT_CSTRING_H