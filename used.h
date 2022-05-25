//
// Created by xjz on 2022/4/11.
//

#ifndef OBJECT_USED_H
#define OBJECT_USED_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
typedef void* Variable;
typedef void** PVariable;
typedef unsigned char var[0];
#define VARIABLE_SIZE 8

#define swap(a,b) do{ \
   typeof(a) temp = (a); \
   (a) = (b);         \
   (b) = temp;\
}while(0)
// +++++++++++++++++++++++ data structure ++++++++++++++++++++++++++

#define TRUE 1
#define FALSE 0
typedef unsigned short uint16d;
typedef char bit8u;
typedef const void * Variable_const;
typedef unsigned int Size_t;
typedef unsigned int Index_t;
typedef unsigned int Number_t;
typedef unsigned int hash_id;
typedef unsigned long long Local;
typedef unsigned long long Current_t;
typedef void (*Clear)();
typedef _Bool (*Empty)();
typedef Variable (*Delete)(Index_t id);
typedef void (*Pop)();
typedef Variable (*Top)();
typedef void (*Reverse)(Index_t id);
typedef Variable (*Head)();
typedef Variable (*Tail)();
typedef void (*Remove)(Variable value);
typedef Variable (*Get)(Index_t id);
typedef void (*Object_Push)(Variable_const value);
typedef _Bool (*Object_Front_Insert)(Variable_const value);
typedef _Bool (*Object_Back_Insert)(Variable_const value);
typedef void (*Object_Iterator_Insert)(Variable iterator,Variable_const value);
typedef void (*Object_Insert)(Index_t id,Variable_const value);
typedef void (*InitSpace)(Number_t num);
typedef Variable (*Real)();
typedef PVariable (*Areal)();
typedef Variable (*Find_Value)(Variable value);

typedef Variable (*Key)();
typedef Variable (*Value)();
typedef Variable (*Item)();


static void clear();
static unsigned int size();
static _Bool empty();
static Variable delete(Index_t id);
static void pop();
static void reverse(Index_t id);
static Variable head();
static Variable tail();
static Variable top();
static Variable front();
static void remove_value(Variable value);
static void object_insert(Index_t id,Variable_const value);
static _Bool object_front_insert(Variable_const value);
static _Bool object_back_insert(Variable_const value);
static void object_iterator_insert(Variable iterator,Variable_const value);
static void object_push(Variable_const value);
static Variable get(Index_t id);
static void space(Number_t num);
static Variable key();
static Variable value();
static Variable item();
static Variable real();
static PVariable areal();
static Variable find_value(Variable value);

#define ONE_NODE_SIZE 16
typedef struct  __attribute__((packed)) ONE_NODE
{
    Variable data;
    struct ONE_NODE *next;
}ONE_NODE;

#define LIST_NODE_SIZE 8
typedef struct  __attribute__((packed)) LIST_NODE
{
    var data;
    struct LIST_NODE *next;
}LIST_NODE;

#define BLOCK_NODE_SIZE 20
typedef struct __attribute__((packed)) BLOCK
{
    var data;
    unsigned int size;
    struct BLOCK *front;
    struct BLOCK *next;
}BLOCK;


#define Buffer 64
#define Q_Buffer 2
typedef LIST_NODE Stack_Node;
typedef LIST_NODE Queue_Node;
typedef ONE_NODE Link_Node;

#define TWO_NODE_SIZE 24
typedef struct TWO_NODE TWO_NODE;
struct __attribute__((packed)) TWO_NODE
{
    TWO_NODE *front;
    Variable data;
    TWO_NODE *next;
};

typedef struct TREE_NODE TREE_NODE;

#define arg(data) (typeof(data)[]){data}

typedef struct __attribute__((packed)) pair_tuple
{
    Variable key;
    Variable value;
}pair_tuple;
typedef TWO_NODE DLink_Node;
typedef void (*Add)(pair_tuple data);
typedef Variable (*Find)(Variable key);
typedef void (*Find_Remove)(Variable key);
static void add(pair_tuple data);
static Variable find(Variable key);
static void find_remove(Variable key);

#define pair(KType,VType) struct __attribute__((packed)) {typeof(KType) key;typeof(VType) value;}
#define TKey(KType) typeof(KType)
#define TValue(VType) typeof(VType)

// +++++++++++++++++++++++ data structure ++++++++++++++++++++++++++

#endif //OBJECT_USED_H
