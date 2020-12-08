//
// Created by Calun on 2020/10/27.
//

#ifndef WEEK3_OBJECTS_H
#define WEEK3_OBJECTS_H



typedef float OBJECT;   //todo 等待弃用

struct ObjectSTU;
typedef struct ObjectSTU Object_obj;
typedef Object_obj * Object;

/** The functions struct of Object
 * To save the memory, the functions point for the class will only save and connect once.
 * The struct only create once in .h file as global variable.
 * Every living object will contain the handle of this static global stu.
 * Use the function "void * getFunctionPoint(Object object, const char * name)" to get the function point of an class.
 */
struct ObjectFuncStu{
    Object (* initFunc) (struct ObjectSTU *);
    Object (* toString) (struct ObjectSTU *);
    int (* free) (struct ObjectSTU *);
    int (*equal)(struct ObjectSTU *, struct ObjectSTU *);
    CharAttributeSearchTreePtr funcs;
};
typedef struct ObjectFuncStu ObjectFunc;
typedef ObjectFunc * ObjectFuncPtr;


struct ObjectSTU{
    ObjectFuncPtr funcs;
    CharAttributeSearchTreePtr data;     //Attributes and Functions;
};

int addAttribute(struct ObjectSTU * object, const char * name, void * ptr);
void * getAttributePoint(Object object, const char *name);
int addFunction(Object object, const char * name, void * ptr);
void * getFunctionPoint(Object object, const char * name);


//typedef struct FloatSTU Float_obj;
typedef Object Float;
Float floatInit();


//struct StringSTU;
typedef Object String;


#endif //WEEK3_OBJECTS_H
