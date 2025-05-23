#include <iostream>
#include <fstream>
#include <string>
#include "sort.hpp"
#include "ordenador.hpp"

using namespace std;

// Conta o número de quebras no vetor
int getNumBreaks(int* vetor, int tamanho) {
  int cont = 0;
  for (int i = 0; i < tamanho - 1; ++i) {
    if (vetor[i] > vetor[i + 1]) {
      ++cont;
    }
  }
  return cont;
}

int main(int argc, char** argv){
  int* vetorOrig;
  int* vetorCopia;
  int seed, num;
  double a, b , c;
  double limiarCusto;
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

  vetorOrig = new int[tamArray];
  vetorCopia = new int[tamArray];
  for(int i = 0; i < tamArray; i++){
    cin >> vetorOrig[i];
  }
  
  numQuebras = getNumBreaks(vetorOrig, tamArray);

  OrdenadorUniversal ordenador = OrdenadorUniversal(a, b, c, numQuebras, seed, vetorOrig);
  
  cout << "size " << tamArray;
  cout << " seed " << seed;
  cout << " breaks " << numQuebras << endl << endl; 
   
  int minParticao = ordenador.determinarLimiarParticao(vetorCopia, tamArray, limiarCusto);
  Sort::SetTamParticao(minParticao);
  Sort::QuickSort(vetorCopia, tamArray);
  int limiarQuebras = ordenador.determinarLimiarQuebras(vetorCopia, tamArray, limiarCusto);

  delete[] vetorCopia;
  delete[] vetorOrig;

  fclose(stdin);

  return 0;
}