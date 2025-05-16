#ifndef SORT_H
#define SORT_H
using namespace std;
#include <iostream>

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

    // Variáveis para metricas do Insertion Sort 
    static int InQtdComparations;
    static int InQtdMoves;
    static int InQtdCalls;

    // Variáveis para metricas do Quick Sort 
    static int QsQtdComparations;
    static int QsQtdMoves;
    static int QsQtdCalls;

    static int QUICK_SORT_SIZE;

    static void InIncCmp();
    static void InResetCmp();
    static void InIncMoves();
    static void InResetMoves();
    static void InIncCalls();
    static void InResetCalls();
    
    static void QsIncCmp();
    static void QsResetCmp();
    static void QsIncMoves();
    static void QsResetMoves();
    static void QsIncCalls();
    static void QsResetCalls();
  };
  
  
#endif