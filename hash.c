//
// Created by xjz on 2022/5/4.
//

#include "hash.h"
static char * summary =  SUMMARY;
static char *summary2 = SUMMARY2;

hash_key unique_hash(char *key)
{
    hash_key hashKey = 0;
    while (*summary)
    {
        hashKey += (*key)*(*summary)+(*summary);
        summary++;
    }
    while(*key)
    {
        hashKey += *key;
        hashKey *= (*key);
        key++;
    }
    summary = SUMMARY;
    return hashKey;
}

hash_key unique_hash_t(char *key,unsigned short bit)
{
    hash_key hashKey = 0;
    while (*summary2)
    {
        hashKey += *summary2;
        hashKey *= *summary2;
        summary2++;
    }
    summary2 = SUMMARY2;
    while(*key&&bit--)
    {
        hashKey += *key;
        hashKey *= (*key);
        key++;
    }
    return hashKey;
}