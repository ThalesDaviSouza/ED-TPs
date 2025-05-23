#include <cmath>
#include <iomanip>
#include "ordenador.hpp"

OrdenadorUniversal::OrdenadorUniversal() { }

// numShuffle = lq (limite de quebras da segunda parte)
void OrdenadorUniversal::shuffleVector(int vetor[], int size, int numShuffle){
  int p1, p2, temp;
  p1 = 0;
  p2 = 0;

  for(int i = 0; i < numShuffle; i++){
    while(p1 == p2){
      p1 = (int)(drand48() * size);
      p2 = (int)(drand48() * size);
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

void OrdenadorUniversal::ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras){
  if(numQuebras < limiarQuebras){
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
  int cmp = Sort::qtdCmp;
  int move = Sort::qtdMoves;
  int calls = Sort::qtdCalls;

  Registro registro(
    tamMin, 
    calcularCusto(cmp, move, calls), 
    cmp,
    move, 
    calls
  );
  
  Registros[numMPS] = registro;
}

void OrdenadorUniversal::registraEstatisticasLimQuebras(int breaks, int numMPS, SortingAlgorithm algo){
  Registro registro(
    breaks, 
    calcularCusto(Sort::qtdCmp, Sort::qtdMoves, Sort::qtdCalls), 
    Sort::qtdCmp, 
    Sort::qtdMoves, 
    Sort::qtdCalls
  );
  
  switch (algo)
  {
    case quick:
      registro.calls;
      registro.moves;
      registro.cmp;
      QsRegistros[numMPS] = registro;
      break;

    case insertion:
      InRegistros[numMPS] = registro;
      break;
      
    default:
      break;
  }
}

double OrdenadorUniversal::calcularCusto(int cmp, int move, int calls){
  return fabs((a * cmp) + (b * move) + (c * calls));
}

int OrdenadorUniversal::menorCustoMinParticao(int numMPS){
  int cmp, moves, calls;
  int idMenorCusto;
  double custo, menorCusto;

  for(int i = 0; i < numMPS; i++){
    cmp = Registros[i].cmp;
    moves = Registros[i].moves;
    calls = Registros[i].calls;

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

// O menor custo é definido pela diferença absoluta entre
// o custo de quicksort e do insertion sort para um determinado
// limiar de quebras 
int OrdenadorUniversal::menorCustoLimiarQuebras(int numMPS, SortingAlgorithm *sort){
  int cmp, moves, calls;
  int idMenorCusto;
  double custoQs, custoIn, custoAbs, menorCusto;

  for(int i = 0; i < numMPS; i++){
    
    custoQs = QsRegistros[i].cost;
    custoIn = InRegistros[i].cost;
    custoAbs = fabs(custoQs - custoIn);
    
    if(i == 0 || menorCusto > custoAbs){
      menorCusto = custoAbs; 
      idMenorCusto = i;
    }
    
  }

  return idMenorCusto;
}

int getMPS(int minMPS, int passoMPS, int num){
  return minMPS + (passoMPS * num);
}

/**
 * Para cada faixa é calculado a posição do min e do max
 */
void OrdenadorUniversal::calculaNovaFaixa(double limParticao, int* minMPS, int* maxMPS, int* passoMPS, int* numMPS, int *minNumMPS, int *maxNumMPS){
  int newMin, newMax, minAux;
  if(limParticao == 0){
    newMin = 0;
    newMax = 2;
  }
  else if(limParticao == *numMPS-1){
    newMin = *numMPS - 3;
    newMax = *numMPS - 1;
  }
  else{
    newMin = limParticao - 1;
    newMax = limParticao + 1;
  }

  *minNumMPS = newMin;
  *maxNumMPS = newMax;

  minAux = *minMPS;

  *minMPS = getMPS(minAux, *passoMPS, newMin);
  *maxMPS = getMPS(minAux, *passoMPS, newMax);

  *passoMPS = (int)((*maxMPS-*minMPS)/5);
  
  if(*passoMPS == 0) (*passoMPS)++;
}

void OrdenadorUniversal::imprimeEstatisticasMinParticao(Registro r){
  cout << "mps " << r.mps << " ";
  cout << "cost " << fixed << setprecision(9) << r.cost << " ";
  cout << "cmp " << r.cmp << " ";
  cout << "move " << r.moves << " ";
  cout << "calls " << r.calls << endl;
}

void OrdenadorUniversal::imprimeEstatisticasLimiarQuebras(int numMPS, SortingAlgorithm algo){
  Registro r;

  if(algo == insertion){  
    cout << "in ";
    r = InRegistros[numMPS];
  } 
  else if(algo == quick){
    cout << "qs ";
    r = QsRegistros[numMPS];
  } 

  cout << "lq " << r.mps << " ";
  cout << "cost " << fixed << setprecision(9) << r.cost << " ";
  cout << "cmp " << r.cmp << " ";
  cout << "move " << r.moves << " ";
  cout << "calls " << r.calls << endl;
}

void OrdenadorUniversal::copiaVetor(int vetor[], int tam){
  for(int i = 0; i < tam; i++){
    vetor[i] = vetorOrig[i];
  }
}

int OrdenadorUniversal::determinarLimiarParticao(int vetor[], int tam, int limiarCusto){
  float diffCusto;
  int minMPS = 2;
  int maxMPS = tam;
  int numMPS = 0;
  int passoMPS = _passoMPS(maxMPS, minMPS);
  int limParticao;
  int i = 0;

  do{
    cout << "iter " << i << endl;
    numMPS = 0;

    for(int tamMin = minMPS; tamMin <= maxMPS; tamMin += passoMPS){
      copiaVetor(vetor, tam);
      Sort::SetTamParticao(tamMin);

      ordenadorUniversal(vetor, tam, tamMin, 0);
      
      registraEstatisticasMinParticao(tamMin, numMPS);
      imprimeEstatisticasMinParticao(Registros[numMPS]);
      
      numMPS++;
    }

    limParticao = menorCustoMinParticao(numMPS);
    int minNumMPS;
    int maxNumMPS;
    calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, &numMPS, &minNumMPS, &maxNumMPS);

    diffCusto = Registros[minNumMPS].cost - Registros[maxNumMPS].cost;
    if(diffCusto < 0){
      diffCusto *= -1;
    }
    
    cout << "nummps " << numMPS;
    cout << " limParticao " << Registros[limParticao].mps;
    cout << " mpsdiff " << setprecision(6) << diffCusto << endl << endl;
    
    i++;
  }while (diffCusto > limiarCusto && numMPS >= 5);

  return Registros[limParticao].mps;
}


int OrdenadorUniversal::determinarLimiarQuebras(int* vetor, int tam, int limiarCusto){
  float diffCusto = limiarCusto + 1;
  int minMPS = 1;
  int maxMPS = tam/2;
  int numMPS = 20;
  int passoMPS = _passoMPS(maxMPS, minMPS);
  int limQuebras;
  int i = 0;
  SortingAlgorithm sort;
  float lastInCost;

  while ((diffCusto > limiarCusto) && (numMPS >= 5)){
    
    cout << "iter " << i << endl;
    numMPS = 0;

    for(limQuebras = minMPS; limQuebras <= maxMPS; limQuebras += passoMPS){
      
      srand48(seed);
      shuffleVector(vetor, tam, limQuebras);
      Sort::QuickSort(vetor, tam);
      registraEstatisticasLimQuebras(limQuebras, numMPS, quick);
      imprimeEstatisticasLimiarQuebras(numMPS, quick);
      
      srand48(seed);
      shuffleVector(vetor, tam, limQuebras);
      Sort::InsertionSort(vetor, tam);
      registraEstatisticasLimQuebras(limQuebras, numMPS, insertion);
      imprimeEstatisticasLimiarQuebras(numMPS, insertion);

      numMPS++;
    }

    limQuebras = menorCustoLimiarQuebras(numMPS, &sort);
    
    int minNumMPS;
    int maxNumMPS;

    calculaNovaFaixa(limQuebras, &minMPS, &maxMPS, &passoMPS, &numMPS, &minNumMPS, &maxNumMPS);

    diffCusto = (float)fabs(InRegistros[minNumMPS].cost - InRegistros[maxNumMPS].cost);
    
    cout << "numlq " << numMPS;
    
    cout << " limQuebras " << QsRegistros[limQuebras].mps;
    
    cout << " lqdiff " << fixed << setprecision(6) << diffCusto << endl << endl;
    
    i++;
  }
  
  limQuebras = InRegistros[limQuebras].mps;

  return limQuebras;
}