//
// Created by Calun on 2020/11/3.
//

#include "tools.h"
#include <stdlib.h>
#include <time.h>

/**Create float random numbers
 * param float a: float Array. Used to save the random number as a container;
 * param int n: the number that the random number generated;
 *
 * */
void random_float(float *a, int n) {
    int i;
    float temp;
    srand((unsigned)time(NULL));
    for (i = 0; i < n; ++i) {
        temp = (float) rand();
        temp /= RAND_MAX;
        a[i] = temp;
    }
}

void random_init(){
    srand((unsigned)time(NULL));
}


int random_int_range(int min, int max) {
    return (rand() % (max-min+1)) + min;

}


/**Copy a float array
 * like strcpy.
 * the function will copy the contains form float array a to float array b.
 * */
void cp_float_array(const float *a, float *b, int a_length)
{
    int i;
    for (i = 0; i < a_length; ++i) {
        b[i] = a[i];
    }
}