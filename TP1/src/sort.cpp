#include "sort.hpp"

void Sort::swap(int vetor[], int posX, int posY){

}

void Sort::InsertionSort(int vetor[], int tam){
  for(int i = 1; i < tam; i++){
    int j = i - 1;
    int aux = vetor[i];

    while(j >= 0 && vetor[j] > aux){
      vetor[j + 1] = vetor[j];  
      j--;
    }

    vetor[j+1] = aux;
  }
}

void Sort::QuickSort(int vetor[], int tam){
  cout << "Quick Sort" << endl;
}

