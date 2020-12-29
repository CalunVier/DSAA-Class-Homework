//
// Created by Calun on 2020/12/21.
//

#include "supermarket.h"
#include "../calunvier/tools.h"
#include <stdlib.h>
#include <stdio.h>
#include "../objects/list.h"
#include "../objects/queue.h"


typedef struct {
    int id;
    int age;
    int buy_numbers;
    int arrive_time;
    int leave_time;
} Customer;
typedef Customer *CustomerPtr;


CustomerPtr newCustomer(int id, int age, int buy, int arrive_time, int leave_time) {
    CustomerPtr c = malloc(sizeof(Customer));
    c->id = id;
    c->age = age;
    c->buy_numbers = buy;
    c->arrive_time = arrive_time;
    c->leave_time = leave_time;
    return c;
}


int clock2int(int h, int min, int s) {
    return h * 3600 + min * 60 + s;
}


int customer_com_arrive_time(void *a1, void *a2) {
    CustomerPtr c1 = a1, c2 = a2;
    if (c1->arrive_time > c2->arrive_time) {
        return 1;
    } else if (c1->arrive_time < c2->arrive_time) {
        return -1;
    } else {
        return 0;
    }
}


static inline int buy_time(int number) {
    return 60 * 5 * number;
}


void clear_queue(ListQueue q, int now_time) {
    CustomerPtr c;
    while (1) {
        c = ListQueue_head(q);
        if (c!= NULL && c->leave_time < now_time) {
            ListQueue_pop(q);
        } else { break; }
    }
}


int old_q_partition(ListQueue q, CustomerPtr c) {
    int len = ListQueue_len(q);
    CustomerPtr oc;
    if (len == 0) return 0;
    for (int i = len; i > 0; --i) {
        oc = ListQueue_get(q, i - 1);
        if (oc->age > c->age)
            return i;
    }
    return 0;
}


int customer_com_id(void *a1, void *a2) {
    return ((CustomerPtr) a1)->id - ((CustomerPtr) a2)->id;
}


int supermarket_main() {
    int customer_Number = 10000;
    int now_time = clock2int(8, 0, 0);
    const int q1_age_limit = 65;
    const int q2_number_limit = 5;
    const int time_per_settle = 10;
    const int essential_settle_time = 60;
    ObjList list_customer = newObjList(0);
    random_init();

    for (int i = 0; i < customer_Number; ++i) {
        ObjList_append(list_customer, newCustomer(i, random_int_range(18, 85),
                                                  random_int_range(1, 50),
                                                  random_int_range(clock2int(8, 0, 0),
                                                                   clock2int(23, 59, 59)),
                                                  0));
    }

    ObjList_sort(list_customer, customer_com_arrive_time);

    ListQueue q1 = newListQueue(), q2 = newListQueue(), q3 = newListQueue(), q4 = newListQueue(), q5 = newListQueue();
    ListQueue Buying = newListQueue();

    int p1 = 0, bq_len;
    int choose[5];
    CustomerPtr ac, bc;
    /* 排队循环
     * ac: 等待排队的人的指针
     * bc: 正在购物的人的指针
     * */
    while ((p1 < customer_Number) || (!ListQueue_isBlank(Buying))) {
        printf("%d %d %d %d %d %d %d\n", p1, ListQueue_len(Buying), ListQueue_len(q1), ListQueue_len(q2),
               ListQueue_len(q3), ListQueue_len(q4), ListQueue_len(q5));
        bc = ((CustomerPtr) ListQueue_head(Buying));
        if (p1 >= customer_Number) goto ProcessBuying;
        ac = ((CustomerPtr) ObjList_get(list_customer, p1));
        if (bc == NULL) goto ProcessIn;
        if (bc->leave_time > ac->arrive_time) {
            ProcessIn:
            //处理进店队列
            now_time = ac->arrive_time;
            ac->leave_time = now_time + buy_time(ac->buy_numbers);
            if (ListQueue_isBlank(Buying)) {
                ListQueue_add(Buying, ac);
            } else {
                bq_len = ListQueue_len(Buying);
                for (int j = bq_len; j > 0; --j) {
                    bc = (CustomerPtr) ListQueue_get(Buying, j - 1);
                    if (bc->leave_time < ac->leave_time) {
                        if (j == bq_len) {
                            ListQueue_add(Buying, ac);
                        } else {
                            ListQueue_insert(Buying, ac, j);
                        }
                        break;
                    }
                }
            }
            ++p1;
        } else {
            ProcessBuying:
            //处理购物队列
            /* 先更新时间
             * 先清洗排队队列
             * 然后计算应该插到哪里
             * 最后更新时间
             * */
            now_time = bc->leave_time;  // 更新时间

            /*清洗队列*/
            clear_queue(q1, now_time);
            clear_queue(q2, now_time);
            clear_queue(q3, now_time);
            clear_queue(q4, now_time);
            clear_queue(q5, now_time);

            /*计算队列位置*/
            if (bc->age >= q1_age_limit) {
                choose[0] = old_q_partition(q1, bc);
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
                    ListQueue_insert(q1, bc, choose[0]);
                    if(choose[0]){
                        bc->leave_time = ((CustomerPtr)ListQueue_get(q1,choose[0]-1))->leave_time +
                                bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }else{
                        bc->leave_time += bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }
                    break;
                case 1:
                    ListQueue_add(q2, bc);
                    if(choose[1]){
                        bc->leave_time = ((CustomerPtr)ListQueue_get(q2,choose[1]-1))->leave_time +
                                         bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }else{
                        bc->leave_time += bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }
                    break;
                case 2:
                    ListQueue_add(q3, bc);
                    if(choose[2]){
                        bc->leave_time = ((CustomerPtr)ListQueue_get(q3,choose[2]-1))->leave_time +
                                         bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }else{
                        bc->leave_time += bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }
                    break;
                case 3:
                    ListQueue_add(q4, bc);
                    if(choose[3]){
                        bc->leave_time = ((CustomerPtr)ListQueue_get(q4,choose[3]-1))->leave_time +
                                         bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }else{
                        bc->leave_time += bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }
                    break;
                case 4:
                    ListQueue_add(q5, bc);
                    if(choose[4]){
                        bc->leave_time = ((CustomerPtr)ListQueue_get(q5,choose[4]-1))->leave_time +
                                         bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }else{
                        bc->leave_time += bc->buy_numbers * time_per_settle+ essential_settle_time;
                    }
                    break;
            }
            ListQueue_pop(Buying);
        }
    }

    //id排序
    ObjList_sort(list_customer, customer_com_id);

    // 打印输出
    FILE *ff = fopen("Hello.txt", "w+");
    for (int i = 0; i < customer_Number; ++i) {
        CustomerPtr ccc = (CustomerPtr) ObjList_get(list_customer, i);
        fprintf(ff, "%05d %02d %02d %02d:%02d:%02d %02d:%02d:%02d\n",
                ccc->id, ccc->age, ccc->buy_numbers, ccc->arrive_time / 3600, (ccc->arrive_time % 3600) / 60,
                ccc->arrive_time % 3600 % 60, ccc->leave_time / 3600, (ccc->leave_time % 3600) / 60,
                ccc->leave_time % 3600 % 60);
    }
    fclose(ff);
    return 0;
}
