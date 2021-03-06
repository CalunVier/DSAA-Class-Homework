//
// Created by Calun on 2020/12/8.
//

#ifndef WEEK3_CHAR_SEARCH_TREE_H
#define WEEK3_CHAR_SEARCH_TREE_H

/** CharAttributeSearchTree
 * Support the dynamic type attribute searching.
 * */

struct CharAttributeSearchTreeNode{
    struct CharAttributeSearchTreeNode * nextSibling;
    struct CharAttributeSearchTreeNode * firstChild;
    char value;
    void * ptr;
};
typedef struct CharAttributeSearchTreeNode CharAttributeSearchTree;
typedef CharAttributeSearchTree * CharAttributeSearchTreePtr;



CharAttributeSearchTreePtr CharTree_createNode(char value);
CharAttributeSearchTreePtr CharTree_searchSibling(CharAttributeSearchTreePtr tree, char value);
void CharTree_addAsSibling(CharAttributeSearchTreePtr node, CharAttributeSearchTreePtr newNode);
CharAttributeSearchTreePtr CharTree_addStr(CharAttributeSearchTreePtr tree, const char * name);
CharAttributeSearchTreePtr CharTree_getCTN(CharAttributeSearchTreePtr tree, const char * name);

#endif //WEEK3_CHAR_SEARCH_TREE_H
