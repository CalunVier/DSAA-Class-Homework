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

