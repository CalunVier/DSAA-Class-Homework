//
// Created by Calun on 2020/10/27.
//
#include "objects.h"

#ifndef WEEK3_QUEUE_H
#define WEEK3_QUEUE_H


struct QueueRecord
{
    int HEAD;
    int REAR;
    int LENGTH;
    int MAX_LENGTH;
    OBJECT *OBJECTS;
};
typedef struct QueueRecord *Queue;
//typedef struct QueueRecord QueueRecord;
Queue newQueue(int max_lenght);
Queue newQueueFromArray(OBJECT *a, int lenght, int max_lenght);
void printQueue(Queue q);
int addObjToQueue(Queue q, OBJECT obj);
int deleteObjFromQueue(Queue q);
int indexObjFormQueue(Queue q, OBJECT obj);
OBJECT getFromQueue(Queue q, int index);

#endif //WEEK3_QUEUE_H
