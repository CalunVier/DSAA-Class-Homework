//
// Created by Calun on 2020/10/27.
//

#ifndef WEEK3_OBJECTS_H
#define WEEK3_OBJECTS_H


struct charAttributeSearchTreeNode;
typedef struct charAttributeSearchTreeNode charAttributeSearchTree;
typedef charAttributeSearchTree * charAttributeSearchTreePtr;

typedef float OBJECT;   //todo 等待弃用
struct ObjectSTU;
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
    charAttributeSearchTreePtr data;     //Attributes and Functions;
};

int addAttributeName(struct ObjectSTU * object, const char * name, void * ptr);
void * getAttributePoint(charAttributeSearchTreePtr tree, const char *name);


//typedef struct FloatSTU Float_obj;
typedef Object Float;
Float floatInit();


//struct StringSTU;
typedef Object String;


#endif //WEEK3_OBJECTS_H
