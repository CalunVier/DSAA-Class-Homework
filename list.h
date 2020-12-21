//
// Created by Calun on 2020/10/27.
//
//#include "objects.h"

#ifndef WEEK3_LIST_H
#define WEEK3_LIST_H
#define OBJECT float
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


//ObjList(Single List)
struct STUObjList;
typedef struct STUObjList *ObjList;
ObjList newObjList();
ObjList newObjListFromArray(void * array, int byte_size, int length);
int ObjList_setObjSize(ObjList l, int size);
int ObjList_append(ObjList l, void * obj);
int ObjList_insert(ObjList l, void * obj, int index);
int ObjList_delete(ObjList l, int index);
int ObjList_index(ObjList l, void * obj);
int ObjList_find(ObjList l, void * obj);
int ObjList_bfind(ObjList l, void * obj, int byte_size);
void * ObjList_get(ObjList l, int index);
int ObjList_free(ObjList l);
int ObjList_isBlank(ObjList l);
int ObjList_len(ObjList l);
int ObjList_deepFree(ObjList l, int (* obj_free)(void *, ...));
int ObjList_sort(ObjList l, int (* objCompare)(void *, void *));

#endif //WEEK3_LIST_H
