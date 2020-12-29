//
// Created by Calun on 2020/10/27.
//
#include "objects.h"

#ifndef WEEK3_QUEUE_H
#define WEEK3_QUEUE_H


struct ArrayQueueRecord
{
    int head;
    int length;
    int max_length;
    void **value;
};
typedef struct ArrayQueueRecord *ArrayQueue;
//typedef struct ArrayQueueRecord ArrayQueueRecord;
ArrayQueue newArrayQueue(int max_length);
ArrayQueue newArrayQueueFromArray(void *a, int length, int max_length, int byte_size);
int ArrayQueue_add(ArrayQueue q, void *obj);
void * ArrayQueue_pop(ArrayQueue q);
int ArrayQueue_index(ArrayQueue q, void *obj);
void * ArrayQueue_get(ArrayQueue q, int index);
int ArrayQueue_len(ArrayQueue q);
int ArrayQueue_insert(ArrayQueue q, void *obj, int index);
int ArrayQueue_isBlank(ArrayQueue q);
void * ArrayQueue_head(ArrayQueue q);


struct STUListQueue;
typedef struct STUListQueue *ListQueue;
ListQueue newListQueue();
ListQueue newListQueueFromArray(void * array, int data_size, int length);
int ListQueue_add(ListQueue q, void * obj);
int ListQueue_insert(ListQueue q, void * obj, int index);
int ListQueue_index(ListQueue q, void * obj);
int ListQueue_delete(ListQueue q, int index);
int ListQueue_pop(ListQueue q);
void * ListQueue_head(ListQueue q);
void * ListQueue_get(ListQueue q, int index);
int ListQueue_free(ListQueue q);
int ListQueue_find(ListQueue q, void * obj);
int ListQueue_bfind(ListQueue q, void * obj, int byte_size);
int ListQueue_isBlank(ListQueue q);
int ListQueue_len(ListQueue q);



#endif //WEEK3_QUEUE_H
