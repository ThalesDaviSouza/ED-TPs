#include "sort.hpp"

int Sort::QUICK_SORT_SIZE = 5;

int Sort::InQtdComparations = 0;
int Sort::InQtdMoves = 0;
int Sort::InQtdCalls = 0;

int Sort::QsQtdComparations = 0;
int Sort::QsQtdMoves = 0;
int Sort::QsQtdCalls = 0;

void Sort::swap(int vetor[], int posX, int posY){
  int aux = vetor[posX];
  
  vetor[posX] = vetor[posY];
  vetor[posY] = aux; 

  QsIncMoves();
  QsIncMoves();
  QsIncMoves();
}

void Sort::InIncCmp(){
  InQtdComparations++;
}
void Sort::InResetCmp(){
  InQtdComparations = 0;
}
void Sort::InIncMoves(){
  InQtdMoves++;
}
void Sort::InResetMoves(){
  InQtdMoves = 0;
}
void Sort::InIncCalls(){
  InQtdCalls++;
}
void Sort::InResetCalls(){
  InQtdCalls = 0;
}

void Sort::QsIncCmp(){
  QsQtdComparations++;
}
void Sort::QsResetCmp(){
  QsQtdComparations = 0;
}
void Sort::QsIncMoves(){
  QsQtdMoves++;
}
void Sort::QsResetMoves(){
  QsQtdMoves = 0;
}
void Sort::QsIncCalls(){
  QsQtdCalls++;
}
void Sort::QsResetCalls(){
  QsQtdCalls = 0;
}

void Sort::_insertionSort(int V[], int l, int r){
  InIncCalls();

  for(int i = 1; i < r; i++){
    InIncMoves();
    int j = i - 1;
    int aux = V[i];

    InIncCmp();
    while(j >= 0 && V[j] > aux){
      InIncCmp();
      InIncMoves();
      V[j + 1] = V[j];  
      j--;
    }

    InIncMoves();
    V[j+1] = aux;
  }
}
void Sort::InsertionSort(int vetor[], int tam){
  InResetCmp();
  InResetCalls();
  InResetMoves();
  _insertionSort(vetor, 0, tam);
}

int Sort::median (int a, int b, int c) {
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    return b;                            // c b a
}

void Sort::partition3(int V[], int l, int r, int *i, int *j) {
  int x;
  QsIncCalls();
  *i = l;
  *j = r;

  x = median(V[l], V[(*i + *j)/2], V[r]);
  
  do
  { 
    while (x > V[*i]){
      (*i)++;
      QsIncCmp();
    }
    QsIncCmp();
    while (x < V[*j]){
      (*j)--;
      QsIncCmp();
    } 
    
    QsIncCmp();
    if (*i <= *j)
    {
      swap(V, *i, *j);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}


void Sort::quickSort3Ins(int * V, int l, int r){
  int i, j;

  QsIncCalls();

  partition3(V, l, r, &i, &j);
  
  if (l < j) {
      if(j - l <= QUICK_SORT_SIZE){
        Sort::_insertionSort(V, l, j);
      }else{
        quickSort3Ins(V, l, j);
      }
    }
  if (i < r) {
      if(r - i <= QUICK_SORT_SIZE){
        Sort::_insertionSort(V, i, r);
      }else{
        quickSort3Ins(V, i, r);
      }
    } 
}

void Sort::QuickSort(int vetor[], int tam){ 
  QsResetCmp();
  QsResetCalls();
  QsResetMoves();
  Sort::quickSort3Ins(vetor, 0, tam);
}
