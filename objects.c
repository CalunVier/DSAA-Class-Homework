//
// Created by Calun on 2020/10/27.
//

#include "objects.h"
#include <stdlib.h>


int getAttributePoint_Object()
{

}


Float floatInit()
{
    Float * f = malloc(sizeof(struct ObjectSTU));

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
}

void addAsSibling_CharTree(charAttributeSearchTreePtr node, charAttributeSearchTreePtr newNode){
    while (node->nextSibling != NULL) {
        node = node->nextSibling;
    }
    node->nextSibling = newNode;
}

int addAttributeName(charAttributeSearchTreePtr tree, const char * name){
    int i;
    charAttributeSearchTreePtr node = tree, tempNode;
    for (i = 0; name[i] != 0; ++i) {
        tempNode = searchCharTreeSibling(node, name[i]);
        if(tempNode == NULL){
            tempNode = createCharTreeNode(name[i]);
            addAsSibling_CharTree(node, tempNode);
        }
        node = tempNode->firstChild;
    }
    return 0;
}

void * getAttributePoint(charAttributeSearchTreePtr tree, const char *name){
    int i;
    charAttributeSearchTreePtr node = searchCharTreeSibling(tree, name[0]);;
    for (i = 1; name[i] != 0; ++i) {
        node = searchCharTreeSibling(node->nextSibling, name[i]);
        if (node == NULL) {
            return NULL;
        }//todo not finished
    }
    return node->ptr;
}



