//
// Created by Calun on 2020/10/27.
//

#include "objects.h"
#include <stdlib.h>
#include <string.h>


//int getAttributePoint_Object()
//{
//
//}

Object objectInit()
{
    Object obj = malloc(sizeof(struct ObjectSTU));
    obj->data = NULL;
    return obj; //todo 其他函数指针的初始化没有写
}

String toString_Float(){
    return "float";
}

Float floatInit()
{
    Float f = objectInit();
    char *str = malloc(sizeof("HelloWorld"));
    strcpy(str, "HelloWorld");
    addAttributeName(f, "testAttr", str);
    return f;
}

//Float toString_Float(Float)
//{
//    Float
//}

//Float float_initFloat(float value){
//    Float f;
//    f.value = value;
//    f.initFloat = float_initFloat;
//}

struct charAttributeSearchTreeNode{
    charAttributeSearchTreePtr nextSibling;
    charAttributeSearchTreePtr firstChild;
    char value;
    void * ptr;
};

charAttributeSearchTreePtr searchCharTreeSibling(charAttributeSearchTreePtr tree, char value){
    while (tree != NULL) {
        if(tree->value == value) return tree;
        else tree = tree->nextSibling;
    }
    return NULL;
}

charAttributeSearchTreePtr createCharTreeNode(char value) {
    charAttributeSearchTreePtr ctp = malloc(sizeof(charAttributeSearchTree));
    ctp->value = value;
    ctp->nextSibling = NULL;
    ctp->ptr = NULL;
    ctp->firstChild = NULL;
    return ctp;
}

void addAsSibling_CharTree(charAttributeSearchTreePtr node, charAttributeSearchTreePtr newNode){
    if (node == NULL) return;
    while (node->nextSibling != NULL) {
        node = node->nextSibling;
    }
    node->nextSibling = newNode;
}

int addAttributeName(Object object, const char * name, void * ptr){
    int i;
    charAttributeSearchTreePtr node = object->data, tempNode;
    if (name[0] == '\0') return 0;
    if (object->data == NULL) {
        //null情况处理
        object->data = createCharTreeNode(name[0]);
        node = object->data;
    } else {
        node = searchCharTreeSibling(object->data, name[0]);
        if (node == NULL) {
            node = createCharTreeNode(name[0]);
            addAsSibling_CharTree(object->data, node);
        }
    }
    for (i = 1; name[i] != 0; ++i) {
        if(node->firstChild == NULL) {  // 如果子节点列表为空（是树叶）要特殊处理（因为要更新firstChild)
            tempNode = createCharTreeNode(name[i]);
            node->firstChild = tempNode;
        }else{
            tempNode = searchCharTreeSibling(node->firstChild, name[i]);
            if(tempNode == NULL) {
                tempNode = createCharTreeNode(name[i]);
                addAsSibling_CharTree(tempNode->firstChild, node);
            }
        }
        node = tempNode;
    }
    node->ptr = ptr;
    return 0;
}

void * getAttributePoint(charAttributeSearchTreePtr tree, const char *name){
    int i = 0;
    charAttributeSearchTreePtr node = tree, tempNode;
    do{
        tempNode = searchCharTreeSibling(node, name[i]);;
        if (tempNode == NULL) return NULL;
        node = tempNode->firstChild;
        ++i;
    }while(name[i] != 0);
    return tempNode->ptr;
}



