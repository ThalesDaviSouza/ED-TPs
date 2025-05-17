#include <iostream>
#include <fstream>
#include <string>
#include "sort.hpp"
#include "ordenador.hpp"

using namespace std;

int main(int argc, char** argv){
  OrdenadorUniversal ordenador = OrdenadorUniversal();
  int* vetor;
  int seed, num;
  double a, b , c;
  float limiarCusto;
  int tamArray;

  // Redireciona a entrada padrão (cin) para ler do arquivo
  if (freopen(argv[1], "r", stdin) == nullptr) {
      cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
      return 1;
  }

  cin >> seed;
  cin >> limiarCusto;
  cin >> a;
  cin >> b;
  cin >> c;
  cin >> tamArray;

  // cout << "seed: " << seed << endl;
  // cout << "limiarCusto: " << limiarCusto << endl;
  // cout << "a: " << a << endl;
  // cout << "b: " << b << endl;
  // cout << "c: " << c << endl;
  // cout << "tamArray: " << tamArray << endl;


  vetor = new int[tamArray];
  for(int i = 0; i < tamArray; i++){
    cin >> vetor[i];
  }
  

  //TODO: trocar por srand48
  // srand(seed);
  
  // Sort::QuickSort(numeros, 20);
  
  // ordenador.shuffleVector(numeros, 20, 3);
  
  // for(int& x : numeros){
  //   cout << x << " ";
  // }
  // Sort::QuickSort(numeros, 20);
  // cout << endl;
  // for(int& x : numeros){
  //   cout << x << " ";
  // }


  return 0;
}