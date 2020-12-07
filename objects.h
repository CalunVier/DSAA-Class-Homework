//
// Created by Calun on 2020/10/27.
//

#ifndef WEEK3_OBJECTS_H
#define WEEK3_OBJECTS_H

typedef float OBJECT;

typedef struct ObjectSTU Object_obj;
typedef Object_obj * Object;

struct ObjectSTU{
    int attributeSize;
    int funcSize;
    Object (* initFunc) (Object);
    Object (* toString) (Object);
    int (* free) (Object);
    void * (* getAttributePoint)(char *);
    void * (* getFunctionPoint)(char *);
    void * data;     //Attributes and Functions;
};


struct ObjectSTU;
typedef struct FloatSTU Float_obj;
typedef Float_obj * Float;
Float floatInit();


struct StringSTU;
typedef struct StringSTU String;

struct charAttributeSearchTreeNode;
typedef struct charAttributeSearchTreeNode charAttributeSearchTree;
typedef charAttributeSearchTree * charAttributeSearchTreePtr;

#endif //WEEK3_OBJECTS_H
