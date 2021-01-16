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
    if (n == NULL) return 0;        //When object is null
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
    return -1; // can not find
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
    if(n == NULL) return 1; // null index
    private_list_delete_node(l, n);
    return 0;
}

int private_list_insert_node(List l, Node n, int index)
{
    Node n0;
    // void list
    if(!(l->len) && index == 0){
        l->head = n;
        linkNode(n, n);
        ++(l->len);
        return 0;
    }

    n0 = private_list_get_node(l, index);
    if(n0 == NULL) {
        return 1; // invalid index
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
    return 0;
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


/* private functions header */
ObjListNode ObjList_private_getFrontNode(ObjList l, ObjListNode node);
ObjListNode ObjList_private_getNodeHandle(ObjList l, int index);
ObjListNode ObjList_private_pickOutNode(ObjList l, ObjListNode node);
int ObjList_private_objEqual(ObjList l, void * obj_in_list, void * obj, int byte_size);
int ObjList_private_nodeDistance(ObjListNode n1, ObjListNode n2);
static inline void ObjList_private_sortSwap(ObjListNode *n1, ObjListNode *n2);
ObjListNode ObjList_private_qsort_median3(ObjListNode start, ObjListNode end, int distance, int (* objCompare)(void *, void *));
void ObjList_private_qsort_(ObjList l, ObjListNode start, ObjListNode end, int (* objCompare)(void *, void *));
static inline void ObjList_private_appendNode(ObjList l, ObjListNode node);
static inline void ObjListNode_private_link(ObjListNode n1, ObjListNode n2);
ObjListNode ObjList_private_getRearNode(ObjList l);
/* private functions */


ObjListNode newObjListNode(){
    ObjListNode oln = malloc(sizeof(struct STUObjListNode));
    oln->value = NULL;
    oln->next = NULL;
    return oln;
}


static inline void ObjListNode_private_link(ObjListNode n1, ObjListNode n2){
    n1->next = n2;
}


int ObjListNode_free(ObjListNode n){
    free(n);
    return 0;
}


ObjList newObjList(int byte_size){
    ObjList l = malloc(sizeof(struct STUObjList));
    l->head = NULL;
    l->byte_size = byte_size;
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
    ObjListNode node = l->head;;
    for (; index > 0 && node != NULL; --index) {
        node = node->next;
    }
    return node;
}


ObjListNode ObjList_private_pickOutNode(ObjList l, ObjListNode node){
    ObjListNode front;
    if(node == l->head)
        l->head = node->next;
    else{
        front = ObjList_private_getFrontNode(l, node);
        ObjListNode_private_link(front, node->next);
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


int ObjList_private_nodeDistance(ObjListNode n1, ObjListNode n2){
    int d;
    for (d = 0; n1 != n2; ++d) {
        n1 = n1->next;
        if (n1 == NULL) {
            return -1;
        }
    }
    return d;
}


static inline void ObjList_private_sortSwap(ObjListNode *n1, ObjListNode *n2) {
    ObjListNode temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}


ObjListNode ObjList_private_qsort_median3(ObjListNode start, ObjListNode end, int distance, int (* objCompare)(void *, void *)){
    ObjListNode n1 = start, n2, n3 = end;
    for (n2 = start, distance /= 2; distance > 0; --distance) {
        n2 = n2->next;
    }
    if(objCompare(n1->value, n2->value) > 0) ObjList_private_sortSwap(&n1, &n2);
    if(objCompare(n1->value, n3->value) > 0) ObjList_private_sortSwap(&n1, &n3);
    if(objCompare(n2->value, n3->value) > 0) ObjList_private_sortSwap(&n2, &n3);
    return n2;
}


void ObjList_private_qsort_(ObjList l, ObjListNode start, ObjListNode end, int (* objCompare)(void *, void *)) {
    int distance = ObjList_private_nodeDistance(start, end);
    ObjList fronts = newObjList(0), behind = newObjList(0);
    ObjListNode
            start_front,
            end_behind,
            temp = NULL,        // In most case, temp as an operator point.
            temp2 = NULL,       // In most case, temp as an front point.
            center;

    start_front = ObjList_private_getFrontNode(l, start);

    if (distance == 0) {
        free(fronts);
        free(behind);
        return;
    }

    if (distance == 1) {
        if (objCompare(start->value, end->value) > 0) {
            if(start_front != NULL){
                start_front->next = end;
                start->next = end->next;
                end->next = start;
            }else{
                l->head = end;
                start->next = end->next;
                end->next = start;
            }
        }
        free(fronts);
        free(behind);
        return;
    }

    center = ObjList_private_qsort_median3(start, end, distance, objCompare);
    temp2 = start_front;
    temp = start;
    while (temp != center) {
        // find the first node which should insert to the behind of center.
        if (objCompare(temp->value, center->value) > 0) {
            if (temp2 != NULL) {
                ObjListNode_private_link(temp2,
                                         temp->next);    // pickOutNode() will calculate from the head. So we don't use it.
                temp->next = NULL;
                ObjList_private_appendNode(behind, temp);
                temp = temp2->next;
            } else {
                ObjList_private_pickOutNode(l, temp);
                temp->next = NULL;
                ObjList_private_appendNode(behind, temp);
                temp = l->head;
            }
            continue;
        }
        // normal case
        temp2 = temp;
        temp = temp->next;
    }

    temp2 = center;
    temp = center->next;
    end_behind = end->next;
    while (temp != end_behind) {
        if (objCompare(temp->value, center->value) < 0) {
            ObjListNode_private_link(temp2,
                                     temp->next);    // pickOutNode() will calculate from the head. So we don't use it.
            temp->next = NULL;
            ObjList_private_appendNode(fronts, temp);
            temp = temp2->next;
            continue;
        }
        temp2 = temp;
        temp = temp->next;
    }

    // insert
    //front
    if (!OL_isBlank(fronts)){
        if(start_front == NULL){
            ObjList_private_getRearNode(fronts)->next = l->head;
            l->head = fronts->head;
        }else{
            ObjList_private_getRearNode(fronts)->next = start_front->next;
            start_front->next = fronts->head;
        }
    }
    //behind
    if (!OL_isBlank(behind))
    {
        end = ObjList_private_getRearNode(behind);
        end->next = center->next;
        center->next = behind->head;
    }
    free(fronts);
    free(behind);
    if (start_front==NULL) start = l->head;
    else start = start_front->next;
    if (temp2 != center) end = temp2;
    ObjList_private_qsort_(l, start, center, objCompare);
    ObjList_private_qsort_(l, center, end, objCompare);
}


ObjListNode ObjList_private_getRearNode(ObjList l){
    ObjListNode node = l->head;
    while(node->next != NULL) node = node->next;
    return node;
}


static inline void ObjList_private_appendNode(ObjList l, ObjListNode node){
    ObjListNode temp;
    if (OL_isBlank(l)) {
        l->head = node;
    }else{
        temp = l->head;
        while(temp->next!=NULL) temp = temp->next;
        ObjListNode_private_link(temp, node);
    }
}


ObjList newObjListFromArray(void * array, int byte_size, int length){
    char * b = (char *) array;
    ObjList l = newObjList(byte_size);
    ObjListNode n = newObjListNode();
    int i;
    ObjList_setObjSize(l, byte_size);
    n->value = b;
    l->head = n;
    for (i = 1; i < length; ++i) {
        n->next = newObjListNode();
        n = n->next;
        n->value = b+i*byte_size;
    }
    return l;
}


int ObjList_setObjSize(ObjList l, int size){
    l->byte_size = size;
    return 0;
}


int ObjList_append(ObjList l, void * obj){
    ObjListNode node = newObjListNode();
    node->value = obj;
    ObjList_private_appendNode(l, node);
    return 0;
}


int ObjList_insert(ObjList l, void *obj, int index){
    ObjListNode node, new_node, tn;
    if (ObjList_len(l) == index) {
        return ObjList_append(l, obj);
    }else{
        node = l->head;
        for (; index > 0; --index) {
            node = node->next;
            if (node == NULL) return 1;
        }
        new_node = newObjListNode();
        new_node->value = obj;
        ObjListNode_private_link(new_node, node);
        tn = ObjList_private_getFrontNode(l, node);
        if(tn != NULL){
            ObjListNode_private_link(tn, new_node);
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
    ObjListNode node = ObjList_private_getNodeHandle(l, index);
    node = ObjList_private_pickOutNode(l, node);
    return ObjListNode_free(node);
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
        if (index < 0) return NULL;
        while(index > 0){
            node = node->next;
            if (node == NULL) return NULL;
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
    free(l);
    return 0;
}


int ObjList_deepFree(ObjList l, int (* obj_free)(void *, ...)){
    ObjListNode node = l->head;
    while(node != NULL){
        obj_free(node->value);
        node = node->next;
    }
    return ObjList_free(l);
}


int ObjList_sort(ObjList l, int (* objCompare)(void *, void *)){
    ObjList_private_qsort_(l, l->head, ObjList_private_getRearNode(l), objCompare);
    return 0;
}


void * ObjList_toArray(ObjList l) {
    int len = ObjList_len(l), index = 0, i;
    char *array;
    ObjListNode node;
    if(!len) return NULL;
    node = l->head;
    array = (char *) malloc(len * l->byte_size);
    while(node != NULL){
        for (i = 0; i < l->byte_size, ++i;) {
            array[i+index*l->byte_size] = *((char *)(node->value) + i);
        }
        ++index;
        node = node->next;
    }
    return (void *)array;
}



/* Array List Part*/
struct ArrayListSTU{
    void * array;
    int len;
    int allocated;
    int byte_size;
};


ArrayList newArrayList(int byte_size){
    ArrayList l = malloc(sizeof(struct ArrayListSTU));
    l->len= 0;
    l->allocated = 4;
}


ArrayList newArrayListFromArray(void * array, int byte_size, int length){

}


int ArrayList_setObjSize(ArrayList l, int size){


}


int ArrayList_append(ArrayList l, void * obj){

}


int ArrayList_insert(ArrayList l, void * obj, int index){

}


int ArrayList_delete(ArrayList l, int index){

}


int ArrayList_index(ArrayList l, void * obj){

}


int ArrayList_find(ArrayList l, void * obj){

}


int ArrayList_bfind(ArrayList l, void * obj, int byte_size){

}


void * ArrayList_get(ArrayList l, int index){

}


int ArrayList_free(ArrayList l){

}


int ArrayList_isBlank(ArrayList l){

}


int ArrayList_len(ArrayList l){

}


int ArrayList_deepFree(ArrayList l, int (* obj_free)(void *, ...)){

}


int ArrayList_sort(ArrayList l, int (* objCompare)(void *, void *)){

}


void * ArrayList_toArray(ArrayList l){

}
