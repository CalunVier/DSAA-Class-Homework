//
// Created by Calun on 2020/10/27.
//

#include <stdlib.h>
#include "queue.h"
#include <stdio.h>


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