//
// Created by Calun on 2020/11/3.
//

#include "sorts.h"
#include <stdlib.h>

void sortSwap(sortElementType *a, sortElementType *b){
    sortElementType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void InsertionSort(sortElementType A[], int N)
{
    int j, P;
    sortElementType temp;   //Element Type
    for (P = 1; P < N; ++P) {
        temp = A[P];
        for (j = P; j > 0 && A[j - 1] > temp; --j) {
            A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}

void PercDown(sortElementType A[], int i, int N){
    int Child;
    sortElementType temp;
    for (temp = A[i]; LeftChild(i) < N; i = Child) {
        Child = LeftChild(i);
        if (Child != N - 1 && A[Child + 1] > A[Child]) {
            ++Child;
        }
        if (temp < A[Child]) {
            A[i] = A[Child];
        } else {
            break;
        }
    }
    A[i] = temp;
}

void Heapsort(sortElementType A[], int N)
{
    int i;
    sortElementType temp;
    for (i = N / 2; i >= 0; --i) {
        PercDown(A, i, N);
    }
    for (i = N - 1; i > 0; --i) {
        temp = A[0];    //DeleteMax
        A[0] = A[i];
        A[i] = temp;
        PercDown(A, 0, i);
    }
}

void Merge(sortElementType A[], sortElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;
    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    //main loop
    while (Lpos <= LeftEnd && Rpos <= RightEnd) {
        if (A[Lpos] <= A[Rpos]) {
            TmpArray[TmpPos++] = A[Lpos++];
        }else{
            TmpArray[TmpPos++] = A[Rpos++];
        }
    }
    while (Lpos <= LeftEnd) {
        TmpArray[TmpPos++] = A[Lpos++];
    }
    while (Rpos <= RightEnd) {
        TmpArray[TmpPos++] = A[Rpos++];
    }
    for (i = 0; i < NumElements; i++, RightEnd--) {
        A[RightEnd] = TmpArray[RightEnd];
    }
}

void MSort(sortElementType A[], sortElementType TmpArray[], int Left, int Right){
    int Center;
    if (Left < Right) {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

void Mergesort(sortElementType A[], int N) {
    sortElementType *TmpArray;

    TmpArray = malloc(N * sizeof(sortElementType));
    if (TmpArray != NULL) {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
}

sortElementType Median3(sortElementType A[], int Left, int Right){
    int Center = (Left + Right) / 2;

    if (A[Left] > A[Center]) sortSwap(&A[Left], &A[Center]);
    if (A[Left] > A[Right]) sortSwap(&A[Left], &A[Right]);
    if (A[Center] > A[Right]) sortSwap(&A[Center], &A[Right]);

    sortSwap(&A[Center], &A[Right - 1]);
    return A[Right - 1];
}

void Qsort(sortElementType A[], int Left, int Right)
{
    int i, j;
    sortElementType Pivot;
    if(Left+Cutoff<=Right)
    {
        Pivot = Median3(A, Left, Right);
        i = Left;
        j = Right - 1;
        while(1){
            while (A[++i] < Pivot);
            while (A[--j] > Pivot);
            if (i < j) {
                sortSwap(&A[i], &A[j]);
            }else{
                break;
            }
        }
        sortSwap(&A[i], &A[Right - 1]);

        Qsort(A, Left, i - 1);
        Qsort(A, i + 1, Right);
    }
}

void Quicksort(sortElementType A[], int N){
    Qsort(A, 0, N - 1);
}
