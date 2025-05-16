#ifndef ORDENADOR_H
#define ORDENADOR_H
using namespace std;

#include "sort.hpp"
#include "registro.hpp"

class OrdenadorUniversal{
  private:
    int _passoMPS(int max, int min);
    Registro InRegistros[6];
    Registro QsRegistros[6];

  public:
    int determinarLimiarParticao(int vetor[], int tam, int limiarCusto);
    void ordenadorUniversal(int vetor[], int tam, int minTamParticao, int limiarCusto);
    void registraEstatisticas(int tamMin, int numMPS);
};

#endif