#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <iostream>

using namespace std;

#include "sort.hpp"
#include "registro.hpp"

class OrdenadorUniversal{
  private:
    double a, b, c;
    int numQuebras;
    int seed;
    int *vetorOrig;
    Registro Registros[10];
    Registro InRegistros[10];
    Registro QsRegistros[10];

    
    int _passoMPS(int max, int min);
    
    int menorCustoMinParticao(int numMPS);
    int menorCustoLimiarQuebras(int numMPS, SortingAlgorithm *sort);

    double calcularCusto(int cmp, int move, int calls);
    
    void ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarQuebras);
    
    void registraEstatisticasMinParticao(int tamMin, int numMPS);
    void registraEstatisticasLimQuebras(int breaks, int numMPS, SortingAlgorithm algo);
    
    void calculaNovaFaixa(double limParticao, int* minMPS, int* maxMPS, int* passoMPS, int* numMPS, int *minNumMPS, int *maxNumMPS);
    
    void imprimeEstatisticasMinParticao(Registro r);
    void imprimeEstatisticasLimiarQuebras(int numMPS, SortingAlgorithm algo);
    
    void copiaVetor(int vetor[], int tam);

  public:
    OrdenadorUniversal(double a, double b, double c, int numQuebras, int seed, int* vetorOrig)
    : a(a), b(b), c(c), numQuebras(numQuebras), seed(seed), vetorOrig(vetorOrig) { }
    OrdenadorUniversal();

    int determinarLimiarParticao(int vetor[], int tam, int limiarCusto);
    int determinarLimiarQuebras(int* vetor, int tam, int limiarCusto);
    
    void shuffleVector(int vetor[], int size, int numShuffle);
};

#endif