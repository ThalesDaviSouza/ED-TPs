#include <iostream>
#include <cstdlib>
#include "sort.hpp"
#include "ordenador.hpp"


int main(){
  OrdenadorUniversal ordenador = OrdenadorUniversal();
  int numeros[20] = {
    18, 12, 6, 23, 15,
    10, 25, 7, 19, 14,
    11, 21, 8, 17, 24,
    13, 16, 22, 20, 9
};

  int seed = 1;

  //TODO: trocar por srand48
  srand(seed);
  
  Sort::QuickSort(numeros, 20);
  
  ordenador.shuffleVector(numeros, 20, 3);
  
  for(int& x : numeros){
    cout << x << " ";
  }
  Sort::QuickSort(numeros, 20);
  cout << endl;
  for(int& x : numeros){
    cout << x << " ";
  }


  return 0;
}