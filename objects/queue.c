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
    q->MAX_LENGTH = max_length;
    q->HEAD = 0;
    q->REAR = -1;
    q->LENGTH = 0;
    q->OBJECTS = (OBJECT *)malloc(sizeof(OBJECT) * max_length);
    return q;
}


ArrayQueue newArrayQueueFromArray(OBJECT *a, int lenght, int max_lenght)
{
    if(max_lenght>=lenght){
        ArrayQueue q = newArrayQueue(max_lenght);
        int i;
        for(i=0;i<lenght;++i) ArrayQueue_add(q, *(a + i));
        return q;
    }else{
        return NULL;
    }
}


void ArrayQueue_print(ArrayQueue q)
{
    int i;
    printf("Information of ArrayQueue:\nHEAD:%d\nREAR:%d\nLENGHT:%d\nMAX_LENGHT:%d\nOBJECTS:[", q->HEAD, q->REAR, q->LENGTH, q->MAX_LENGTH);
    for(i=q->HEAD;i<=q->REAR; ++i)
    {
        if(i-q->HEAD) printf(", ");
        printf("%f", *(q->OBJECTS+ (i%q->MAX_LENGTH)));
    }
    putchar(']');
    putchar('\n');
}

int ArrayQueue_add(ArrayQueue q, OBJECT obj)
{
    if(q->LENGTH < q->MAX_LENGTH)
    {
        ++q->REAR;
        *(q->OBJECTS+(q->REAR % q->MAX_LENGTH)) = obj;
        ++q ->LENGTH;
        return 0;
    }else{
        printf("ERROR: No more memory to add the object!\n");
        return 1;
    }
    return -1;
}


int ArrayQueue_pop(ArrayQueue q)
{
    if(q->LENGTH)
    {
        ++q->HEAD;
        --q->LENGTH;
        return 0;
    }else{
        printf("ERROR: There is an empty ArrayQueue!");
        return 1;
    }
    return -1;
}

int ArrayQueue_index(ArrayQueue q, OBJECT obj)
{
    int i;
    for(i=q->HEAD;i<=q->REAR; ++i)
    {
        if(*(q->OBJECTS+ (i%q->MAX_LENGTH)) == obj) return (i - q->HEAD);
    }
    return -1;
}

OBJECT ArrayQueue_get(ArrayQueue q, int index)
{
    return *(q->OBJECTS+((q->HEAD+index) % q->MAX_LENGTH));
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
