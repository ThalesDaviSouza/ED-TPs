#ifndef SORT_H
#define SORT_H
using namespace std;
#include <iostream>
#define QUICK_SORT_SIZE 5

class Sort{
  private:
    static void swap(int vetor[], int posX, int posY);
    static void quickSort3Ins(int V[], int l, int r);
    static void _insertionSort(int V[], int l, int r);
    static void partition3(int V[], int l, int r, int *i, int *j);
    static int median(int a, int b, int c);
  public:
    static void InsertionSort(int vetor[], int tam);
    static void QuickSort(int vetor[], int tam);
};

#endif