//
// Created by Calun on 2020/11/3.
//

#include "tools.h"
#include <stdlib.h>
#include <time.h>

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

void cp_float_array(const float *a, float *b, int a_length)
{
    int i;
    for (i = 0; i < a_length; ++i) {
        b[i] = a[i];
    }
}