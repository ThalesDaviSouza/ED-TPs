#ifndef SORT_H
#define SORT_H

enum SortingAlgorithm{
  quick,
  insertion
};

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

    // Variáveis para metricas
    static int qtdCmp;
    static int qtdMoves;
    static int qtdCalls;
    
    static int InQtdCmp;
    static int InQtdMoves;
    static int InQtdCalls;

    static int QUICK_SORT_SIZE;

    static void incCmp();
    static void resetCmp();
    static void incMoves();
    static void resetMoves();
    static void incCalls();
    static void resetCalls();
    
    static void SetTamParticao(int tam);
  };
  
  
#endif