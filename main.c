//#include <stdio.h>
//#include "queue.h"
//#include <stdlib.h>
//#include <time.h>
//#include "list.h"
//
//
//int root_menu();
//int operation_menu();
//OBJECT insert_menu();
//OBJECT search_menu();
//
//int main(int argc, char* argv[])
//{
//    int n, i, itemp, choise1,choise2;
//    float *a;
//    float temp, target, bigger=1, smaller=0;
//    FILE *f = fopen("output.txt", "w+");
//    srand((unsigned)time(NULL));
//    Queue q;
//    // 生成随机数并写入文件
//    printf("Please type in n:");
//
//    scanf("%d", &n);
//    for(i=0;i<n;++i)
//    {
//        temp = (float)rand();
//        temp /=RAND_MAX;
//        fprintf(f, "%f\n", temp);
//        //printf("%f\n", temp);		//输出到控制台
//    }
//    fclose(f);
//
//    //读取随机数
//    f = fopen("output.txt", "r");
//    a = (float *)malloc(sizeof(float)*n);
//    for(i=0;i<n;++i){
//        fscanf(f, "%f", a+i);
//        //printf("debug:a+i:%f\n",a[i]);		//debug print
//    }
//
//    //交互菜单部分
//rootMenu:
//    choise1 = root_menu();
//    if (choise1==1)
//    {
//        //创建并写入队列
//        q = newQueueFromArray(a, n, n*2);
//        OBJECT operateOBJ;
//QueueMenu:
//        choise2 = operation_menu();
//        if (choise2==1)
//        {
//            operateOBJ = insert_menu();
//            itemp = addObjToQueue(q, operateOBJ);
//            if(!itemp) printf("成功插入数据:%f\n", operateOBJ);
//            goto QueueMenu;
//        }else if (choise2 == 2){
//            if((q->LENGTH) > 0){
//                operateOBJ = getFromQueue(q,q->HEAD);
//                itemp = deleteObjFromQueue(q);
//                if (!itemp) printf("成功删除数据：%f\n",operateOBJ);
//                else printf("删除失败\n");
//            }else printf("删除失败\n");
//            goto QueueMenu;
//        }else if (choise2 == 3){
//            operateOBJ = search_menu();
//            int ind = indexObjFormQueue(q,operateOBJ);
//            printf("查询的数据位置为：%d\n", ind);
//            goto QueueMenu;
//        }else if (choise2 == 4){
//            printQueue(q);
//            goto QueueMenu;
//        }else if (choise2 == 5){
//            goto rootMenu;
//        }else goto QueueMenu;
//    } else if(choise1 == 3){
//        //创建并写入列表
//        List l = newListFromArray(a, n);
//        OBJECT operateOBJ;
//ListMenu:
//        choise2 = operation_menu();
//        if (choise2==1)
//        {
//            operateOBJ = insert_menu();
//            itemp = list_append(l, operateOBJ);
//            if(!itemp) printf("成功插入数据:%f\n", operateOBJ);
//            goto ListMenu;
//        }else if (choise2 == 2){
//            if((q->LENGTH) > 0){
//                operateOBJ = list_get(l, l->len - 1);
//                itemp = list_delete(l, l->len-1);
//                if (!itemp) printf("成功删除数据：%f\n",operateOBJ);
//                else printf("删除失败\n");
//            }else printf("删除失败\n");
//            goto ListMenu;
//        }else if (choise2 == 3){
//            operateOBJ = search_menu();
//            int ind = list_index(l,operateOBJ);
//            printf("查询的数据位置为：%d\n", ind);
//            goto ListMenu;
//        }else if (choise2 == 4){
//            printList(l);
//            goto ListMenu;
//        }else if (choise2 == 5){
//            goto rootMenu;
//        }else goto ListMenu;
//    }else if(choise1 == 4){
//        //pass
//    }else{
//        goto rootMenu;
//    }
//
//
//    return 0;
//}
//
//
//int root_menu()
//{
//    int choise;
//    printf("请选择需要存储数据的数据结构\n1.queue\n2.stack\n3.list\n4.exit\n请输入序号:");
//    scanf("%d", &choise);
//    return choise;
//}
//
//int operation_menu()
//{
//    int choise;
//    printf("请选择需要的操作\n1.插入\n2.删除\n3.查询\n4.遍历数据\n5.返回上一级\n请输入你的选择：");
//    scanf("%d", &choise);
//    return choise;
//}
//
//OBJECT insert_menu()
//{
//    OBJECT obj;
//    printf("请输入要插入的数据：");
//    scanf("%f", &obj);
//    return obj;
//}
//
//OBJECT search_menu()
//{
//    OBJECT obj;
//    printf("请输入你要查询的数据：");
//    scanf("%f", &obj);
//    return obj;
//}
//数据结构↑

//20201103排序

#include <stdio.h>
#include <time.h>
#include "sorts.h"
#include "tools.h"
#define fnumbers (10000)

int main(void)
{

//    float a0[fnumbers], a1[fnumbers], a2[fnumbers], a3[fnumbers];
//    clock_t start, end;
//    random_float(a0, fnumbers);
//    cp_float_array(a0, a1, fnumbers);
//    cp_float_array(a0, a2, fnumbers);
//    cp_float_array(a0, a3, fnumbers);
//
//    start = clock();
//    InsertionSort(a0, fnumbers);
//    end = clock();
//    printf("InsertionSort运行时间为：%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Mergesort(a1, fnumbers);
//    end = clock();
//    printf("Mergesort运行时间为：%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Heapsort(a2, fnumbers);
//    end = clock();
//    printf("Heapsort运行时间为：%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Quicksort(a3, fnumbers);
//    end = clock();
//    printf("Quicksort运行时间为：%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    int a = sizeof(void *);
    printf("%d", a);
}

