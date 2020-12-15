//
// Created by Calun on 2020/10/27.
//

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

//private functions
Node private_list_get_node(List l, int index);
int private_list_delete_node(List l, Node n);
int private_list_insert_node(List l, Node n, int index);

//Node functions
Node newNode(OBJECT value){
    Node n = malloc(sizeof(struct nodeSTU));
    n->value = value;
    n->front = NULL;
    n->next = NULL;
    return n;
}

int linkNode(Node n1, Node n2){
    n1->next = n2;
    n2->front = n1;
    return 0;
}

int freeNode(Node n)
{
    free(n);
    return 0;
}


//List functions
List newList()
{
    List l = malloc(sizeof(struct listSTU));
    l->head = NULL;
    l->len = 0;
    return l;
}

int list_append(List l, OBJECT value)
{
    Node n = newNode(value);
    if (l->len) {
        linkNode(l->head->front, n);
        linkNode(n, l->head);
    } else {
        l->head = n;
        linkNode(n,n);
    }
    ++(l->len);
    return 0;
}

Node private_list_get_node(List l, int index)
{
    if (index < l->len){
        Node n = l->head;
        for (;index>0; --index) {
            n = n->next;
        }
        return n;
    }else{
        return NULL;
    }
}

OBJECT list_get(List l, int index) {
    Node n = private_list_get_node(l, index);
    if (n == NULL) return 0;        //object的无效取值问题
    else return n->value;
}

int list_index(List l, OBJECT object) {
    Node n = l->head;
    int i = 0;
    do {

        if (n->value == object) return i;
        n = n->next;
        ++i;
    } while (n != l->head);
    return -1; //找不到
}

int private_list_delete_node(List l, Node n)
{
    if(l->len>1){
        if (l->head == n) {
            l->head = n->next;
        }
        linkNode(n->front, n->next);
    } else {
        l->head = NULL;
    }
    --(l->len);
    freeNode(n);
    return 0;
}

int list_delete(List l, int index)
{
    Node n = private_list_get_node(l, index);
    if(n == NULL) return 1; //空索引
    private_list_delete_node(l, n);
    return 0;
}

int private_list_insert_node(List l, Node n, int index)
{
    Node n0;
    // 空列表
    if(!(l->len) && index == 0){
        l->head = n;
        linkNode(n, n);
        ++(l->len);
        return 0;
    }

    n0 = private_list_get_node(l, index);
    if(n0 == NULL) {
        return 1; //无效索引
    }
    linkNode(n0->front, n);
    linkNode(n, n0);
    ++(l->len);
    if(!index){
        l->head = n;
    }
    return 0;
}

int list_insert(List l, OBJECT value, int index)
{
    Node n = newNode(value);
    return private_list_insert_node(l, n, index);
}

int freeList(List l)
{
    Node n0, n;
    if (l->head != NULL){
        n0 = l->head;
        if(l->len>1){
            n = n0->next;
            while (1){
                n = n->next;
                freeNode(n->front);
                if(n==n0) break;
            }
        }
        freeNode(n0);
    }
    free(l);
}

List newListFromArray(OBJECT * objs, int length)
{
    int i;
    List l = newList();
    for (i = 0; i < length; ++i) {
        list_append(l, *(objs + i));
    }
    return l;
}

int printList(List l)
{
    Node n = l->head;
    printf("LEN:%d\nCONTENTS:[", l->len);
    if (l->head != NULL){
        do {
            printf("%f", n->value);
            n = n->next;
            if (n == l->head) break;
            printf(", ");
        }while (1);
    }
    printf("]\n");
    return 0;
}


//ObjList
/**
 * The ObjList is designed for any type of data. So, the type of value point is "void *". It's not recommend to store
 * multiple type value. There is an byte_size attribute in the root of ObjList refer to mark the object size. You can
 * use setObjSize() to set the default object data size in byte. If you don't do it, the default value of byte_size is
 * 0.
 * */

struct STUObjListNode;
typedef struct STUObjListNode *ObjListNode;


struct STUObjListNode{
    ObjListNode next;
    void * value;
};


struct STUObjList{
    ObjListNode head;
    int byte_size;
};


ObjListNode newObjListNode(){
    ObjListNode oln = malloc(sizeof(struct STUObjListNode));
    oln->value = NULL;
    oln->next = NULL;
    return oln;
}


int ObjListNode_link(ObjListNode n1, ObjListNode n2){
    n1->next = n2;
    return 0;
}


int ObjListNode_free(ObjListNode n){
    free(n);
    return 0;
}


ObjList newObjList(){
    ObjList l = malloc(sizeof(struct STUObjList));
    l->head = NULL;
    l->byte_size = 0;
    return l;
}


#define OL_isBlank(l) ((l)->head == NULL ? 1 : 0)
int ObjList_isBlank(ObjList l){
    return OL_isBlank(l);
}


ObjListNode ObjList_private_getFrontNode(ObjList l, ObjListNode node){
    ObjListNode tn = l->head;
    if (l->head == node) return NULL;
    while(tn->next != NULL)
        if (tn->next == node) return tn;
        else tn = tn->next;
    return NULL;
}


ObjListNode ObjList_private_getNodeHandle(ObjList l, int index){
    /**/
    ObjListNode node = l->head;;
    for (; index > 0; --index) {
        node = node->next;
    }
    return node;
}


int ObjList_private_objEqual(ObjList l, void * obj_in_list, void * obj, int byte_size){
    unsigned char *oil = obj_in_list, *o = obj;
    int i;
    for (i = 0; i < byte_size; ++i) {
        if (*oil != *o) {
            return 0;
        }
    }
    return 1;
}


ObjList newObjListFromArray(void * array, int byte_size, int length){
    ObjList l = newObjList();
    ObjListNode n = newObjListNode();
    int i;
    ObjList_setObjSize(l, byte_size);
    n->value = array;
    l->head = n;
    for (i = 1; i < length; ++i) {
        n->next = newObjListNode();
        n = n->next;
        n->value = array+i;
    }
    return l;
}


int ObjList_setObjSize(ObjList l, int size){
    l->byte_size = size;
    return 0;
}


int ObjList_append(ObjList l, void * obj){
    ObjListNode node = newObjListNode(), temp;
    node->value = obj;
    if (OL_isBlank(l)) {
        l->head = node;
    }else{
        temp = l->head;
        while(temp->next!=NULL) temp = temp->next;
        ObjListNode_link(temp, node);
    }
    return 0;
}


int ObjList_insert(ObjList l, void *obj, int index){
    ObjListNode node, new_node, tn;
    if (OL_isBlank(l) && index==0) {
        return ObjList_append(l, obj);
    }else{
        node = l->head;
        for (; index > 0; --index) {
            node = node->next;
            if (node == NULL) return 1;
        }
        new_node = newObjListNode();
        new_node->value = obj;
        ObjListNode_link(new_node, node);
        tn = ObjList_private_getFrontNode(l, node);
        if(tn != NULL){
            ObjListNode_link(tn, new_node);
        }else{
            l->head = new_node;
        }
        return 0;
    }
}


int ObjList_len(ObjList l){
    int len = 0;
    ObjListNode n = l->head;
    while(n != NULL){
        n = n->next;
        ++len;
    }
    return len;
}


int ObjList_delete(ObjList l, int index){
    ObjListNode node = l->head, tn;
    if(OL_isBlank(l)) return 1;
    for (; index > 0; --index) {
        if(node->next != NULL)
            node = node->next;
        else return 1;
    }
    if(node == l->head)
        l->head = node->next;
    else{
        tn = ObjList_private_getFrontNode(l, node);
        ObjListNode_link(tn, node->next);
    }
    ObjListNode_free(node);
    return 0;
}


int ObjList_index(ObjList l, void * obj){
    ObjListNode node;
    int i;
    if (!OL_isBlank(l)){
        node = l->head;
        for (i = 0; node != NULL; node = node->next,++i) {
            if(node->value == obj) return i;
        }
    }
    return -1;
}


int ObjList_find(ObjList l, void * obj){
    return ObjList_bfind(l, obj, l->byte_size);
}


int ObjList_bfind(ObjList l, void * obj, int byte_size){
    int i;
    ObjListNode node;
    if(!OL_isBlank(l)){
        node = l->head;
        for (i = 0; node != NULL; node = node->next, ++i) {
            if (ObjList_private_objEqual(l, node->value, obj, byte_size)) {
                return i;
            }
        }
    }
    return -1;
}


void * ObjList_get(ObjList l, int index){
    ObjListNode node;
    if(!OL_isBlank(l)){
        node = l->head;
        while(index > 0){
            node = node->next;
            --index;
        }
        return node->value;
    }
    return NULL;
}


int ObjList_free(ObjList l){
    ObjListNode node = l->head, temp;
    while(node != NULL){
        temp = node->next;
        ObjListNode_free(node);
        node = temp;
    }
    return 0;
}
//
//int ObjList_deepFree(ObjList l, int (* obj_free)(void *, ...)){
//    ObjListNode node = l->head;
//    while(node != NULL){
//        obj_free(node->value);
//        node = node->next;
//    }
//    return ObjList_free(l);
//}
