//
// Created by Calun on 2020/10/27.
//

#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include "list.h"


ArrayQueue newArrayQueue(int max_length)
{
    ArrayQueue q = (ArrayQueue) malloc(sizeof(struct ArrayQueueRecord));
    q->max_length = max_length;
    q->head = 0;
    q->length = 0;
    q->value = (void *)malloc(sizeof(void *) * max_length);
    return q;
}


ArrayQueue newArrayQueueFromArray(void *a, int length, int max_length, int byte_size)
{
    char * b = a;
    if(max_length>=length){
        ArrayQueue q = newArrayQueue(max_length);
        int i;
        for(i=0;i<length;++i) ArrayQueue_add(q, b + i * byte_size);
        return q;
    }else{
        return NULL;
    }
}


/* ArrayQueue private*/
static inline int ArrayQueue_private_index2position(ArrayQueue q, int index){
    if(index >= 0) {
        return (q->head + index) % q->max_length;
    }else{
        return q->max_length - 1 - ((-index-1) % q->max_length);
    }
}

/* ArrayQueue private end*/


int ArrayQueue_len(ArrayQueue q){
    return q->length;
}


int ArrayQueue_add(ArrayQueue q, void *obj)
{
    if(q->length < q->max_length){
        /* length is 1 greater than index */
        q->value[(q->head + q->length) % q->max_length] = obj;
        ++(q->length);
        return 0;
    }else{
        /*ERROR: No more memory to add the object!*/
        return 1;
    }
}


void * ArrayQueue_pop(ArrayQueue q)
{
    void * value = NULL;
    if(q->length)
    {
        value = q->value[q->head];
        q->head = (q->head + 1) % q->max_length;
        --q->length;
    }else{
        /*ERROR: There is an empty ArrayQueue!*/
    }
    return value;
}

int ArrayQueue_index(ArrayQueue q, void *obj)
{
    /* todo: need to be fix */
    int i;
    return -1;
}

void * ArrayQueue_get(ArrayQueue q, int index)
{
    /* The index is relative index for head, not for value[0]! */
    if(index < q->length){
        return q->value[(q->head + index) % q->max_length];
    }else{
        return NULL;
    }
}


int ArrayQueue_insert(ArrayQueue q, void *obj, int index){
    int p;
    if (q->length < q->max_length) {
        p = q->length;
        for (; p > index; --p) {
            q->value[ArrayQueue_private_index2position(q, p)] = q->value[ArrayQueue_private_index2position(q, p-1)];
        }
        q->value[ArrayQueue_private_index2position(q, index)] = obj;
        ++q->length;
        return 0;
    }else{
        return 1;
    }
}


int ArrayQueue_isBlank(ArrayQueue q){
    return q->length? 0 : 1;
}


void * ArrayQueue_head(ArrayQueue q){
    return ArrayQueue_get(q, 0);
}


//ListQueue
struct STUListQueue{
    ObjList list;
};


ListQueue newListQueue(){
    ObjList l = newObjList(0);
    ListQueue lq = malloc(sizeof(struct STUListQueue));
    lq->list = l;
    return lq;
}


ListQueue newListQueueFromArray(void * array, int data_size, int length){
    ObjList l = newObjListFromArray(array, data_size, length);
    ListQueue lq = malloc(sizeof(struct STUListQueue));
    lq->list = l;
    return lq;
}


int ListQueue_add(ListQueue q, void * obj){
    return ObjList_append(q->list, obj);
}


int ListQueue_insert(ListQueue q, void * obj, int index){
    return ObjList_insert(q->list, obj, index);
}


int ListQueue_index(ListQueue q, void * obj){
    return ObjList_index(q->list, obj);
}


int ListQueue_delete(ListQueue q, int index){
    return ObjList_delete(q->list, index);
}


int ListQueue_pop(ListQueue q){
    return ObjList_delete(q->list, 0);
}


void * ListQueue_head(ListQueue q){
    return ObjList_get(q->list, 0);
}


void * ListQueue_get(ListQueue q, int index){
    return ObjList_get(q->list, index);
}


int ListQueue_free(ListQueue q){
    ObjList_free(q->list);
    free(q);
    return 0;
}


int ListQueue_find(ListQueue q, void * obj){
    return ObjList_find(q->list, obj);
}


int ListQueue_bfind(ListQueue q, void * obj, int byte_size){
    return ObjList_bfind(q->list, obj, byte_size);
}


int ListQueue_isBlank(ListQueue q){
    return ObjList_isBlank(q->list);
}


int ListQueue_len(ListQueue q){
    return ObjList_len(q->list);
}
