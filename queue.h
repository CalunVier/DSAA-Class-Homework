//
// Created by Calun on 2020/10/27.
//
#include "objects.h"

#ifndef WEEK3_QUEUE_H
#define WEEK3_QUEUE_H


struct ArrayQueueRecord
{
    int HEAD;
    int REAR;
    int LENGTH;
    int MAX_LENGTH;
    OBJECT *OBJECTS;
};
typedef struct ArrayQueueRecord *ArrayQueue;
//typedef struct ArrayQueueRecord ArrayQueueRecord;
ArrayQueue newArrayQueue(int max_length);
ArrayQueue newArrayQueueFromArray(OBJECT *a, int lenght, int max_lenght);
void ArrayQueue_print(ArrayQueue q);
int ArrayQueue_add(ArrayQueue q, OBJECT obj);
int ArrayQueue_pop(ArrayQueue q);
int ArrayQueue_index(ArrayQueue q, OBJECT obj);
OBJECT ArrayQueue_get(ArrayQueue q, int index);


struct STUListQueue;
typedef struct STUListQueue *ListQueue;
ListQueue newListQueue();
ListQueue newListQueueFromArray(void * array, int data_size, int length);
int ListArray_add(ListQueue q, void * obj);
int ListQueue_insert(ListQueue q, void * obj, int index);
int ListArray_index(ListQueue q, void * obj, int data_size);
int ListArray_delete(ListQueue q, int index);
void ListQueue_pop(ListQueue q);
void * ListQueue_head(ListQueue q);
void * ListQueue_get(ListQueue q, int index);
void * ListQueue_free(ListQueue q);

#endif //WEEK3_QUEUE_H
