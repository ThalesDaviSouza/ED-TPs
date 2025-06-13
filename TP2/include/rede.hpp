#ifndef REDE_H
#define REDE_H

#include "armazem.hpp"

class Rede{
public:
  int capacidadeTransporte;
  int numArmazens;  
  Armazem* armazens;
  int** conexoes;

  Rede(int numArmazens, int capacidadeTransporte);
  ~Rede();

};

#endif