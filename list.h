//
// Created by Calun on 2020/10/27.
//
#include "objects.h"

#ifndef WEEK3_LIST_H
#define WEEK3_LIST_H

typedef struct nodeSTU * Node;
typedef struct listSTU *List;

struct nodeSTU{
    OBJECT value;
    Node front;
    Node next;
};

struct listSTU
{
    int len;
    Node head;
};

//Node functions
Node newNode(OBJECT value);
int linkNode(Node n1, Node n2);
int freeNode(Node n);

//List functions
List newList();
int list_append(List l, OBJECT value);
int list_insert(List l, OBJECT value, int index);
int list_delete(List l, int index);
OBJECT list_get(List l, int index);
int freeList(List l);
List newListFromArray(OBJECT * objs, int length);
int list_index(List l, OBJECT object);
int printList(List l);
#endif //WEEK3_LIST_H
