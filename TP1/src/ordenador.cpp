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
  int menorCusto, idMenorCusto;
  double custo;

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

int OrdenadorUniversal::menorCustoLimiarQuebras(int numMPS, SortingAlgorithm *sort){
  int cmp, moves, calls;
  int menorCusto, idMenorCusto;
  double custoQs, custoIn;

  for(int i = 0; i < numMPS; i++){
    
    custoQs = QsRegistros[i].cost;
    custoIn = InRegistros[i].cost;
   
    if(i == 0 || menorCusto > custoQs){
      menorCusto = custoQs;
      *sort = quick;
      idMenorCusto = i;
    }
    
    if(menorCusto > custoIn){
      menorCusto = custoIn;
      *sort = insertion;
      idMenorCusto = i;
    }
  }

  return idMenorCusto;
}

int getMPS(int minMPS, int passoMPS, int num){
  return minMPS + (passoMPS * num);
}

int getNumMPS(int minMPS, int passoMPS, int value){
  return (value - minMPS) / passoMPS;
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

  *minMPS = getMPS(*minMPS, *passoMPS, newMin);
  *maxMPS = getMPS(*minMPS, *passoMPS, newMax);
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
  cout << "cost " << r.cost << " ";
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
      // srand48(seed);
      // shuffleVector(vetor, tam, numQuebras);
      copiaVetor(vetor, tam);
      Sort::SetTamParticao(tamMin);
      ordenadorUniversal(vetor, tam, tamMin, 0);
      registraEstatisticasMinParticao(tamMin, numMPS);
      imprimeEstatisticasMinParticao(Registros[numMPS]);
      numMPS++;
    }
    limParticao = menorCustoMinParticao(numMPS);
    calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, &numMPS);

    int minNumMPS = getNumMPS(minMPS, passoMPS, minMPS);
    int maxNumMPS = getNumMPS(minMPS, passoMPS, maxMPS);

    diffCusto = fabs(Registros[minNumMPS].cost - Registros[maxNumMPS].cost);
    

    cout << "numps " << numMPS;
    cout << " limParticao " << Registros[limParticao].mps;
    cout << " mpsdiff " << diffCusto << endl << endl;
    i++;
  }while (diffCusto > limiarCusto && numMPS >= 5);

  return limParticao;
}

int OrdenadorUniversal::determinarLimiarQuebras(int vetor[], int tam, int limiarCusto){
  double diffCusto;
  int minMPS = 2;
  int maxMPS = tam;
  int numMPS = 0;
  int passoMPS = _passoMPS(maxMPS, minMPS);
  int limParticao;
  int i = 0;
  SortingAlgorithm sort;

  Sort::SetTamParticao(50);

  do{
    cout << "inter " << i << endl;
    numMPS = 0;

    for(int limQuebras = minMPS; limQuebras <= maxMPS; limQuebras += passoMPS){
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
    limParticao = menorCustoLimiarQuebras(numMPS, &sort);
    calculaNovaFaixa(limParticao, &minMPS, &maxMPS, &passoMPS, &numMPS);

    int minNumMPS = getNumMPS(minMPS, passoMPS, minMPS);
    int maxNumMPS = getNumMPS(minMPS, passoMPS, maxMPS);
    
    if(sort == quick){
      diffCusto = fabs(QsRegistros[minNumMPS].cost - QsRegistros[maxNumMPS].cost);
    }
    else if(sort == insertion){
      diffCusto = fabs(InRegistros[minNumMPS].cost - InRegistros[maxNumMPS].cost);
    }

    cout << "numlq " << numMPS;
    
    if(sort == quick)
      cout << " limQuebras " << QsRegistros[limParticao].mps;
    else if(sort == insertion)
      cout << " limQuebras " << InRegistros[limParticao].mps;

    cout << " lqdiff " << diffCusto << endl << endl;
    i++;
  }while (diffCusto > limiarCusto && numMPS >= 5);

  return limParticao;
}