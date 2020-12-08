//
// Created by Calun on 2020/10/27.
//

#include <stdlib.h>
#include <string.h>
#include "char_search_tree.h"
#include "objects.h"


int addAttribute(Object object, const char * name, void * ptr){
    if (name[0] == '\0') return 0;
    if (object->data == NULL) {
        //null情况处理
        object->data = CharTree_createNode(name[0]);
    }
    CharTree_addStr(object->data, name)->ptr = ptr;
    return 0;
}

void * getAttributePoint(Object object, const char *name){
    return CharTree_getCTN(object->data, name)->ptr;
}

int addFunction(Object object, const char * name, void * ptr){
    if (name[0] == '\0') return 0;
    if (object->funcs->funcs == NULL) {
        //null情况处理
        object->funcs->funcs = CharTree_createNode(name[0]);
    }
    CharTree_addStr(object->funcs->funcs, name)->ptr = ptr;
    return 0;
}

void * getFunctionPoint(Object object, const char * name){
    return CharTree_getCTN(object->funcs->funcs, name)->ptr;
}


/** Objects
 * The init function of Object contains two parts:
 * ObjectInit(Object, object)
 * newObject[_from](Object object, ...)
 *   The ObjectsInit function used to build essential interface of an object.
 * but not create any space in memory. The extends action will be processed
 * in this function. You can call the ObjectInit of super class to build the
 * super interface.
 *   The newObject[_from](Object object, ...) used to create a new Object example,
 * which will create space in memory (usually in first line), and call ObjectInit
 * function (usually in second line).
 * */
Object objectInit()
{
    Object obj = malloc(sizeof(struct ObjectSTU));
    obj->data = NULL;
    return obj; //todo 其他函数指针的初始化没有写
}



Float floatInit()
{
    Float f = objectInit();
    char *str = malloc(sizeof("HelloWorld"));
    strcpy(str, "HelloWorld");
    addAttribute(f, "testAttr", str);
    return f;
}

