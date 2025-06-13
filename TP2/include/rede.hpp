#ifndef REDE_H
#define REDE_H

#include "armazem.hpp"

class Rede{
public:
  int numArmazens;  
  Armazem* armazens;
  int** conexoes;

  Rede(int numArmazens);
  ~Rede();

};

#endif