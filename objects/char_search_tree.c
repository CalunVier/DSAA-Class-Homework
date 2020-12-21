//
// Created by Calun on 2020/12/8.
//
#include <stdlib.h>
#include "char_search_tree.h"




CharAttributeSearchTreePtr CharTree_createNode(char value) {
    CharAttributeSearchTreePtr ctp = malloc(sizeof(CharAttributeSearchTree));
    ctp->value = value;
    ctp->nextSibling = NULL;
    ctp->ptr = NULL;
    ctp->firstChild = NULL;
    return ctp;
}


CharAttributeSearchTreePtr CharTree_searchSibling(CharAttributeSearchTreePtr tree, char value){
    while (tree != NULL) {
        if(tree->value == value) return tree;
        else tree = tree->nextSibling;
    }
    return NULL;
}


void CharTree_addAsSibling(CharAttributeSearchTreePtr node, CharAttributeSearchTreePtr newNode){
    if (node == NULL) return;
    while (node->nextSibling != NULL) {
        node = node->nextSibling;
    }
    node->nextSibling = newNode;
}


CharAttributeSearchTreePtr CharTree_addStr(CharAttributeSearchTreePtr tree, const char * name)
{
    int i;
    CharAttributeSearchTreePtr node = tree, tempNode;
    // 第一次搜索 确定node指针；
    node = CharTree_searchSibling(tree, name[0]);
    if (node == NULL) {
        node = CharTree_createNode(name[0]);
        CharTree_addAsSibling(tree, node);
    }

    for (i = 1; name[i] != 0; ++i) {
        if(node->firstChild == NULL) {  // 如果子节点列表为空（是树叶）要特殊处理（因为要更新firstChild)
            tempNode = CharTree_createNode(name[i]);
            node->firstChild = tempNode;
        }else{
            tempNode = CharTree_searchSibling(node->firstChild, name[i]);
            if(tempNode == NULL) {
                tempNode = CharTree_createNode(name[i]);
                CharTree_addAsSibling(tempNode->firstChild, node);
            }
        }
        node = tempNode;
    }
    return node;
}


CharAttributeSearchTreePtr CharTree_getCTN(CharAttributeSearchTreePtr tree, const char * name)
{
    int i = 0;
    CharAttributeSearchTreePtr node = tree, tempNode;
    do{
        tempNode = CharTree_searchSibling(node, name[i]);;
        if (tempNode == NULL) return NULL;
        node = tempNode->firstChild;
        ++i;
    }while(name[i] != '\0');
    return tempNode;
}

