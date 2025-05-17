#include <iostream>
#include <fstream>
#include <string>
#include "sort.hpp"
#include "ordenador.hpp"

using namespace std;

int main(int argc, char** argv){
  int* vetor;
  int seed, num;
  double a, b , c;
  float limiarCusto;
  int tamArray;
  int numQuebras;
  
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

  srand48(seed);
  numQuebras = drand48() * tamArray;

  OrdenadorUniversal ordenador = OrdenadorUniversal(a, b, c, numQuebras, seed);
  
  cout << "size " << tamArray;
  cout << " seed " << seed;
  cout << " breaks " << numQuebras << endl << endl; 
  
  vetor = new int[tamArray];
  for(int i = 0; i < tamArray; i++){
    cin >> vetor[i];
  }
  
  Sort::QuickSort(vetor, tamArray);  
  
  ordenador.determinarLimiarParticao(vetor, tamArray, limiarCusto);
  ordenador.determinarLimiarQuebras(vetor, tamArray, limiarCusto);

  return 0;
}