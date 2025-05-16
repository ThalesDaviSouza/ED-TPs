#include "ordenador.hpp"



int OrdenadorUniversal::_passoMPS(int max, int min){
  return (int)(max - min)/5;
}


// TODO: implementar a função OrdenadorUniversal
void OrdenadorUniversal::ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarCusto){
  
}

void OrdenadorUniversal::registraEstatisticas(int tamMin, int numMPS){
  // Registro r(tamMin, 0, Sort::qtdComparations, Sort::qtdMoves, Sort::qtdCalls);
  // registros[numMPS] = r;
}

// int OrdenadorUniversal::determinarLimiarParticao(int vetor[], int tam, int limiarCusto){
//   int diffCusto;
//   int minMPS = 2;
//   int maxMPS = tam;
//   int passoMPS = _passoMPS(maxMPS, minMPS);
//   int numMPS = 0;

//   do{
//     for(int tamMin = minMPS; tamMin <= maxMPS; tamMin += passoMPS){
//       ordenadorUniversal(vetor, tam, tamMin, limiarCusto);
//       registraEstatisticas(tamMin, numMPS);
//       numMPS++;
//     }
//     // TODO: continuar do limParticao

//   }while (diffCusto > limiarCusto && numMPS >= 5);

// }