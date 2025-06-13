#include "rede.hpp"

Rede::Rede(int numArmazens){
  this->numArmazens = numArmazens;
  this->armazens = new Armazem[numArmazens];
  
  this->conexoes = new int*[numArmazens];
  for(int i = 0; i < numArmazens; i++){
    this->conexoes[i] = new int[numArmazens];
  }
}

Rede::~Rede(){
  delete[] this->armazens;

  for(int i = 0; i < numArmazens; i++){
    delete[] this->conexoes[i];
  }

  delete[] this->conexoes;
}
