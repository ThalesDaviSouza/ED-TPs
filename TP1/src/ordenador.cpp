#include "ordenador.hpp"

OrdenadorUniversal::OrdenadorUniversal() { }

// numShuffle = lq (limite de quebras da segunda parte)
void OrdenadorUniversal::shuffleVector(int vetor[], int size, int numShuffle){
  int p1, p2, temp;
  p1 = 0;
  p2 = 0;

  cout << "Teste" << endl;
  for(int i = 0; i < numShuffle; i++){
    while(p1 == p2){
      p1 = (int)(rand() % size);
      p2 = (int)(rand() % size);
      
      // TODO: trocar por:
      // p1 = (int)(drand48() * size);
      // p2 = (int)(drand48() * size);
    }
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    temp = vetor[p1];
    vetor[p1] = vetor[p2];
    vetor[p2] = temp;
    p1 = 0;
    p2 = 0;
  }

}

int OrdenadorUniversal::_passoMPS(int max, int min){
  return (int)(max - min)/5;
}


// TODO: implementar a função OrdenadorUniversal
void OrdenadorUniversal::ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarCusto){
  
}

void OrdenadorUniversal::registraEstatisticas(int tamMin, int numMPS){
  Registro registroIn(
    tamMin, 0, 
    Sort::InQtdComparations, 
    Sort::InQtdMoves, 
    Sort::InQtdCalls
  );
  
  Registro registroQs(
    tamMin, 0, 
    Sort::QsQtdComparations, 
    Sort::QsQtdMoves, 
    Sort::QsQtdCalls
  );
  
  InRegistros[numMPS] = registroIn;
  QsRegistros[numMPS] = registroQs;
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