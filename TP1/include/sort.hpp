#ifndef SORT_H
#define SORT_H
using namespace std;
#include <iostream>

class Sort{
  private:
    static void swap(int vetor[], int posX, int posY);
  public:
    static void InsertionSort(int vetor[], int tam);
    static void QuickSort(int vetor[], int tam);
};

#endif