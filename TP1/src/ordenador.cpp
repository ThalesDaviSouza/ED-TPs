#include <cmath>
#include "ordenador.hpp"

OrdenadorUniversal::OrdenadorUniversal() { }

// numShuffle = lq (limite de quebras da segunda parte)
void OrdenadorUniversal::shuffleVector(int vetor[], int size, int numShuffle){
  int p1, p2, temp;
  p1 = 0;
  p2 = 0;

  for(int i = 0; i < numShuffle; i++){
    while(p1 == p2){
      p1 = (int)(rand() % size);
      p2 = (int)(rand() % size);
      
      // TODO: trocar por:
      // p1 = (int)(drand48() * size);
      // p2 = (int)(drand48() * size);
    }
   
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
  if(numQuebras < limiarCusto){
    Sort::InsertionSort(vetor, tam);
  }
  else{
    if(tam > minTamParticao){
      Sort::QuickSort(vetor, tam);
    }
    else{
      Sort::InsertionSort(vetor, tam);
    }
  }
}

void OrdenadorUniversal::registraEstatisticasMinParticao(int tamMin, int numMPS){
  int cmp = Sort::InQtdComparations + Sort::QsQtdComparations;
  int move = Sort::InQtdMoves + Sort::QsQtdMoves;
  int calls = Sort::InQtdCalls + Sort::QsQtdCalls;

  Registro registro(
    tamMin, 
    calcularCusto(cmp, move, calls), 
    cmp,
    move, 
    calls
  );
  
  Registros[numMPS] = registro;
}

void OrdenadorUniversal::registraEstatisticasLimQuebras(int tamMin, int numMPS){
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

double OrdenadorUniversal::calcularCusto(int cmp, int move, int calls){
  return (a * cmp) + (b * move) + (c * calls);
}

int OrdenadorUniversal::menorCustoMinParticao(int numMPS){
  int cmp, moves, calls;
  int menorCusto, idMenorCusto, custo;

  for(int i = 0; i < numMPS; i++){
    cmp = Registros[i].cmp;
    moves = Registros[i].moves;
    calls = Registros[i].calls;

    // cout << "i: " << i << endl;
    // cout << "cmp: " << Registros[i].cmp << endl;
    // cout << "moves: " << Registros[i].moves << endl;
    // cout << "calls: " << Registros[i].calls << endl;

    custo = fabs(calcularCusto(cmp, moves, calls));
    if(custo < 0){
      custo *= -1;
    }

    if(i == 0 || menorCusto > custo){
      menorCusto = custo;
      idMenorCusto = i;
    }
  }

  return idMenorCusto;
}

void OrdenadorUniversal::calculaNovaFaixa(float limParticao, int* minMPS, int* maxMPS, int* passoMPS, int* numMPS){
  int newMin, newMax;
  if(limParticao == 0){
    newMin = 0;
    newMax = 2;
  }
  else if(limParticao == *numMPS-1){
    newMin = *numMPS - 3;
    newMax = *numMPS - 1;
  }
  else{
    newMin = limParticao -1;
    newMax = limParticao+1;
  }

  *minMPS = newMin;
  *maxMPS = newMax;
  *passoMPS = (int)((*maxMPS-*minMPS)/5);
  if(*passoMPS == 0) (*passoMPS)++;
}

void OrdenadorUniversal::imprimeEstatisticasMinParticao(Registro r){
  cout << "mps " << r.mps << " ";
  cout << "cost " << r.cost << " ";
  cout << "cmp " << r.cmp << " ";
  cout << "move " << r.moves << " ";
  cout << "calls " << r.calls << endl;
}

int OrdenadorUniversal::determinarLimiarParticao(int vetor[], int tam, int limiarCusto){
  double diffCusto;
  int minMPS = 2;
  int maxMPS = tam;
  int numMPS = 0;
  int passoMPS = _passoMPS(maxMPS, minMPS);
  int limParticao;
  int i = 0;

  Sort::SetTamParticao(50);
  
  do{
    cout << "inter " << i << endl;
    numMPS = 0;
    for(int tamMin = minMPS; tamMin <= maxMPS; tamMin += passoMPS){
      // Sort::SetTamParticao(tamMin);
      shuffleVector(vetor, tam, numQuebras);
      ordenadorUniversal(vetor, tam, tamMin, limiarCusto);
      registraEstatisticasMinParticao(tamMin, numMPS);
      imprimeEstatisticasMinParticao(Registros[numMPS]);
      numMPS++;
    }
    limParticao = menorCustoMinParticao(numMPS);
    calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, &numMPS);
    diffCusto = fabs(Registros[minMPS].cost - Registros[maxMPS].cost);

    cout << "numps " << numMPS;
    cout << " limParticao " << Registros[limParticao].mps;
    cout << " mpsdiff " << diffCusto << endl << endl;
    i++;
  }while (diffCusto > limiarCusto && numMPS >= 5);

  return limParticao;
}