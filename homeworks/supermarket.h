//
// Created by Calun on 2020/12/21.
//

#ifndef WEEK3_SUPERMARKET_H
#define WEEK3_SUPERMARKET_H
typedef struct {
    int id;
    int age;
    int buy_numbers;
    int arrive_time;
    int leave_time;
} Customer;
typedef Customer *CustomerPtr;
CustomerPtr newCustomer(int id, int age, int buy, int arrive_time, int leave_time);
int clock2int(int h, int min, int s);
int customer_com_arrive_time(void *a1, void *a2);
int customer_com_id(void *a1, void *a2);

int supermarket_main();
#endif //WEEK3_SUPERMARKET_H
