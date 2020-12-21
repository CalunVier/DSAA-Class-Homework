//
// Created by Calun on 2020/11/3.
//

#ifndef WEEK3_SORTS_H
#define WEEK3_SORTS_H

#define LeftChild(i) (2*(i)+1)
#define Cutoff (3)

typedef float sortElementType;
//void sortSwap(sortElementType *a, sortElementType *b);
void Heapsort(sortElementType A[], int N);
void InsertionSort(sortElementType A[], int N);
void Mergesort(sortElementType A[], int N);
void Quicksort(sortElementType A[], int N);
#endif //WEEK3_SORTS_H
