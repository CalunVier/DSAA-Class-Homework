//
// Created by Calun on 2020/10/27.
//
//#include "objects.h"

#ifndef WEEK3_LIST_H
#define WEEK3_LIST_H
typedef float OBJECT;
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
struct STUObjListIterator;
typedef struct STUObjListIterator *ObjListIterator;
ObjList newObjList(int byte_size);
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
void * ObjList_toArray(ObjList l);

ObjListIterator ObjList_getIterator(ObjList l);
void * ObjListIterator_next(ObjListIterator oli);
int * ObjListIterator_reset(ObjListIterator oli);
int * ObjListIterator_set(ObjListIterator oli, int index);



/* ArrayList Part */
struct ArrayListSTU;
typedef struct ArrayListSTU *ArrayList;
ArrayList newArrayList(int byte_size);
ArrayList newArrayListFromArray(void * array, int byte_size, int length);
int ArrayList_setObjSize(ArrayList l, int size);
int ArrayList_append(ArrayList l, void * obj);
int ArrayList_insert(ArrayList l, void * obj, int index);
int ArrayList_delete(ArrayList l, int index);
int ArrayList_index(ArrayList l, void * obj);
int ArrayList_find(ArrayList l, void * obj);
int ArrayList_bfind(ArrayList l, void * obj, int byte_size);
void * ArrayList_get(ArrayList l, int index);
int ArrayList_free(ArrayList l);
int ArrayList_isBlank(ArrayList l);
int ArrayList_len(ArrayList l);
int ArrayList_deepFree(ArrayList l, int (* obj_free)(void *, ...));
int ArrayList_sort(ArrayList l, int (* objCompare)(void *, void *));
void * ArrayList_toArray(ArrayList l);

#endif //WEEK3_LIST_H
