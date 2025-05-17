#ifndef ORDENADOR_H
#define ORDENADOR_H
using namespace std;

#include "sort.hpp"
#include "registro.hpp"

class OrdenadorUniversal{
  private:
    double a, b, c;
    int numQuebras;
    Registro Registros[6];
    Registro InRegistros[6];
    Registro QsRegistros[6];

    
    int _passoMPS(int max, int min);
    int menorCustoMinParticao(int numMPS);
    double calcularCusto(int cmp, int move, int calls);
    void ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarCusto);
    void registraEstatisticasMinParticao(int tamMin, int numMPS);
    void registraEstatisticasLimQuebras(int tamMin, int numMPS);
    void calculaNovaFaixa(float limParticao, int* minMPS, int* maxMPS, int* passoMPS, int* numMPS);
    void imprimeEstatisticasMinParticao(Registro r);

  public:
    OrdenadorUniversal(double a, double b, double c, int numQuebras)
    : a(a), b(b), c(c), numQuebras(numQuebras) { }
    OrdenadorUniversal();
    int determinarLimiarParticao(int vetor[], int tam, int limiarCusto);
    void shuffleVector(int vetor[], int size, int numShuffle);
};

#endif