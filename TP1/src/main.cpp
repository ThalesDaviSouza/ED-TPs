#include <iostream>
#include <cstdlib>
#include "sort.hpp"


int main(){
  int numeros[20] = {13, 7, 1, 18, 10, 5, 20, 2, 14, 9,
                       6, 16, 3, 12, 19, 8, 11, 17, 15, 4};

  Sort::QuickSort(numeros, 20);

  for(int& x : numeros){
    cout << x << " ";
  }

  // cout << "Teste: " << Sort::qtdCalls++ << endl;
  // cout << "Teste: " << Sort::qtdCalls << endl;

  // srand(101);
  // int teste = (int)(rand()*10);
  // int teste1 = (int)(rand()*10);

  // cout << teste << endl;
  // cout << teste1 << endl;


  return 0;
}