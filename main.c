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
//    // �����������д���ļ�
//    printf("Please type in n:");
//
//    scanf("%d", &n);
//    for(i=0;i<n;++i)
//    {
//        temp = (float)rand();
//        temp /=RAND_MAX;
//        fprintf(f, "%f\n", temp);
//        //printf("%f\n", temp);		//���������̨
//    }
//    fclose(f);
//
//    //��ȡ�����
//    f = fopen("output.txt", "r");
//    a = (float *)malloc(sizeof(float)*n);
//    for(i=0;i<n;++i){
//        fscanf(f, "%f", a+i);
//        //printf("debug:a+i:%f\n",a[i]);		//debug print
//    }
//
//    //�����˵�����
//rootMenu:
//    choise1 = root_menu();
//    if (choise1==1)
//    {
//        //������д�����
//        q = newQueueFromArray(a, n, n*2);
//        OBJECT operateOBJ;
//QueueMenu:
//        choise2 = operation_menu();
//        if (choise2==1)
//        {
//            operateOBJ = insert_menu();
//            itemp = addObjToQueue(q, operateOBJ);
//            if(!itemp) printf("�ɹ���������:%f\n", operateOBJ);
//            goto QueueMenu;
//        }else if (choise2 == 2){
//            if((q->LENGTH) > 0){
//                operateOBJ = getFromQueue(q,q->HEAD);
//                itemp = deleteObjFromQueue(q);
//                if (!itemp) printf("�ɹ�ɾ�����ݣ�%f\n",operateOBJ);
//                else printf("ɾ��ʧ��\n");
//            }else printf("ɾ��ʧ��\n");
//            goto QueueMenu;
//        }else if (choise2 == 3){
//            operateOBJ = search_menu();
//            int ind = indexObjFormQueue(q,operateOBJ);
//            printf("��ѯ������λ��Ϊ��%d\n", ind);
//            goto QueueMenu;
//        }else if (choise2 == 4){
//            printQueue(q);
//            goto QueueMenu;
//        }else if (choise2 == 5){
//            goto rootMenu;
//        }else goto QueueMenu;
//    } else if(choise1 == 3){
//        //������д���б�
//        List l = newListFromArray(a, n);
//        OBJECT operateOBJ;
//ListMenu:
//        choise2 = operation_menu();
//        if (choise2==1)
//        {
//            operateOBJ = insert_menu();
//            itemp = list_append(l, operateOBJ);
//            if(!itemp) printf("�ɹ���������:%f\n", operateOBJ);
//            goto ListMenu;
//        }else if (choise2 == 2){
//            if((q->LENGTH) > 0){
//                operateOBJ = list_get(l, l->len - 1);
//                itemp = list_delete(l, l->len-1);
//                if (!itemp) printf("�ɹ�ɾ�����ݣ�%f\n",operateOBJ);
//                else printf("ɾ��ʧ��\n");
//            }else printf("ɾ��ʧ��\n");
//            goto ListMenu;
//        }else if (choise2 == 3){
//            operateOBJ = search_menu();
//            int ind = list_index(l,operateOBJ);
//            printf("��ѯ������λ��Ϊ��%d\n", ind);
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
//    printf("��ѡ����Ҫ�洢���ݵ����ݽṹ\n1.queue\n2.stack\n3.list\n4.exit\n���������:");
//    scanf("%d", &choise);
//    return choise;
//}
//
//int operation_menu()
//{
//    int choise;
//    printf("��ѡ����Ҫ�Ĳ���\n1.����\n2.ɾ��\n3.��ѯ\n4.��������\n5.������һ��\n���������ѡ��");
//    scanf("%d", &choise);
//    return choise;
//}
//
//OBJECT insert_menu()
//{
//    OBJECT obj;
//    printf("������Ҫ��������ݣ�");
//    scanf("%f", &obj);
//    return obj;
//}
//
//OBJECT search_menu()
//{
//    OBJECT obj;
//    printf("��������Ҫ��ѯ�����ݣ�");
//    scanf("%f", &obj);
//    return obj;
//}
//���ݽṹ��

//20201103����

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
//    printf("InsertionSort����ʱ��Ϊ��%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Mergesort(a1, fnumbers);
//    end = clock();
//    printf("Mergesort����ʱ��Ϊ��%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Heapsort(a2, fnumbers);
//    end = clock();
//    printf("Heapsort����ʱ��Ϊ��%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
//
//    start = clock();
//    Quicksort(a3, fnumbers);
//    end = clock();
//    printf("Quicksort����ʱ��Ϊ��%lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    int a = sizeof(void *);
    printf("%d", a);
}

