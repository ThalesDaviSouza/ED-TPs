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

  //TODO: trocar por:
  // srand48(seed);
  srand(seed);
  // TODO: trocar por:
  // numQuebras = drand48() * tamArray;
  numQuebras = rand() % tamArray;

  // numQuebras = 758;

  OrdenadorUniversal ordenador = OrdenadorUniversal(a, b, c, numQuebras);
  
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