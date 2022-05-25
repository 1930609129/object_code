//
// Created by xjz on 2022/5/9.
//

#ifndef OBJECT_ALM_H
#define OBJECT_ALM_H
#include "q_stack.h"
#define __mut__(data,v,num_){ \
    typeof(num_) num = num_;                            \
    while(num)                  \
    {                           \
        num--;\
        data[num] *= v;                        \
    }\
}

#define __add__(data,v,num_){ \
    typeof(num_) num = num_;                            \
    while(num)                  \
    {                           \
        num--;\
        data[num] += v;                        \
    }\
}

#define __div__(data,v,num_){ \
    typeof(num_) num = num_;                            \
    while(num)                  \
    {                           \
        num--;\
        data[num] /= v;                        \
    }                                    \
}

#define __sub__(data,v,num_){ \
    typeof(num_) num = num_;                            \
    while(num)                  \
    {                           \
        num--;\
        data[num] -= v;                        \
    }                                   \
}

#define __v_add__(data,v,num_){ \
    typeof(num_) num = num_;      \
    while(num)                    \
    {                             \
        num--;                    \
        data[num]+=v[num];\
    }\
}

#define __v_sub__(data,v,num_){ \
    typeof(num_) num = num_;      \
    while(num)                    \
    {                             \
        num--;                    \
        data[num]-=v[num];\
    }\
}

#define __v_div__(data,v,num_){ \
    typeof(num_) num = num_;      \
    while(num)                    \
    {                             \
        num--;                    \
        data[num]/=v[num];\
    }\
}

#define __v_mut__(data,v,num_){ \
    typeof(num_) num = num_;      \
    while(num)                    \
    {                             \
        num--;                    \
        data[num]*=v[num];\
    }\
}

#define order_max <
#define order_min >

#define __sort__(data,num,order) do{ \
    int i,j;                   \
    int left = 0,right = (num)-1;\
    Address obj = q_stack_run_obj.obj;                           \
    q_stack(int[2],s_);\
    q_stack_run(s_);                \
    q_stack_run_obj.push((int[2]){left,right});     \
    typeof(data[0]) middle;                               \
    while(s_.number)            \
    {                          \
        int *p2 = q_stack_run_obj.top();     \
        left = i = p2[0];             \
        right = j = p2[1];     \
        middle = data[(left+right)/2];                       \
        q_stack_run_obj.pop();\
        do{                    \
            while((data[i] order middle) && (i<right)) \
                i++;           \
            while(!(data[j] order middle) && data[j] != middle && (j>left)) \
                j--;           \
            if(i<=j)           \
            {                  \
                swap(data[i],data[j]);              \
                i++;           \
                j--;\
            }\
        }while(i<=j);           \
        if(right>i) \
            q_stack_run_obj.push((int[2]){i,right});\
        if(left<j)\
            q_stack_run_obj.push((int[2]){left,j});\
    }\
    q_stack_run_obj.obj = obj;\
}while(0)
//
#define __find__(var,stop_con,value)({ \
     Size_t offset = sizeof(var.data);                               \
     Variable data = *(void**)((void*)&var.data+offset-8);                                \
     Variable local = NULL;            \
     char flag = 0;                    \
     Number_t num;                     \
     Size_t type_size;\
     if(sizeof(stop_con)==4)      \
     {                                 \
          typeof(stop_con) stop_num = stop_con;                      \
          type_size =  *(Size_t*)((void*)&(var.data)+sizeof(var)-4);                            \
          local = data;                             \
          while(stop_num--)            \
          {                            \
                if(memcmp(local,arg(value),type_size)==0)                 \
                {                      \
                    flag = 1;\
                    break;              \
                }\
                local+=type_size;\
          }                            \
          if(flag==0)                     \
            local = NULL;\
     }\
     else if(offset == LIST_NODE_SIZE)       \
     {                                 \
        type_size = *(Size_t*)((void*)&(var.data)+sizeof(var)-4);\
        Number_t end = var.number%Buffer;                            \
        num = Buffer;\
        while(data!=(stop_con))              \
        {                                  \
        \
            Variable temp = *(void**)(data+offset-8);                           \
            if(temp==NULL)       \
            {                      \
                if(end) num = end;     \
            }\
            local = (data+offset);    \
            for(int i=0;i<num;i++)   \
            {                           \
                if(memcmp(local,arg(value),type_size)==0)                \
                {                      \
                    flag = 1;\
                    break;\
                }                      \
                local+=type_size;\
            }                          \
            if(flag)                   \
                break;\
            local = NULL;                           \
            data = temp;                           \
        }                                  \
        \
     }                                  \
     else if(offset == BLOCK_NODE_SIZE) \
     {                                 \
        type_size = *(Size_t*)((void*)&(var.data)+sizeof(var)-4);                \
        while(data!=(stop_con))          \
        {                              \
            num = *(Number_t*)(data);                          \
            local = (data+offset);                           \
            for(int i=0;i<num;i++)     \
            {                          \
                if(memcmp(local,arg(value),type_size)==0)                \
                {                      \
                    flag = 1;\
                    break;\
                }                      \
                local+=type_size;\
            }                          \
            if(flag)                   \
                break;\
            local = NULL;                          \
            data = *(void**)(data+offset-8);\
        }\
     }                                 \
                                       \
     else if(offset == TWO_NODE_SIZE || offset == ONE_NODE_SIZE)  \
     {                                 \
        Variable temp = (void*)value;                               \
        while(data!=(stop_con))          \
        {                              \
            Variable v =  *(void**)(data);                          \
            if(v==temp)      \
            {                          \
                local = v;\
                break;\
            }                          \
                                       \
            data = *(void**)(data+8);                               \
        }\
     }                                 \
     \
     local;                                        \
})

#endif //OBJECT_ALM_H