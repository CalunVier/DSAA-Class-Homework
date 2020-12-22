//
// Created by Calun on 2020/12/21.
//

#include "../calunvier/tools.h"
#include <stdlib.h>
#include <stdio.h>
#include "../objects/list.h"
#include "../objects/queue.h"

#define Cutoff (3)

typedef int sortElementType;
typedef struct {
    int id;
    int age;
    int buy_numbers;
    int arrive_time;
    int leave_time;
} Customer;
typedef Customer * CustomerPtr;

CustomerPtr newCustomer(int id, int age, int buy, int arrive_time, int leave_time){
    CustomerPtr c = malloc(sizeof(Customer));
    c->id = id;
    c->age = age;
    c->buy_numbers = buy;
    c->arrive_time = arrive_time;
    c->leave_time = leave_time;
    return c;
}

int clock2int(int h, int min, int s){
    return h*3600+min*60+s;
}

int customer_com_arrive_time(void * a1, void * a2){
    CustomerPtr c1 = a1, c2 = a2;
    if (c1->arrive_time > c2->arrive_time) {
        return 1;
    } else if (c1->arrive_time < c2->arrive_time) {
        return -1;
    }else{
        return 0;
    }
}


static inline int buy_time(int number){
    return 60*5*number;
}


void clear_queue(ListQueue q, int now_time){
    CustomerPtr c;
    int len = ListQueue_len(q);
    while (1) {
        c = ListQueue_head(q);
        if (c->leave_time < now_time) {
            ListQueue_pop(q);
        } else { break; }
    }
}


int old_q_partition(ListQueue q, CustomerPtr c){
    int len = ListQueue_len(q);
    CustomerPtr oc;
    if (len== 0) return 0;
    for (int i = len; i > 0; --i) {
        oc = ListQueue_get(q, i - 1);
        if (oc->age > c->age)
            return i;
    }
    return 0;
    //todo wait for implement
}


int supermarket_main(){
    int customer_Number = 1000;
    int now_time = clock2int(8, 0, 0);
    int q1_age_limit = 65;
    int q2_number_limit = 5;
    ObjList list_customer = newObjList();
    random_init();
    for (int i = 0; i < customer_Number; ++i) {
        ObjList_append(list_customer, newCustomer(i, random_int_range(18, 85), random_int_range(1, 50),
                                                  random_int_range(clock2int(8, 0, 0), clock2int(23, 59, 59)),
                                                  0));
        ObjList_sort(list_customer, customer_com_arrive_time);
    }

    ListQueue q1 = newListQueue(), q2 = newListQueue(), q3 = newListQueue(), q4 = newListQueue(), q5 = newListQueue();
    ListQueue Buying = newListQueue();

    int p1 = 0, bq_len;
    int choose[5];
    CustomerPtr ac, bc;
    while ((p1 < customer_Number) || ListQueue_isBlank(Buying)) {
        bc = ((CustomerPtr) ListQueue_head(Buying));
        ac = ((CustomerPtr) ObjList_get(list_customer, p1));
        if (bc->leave_time > ac->arrive_time) {
            //处理进入队列
            ac->leave_time = now_time + buy_time(ac->buy_numbers);
            bq_len = ListQueue_len(Buying);
            if (ListQueue_isBlank(Buying)) {
                ListQueue_add(Buying, ac);
            } else
                for (int j = bq_len; j > 0; --j) {
                    bc = (CustomerPtr) ListQueue_get(Buying, j - 1);
                    if (bc->leave_time < ac->leave_time) {
                        if (j == bq_len) {
                            ListQueue_add(Buying, ac);
                        } else {
                            ListQueue_insert(Buying, ac, j);
                        }
                    }
                }
            now_time = ac->arrive_time;
            ++p1;
        } else {
            //处理购物队列
            /* 先更新时间
             * 先清洗排队队列
             * 然后计算应该插到哪里
             * 最后更新时间
             * */
            now_time = bc->leave_time;
            clear_queue(q1, now_time);
            clear_queue(q2, now_time);
            clear_queue(q3, now_time);
            clear_queue(q4, now_time);
            clear_queue(q5, now_time);

            /*计算队列位置*/
            if (bc->age >= q1_age_limit) {
                // todo 计算插入q1的位置
            } else {
                choose[0] = -1;
            }
            if (bc->buy_numbers <= q2_number_limit) {
                choose[1] = ListQueue_len(q2);
            } else {
                choose[1] = -1;
            }
            choose[2] = ListQueue_len(q3);
            choose[3] = ListQueue_len(q4);
            choose[4] = ListQueue_len(q5);

            /*选择插入队列*/
            int q2insert = 2;
            if (choose[3] < choose[q2insert]) q2insert = 3;
            if (choose[4] < choose[q2insert]) q2insert = 4;
            if (choose[0] > 0 && choose[0] < choose[q2insert]) q2insert = 0;
            if (choose[1] > 0 && choose[1] < choose[q2insert]) q2insert = 1;

            /*处理插入*/
            switch (q2insert) {
                case 0:
                    break;
                case 1:
                    break;
                default:
                    break;
            }
            ListQueue_pop(Buying);
        }
    }

    //id排序

    FILE * ff = fopen("Hello.txt", "w+");
    for (int i = 0; i < customer_Number; ++i) {
        CustomerPtr ccc = (CustomerPtr) ObjList_get(list_customer, i);
        fprintf(ff, "%05d %02d %02d %02d:%02d:%02d %02d:%02d:%02d\n",
                ccc->id, ccc->age, ccc->buy_numbers, ccc->arrive_time / 3600, (ccc->arrive_time % 3600)/60,
                        ccc->arrive_time % 3600 % 60, ccc->leave_time / 3600, (ccc->leave_time % 3600)/60,
                ccc->leave_time % 3600 % 60);
    }
    fclose(ff);
    return 0;
}
