#include <iostream>
#include "sort.hpp"

int main(){
  int numeros[20] = {13, 7, 1, 18, 10, 5, 20, 2, 14, 9,
                       6, 16, 3, 12, 19, 8, 11, 17, 15, 4};
  Sort::QuickSort(numeros, 20);

  for(int& x : numeros){
    cout << x << " ";
  }

  return 0;
}