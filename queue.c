//
// Created by Calun on 2020/10/27.
//

#include <stdlib.h>
#include "queue.h"
#include <stdio.h>


Queue newQueue(int max_lenght)
{
    Queue q = (Queue) malloc(sizeof(struct QueueRecord));
    q->MAX_LENGTH = max_lenght;
    q->HEAD = 0;
    q->REAR = -1;
    q->LENGTH = 0;
    q->OBJECTS = (OBJECT *)malloc(sizeof(OBJECT)*max_lenght);
    return q;
}


Queue newQueueFromArray(OBJECT *a, int lenght, int max_lenght)
{
    if(max_lenght>=lenght){
        Queue q = newQueue(max_lenght);
        int i;
        for(i=0;i<lenght;++i) addObjToQueue(q, *(a+i));
        return q;
    }else{
        return NULL;
    }
}


void printQueue(Queue q)
{
    int i;
    printf("Information of Queue:\nHEAD:%d\nREAR:%d\nLENGHT:%d\nMAX_LENGHT:%d\nOBJECTS:[", q->HEAD, q->REAR, q->LENGTH, q->MAX_LENGTH);
    for(i=q->HEAD;i<=q->REAR; ++i)
    {
        if(i-q->HEAD) printf(", ");
        printf("%f", *(q->OBJECTS+ (i%q->MAX_LENGTH)));
    }
    putchar(']');
    putchar('\n');
}

int addObjToQueue(Queue q, OBJECT obj)
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


int deleteObjFromQueue(Queue q)
{
    if(q->LENGTH)
    {
        ++q->HEAD;
        --q->LENGTH;
        return 0;
    }else{
        printf("ERROR: There is an empty Queue!");
        return 1;
    }
    return -1;
}

int indexObjFormQueue(Queue q, OBJECT obj)
{
    int i;
    for(i=q->HEAD;i<=q->REAR; ++i)
    {
        if(*(q->OBJECTS+ (i%q->MAX_LENGTH)) == obj) return (i - q->HEAD);
    }
    return -1;
}

OBJECT getFromQueue(Queue q, int index)
{
    return *(q->OBJECTS+((q->HEAD+index) % q->MAX_LENGTH));
}