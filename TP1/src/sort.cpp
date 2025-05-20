#include "sort.hpp"

int Sort::QUICK_SORT_SIZE = 1;

int Sort::qtdCmp = 0;
int Sort::qtdMoves = 0;
int Sort::qtdCalls = 0;

int Sort::InQtdCmp = 0;
int Sort::InQtdMoves = 0;
int Sort::InQtdCalls = 0;

void Sort::swap(int vetor[], int posX, int posY){
  int aux = vetor[posX];
  
  vetor[posX] = vetor[posY];
  vetor[posY] = aux; 

  incMoves();
  incMoves();
  incMoves();
}

void Sort::incCmp(){
  qtdCmp++;
}
void Sort::resetCmp(){
  qtdCmp = 0;
  InQtdCmp = 0;
}
void Sort::incMoves(){
  qtdMoves++;
}
void Sort::resetMoves(){
  qtdMoves = 0;
  InQtdMoves = 0;
}
void Sort::incCalls(){
  qtdCalls++;
}
void Sort::resetCalls(){
  qtdCalls = 0;
  InQtdCalls = 0;
}

void Sort::SetTamParticao(int tam){
  QUICK_SORT_SIZE = tam;
}

void Sort::_insertionSort(int V[], int l, int r){
  incCalls();
  InQtdCalls++;

  int j;

  for(int i = l+1; i <= r; i++){
    incMoves();
    InQtdMoves++;

    int aux = V[i];
    j = i - 1;

    incCmp();
    while(j >= 0 && V[j] > aux){
      incCmp();
      InQtdCmp++;
      incMoves();
      InQtdMoves++;
      V[j + 1] = V[j];  
      j--;
    }

    incMoves();
    InQtdMoves++;
    V[j+1] = aux;
  }
}
void Sort::InsertionSort(int vetor[], int tam){
  resetCmp();
  resetCalls();
  resetMoves();
  _insertionSort(vetor, 0, tam-1);
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
  incCalls();
  *i = l;
  *j = r;

  x = median(V[l], V[(*i + *j)/2], V[r]);
  
  do
  { 
    while (x > V[*i]){
      (*i)++;
      incCmp();
    }
    incCmp();
    while (x < V[*j]){
      (*j)--;
      incCmp();
    } 
    
    incCmp();
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

  incCalls();

  partition3(V, l, r, &i, &j);
  
  if (l < j) {
    if((j - l) < QUICK_SORT_SIZE){
      Sort::_insertionSort(V, l, j);
    }else{
      quickSort3Ins(V, l, j);
    }
  }
  if (i < r) {
    if((r - i) < QUICK_SORT_SIZE){
      Sort::_insertionSort(V, i, r);
    }else{
      quickSort3Ins(V, i, r);
    }
  } 
}

void Sort::QuickSort(int vetor[], int tam){ 
  resetCmp();
  resetCalls();
  resetMoves();
  Sort::quickSort3Ins(vetor, 0, tam-1);
}
