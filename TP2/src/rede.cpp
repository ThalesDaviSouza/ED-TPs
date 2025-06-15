#include "rede.hpp"
#include <iostream>

Rede::Rede(int numArmazens, int capacidadeTransporte){
  this->numArmazens = numArmazens;
  this->capacidadeTransporte = capacidadeTransporte;
  this->armazens = new Armazem[numArmazens];
  
  this->conexoes = new int*[numArmazens];
  for(int i = 0; i < numArmazens; i++){
    this->conexoes[i] = new int[numArmazens];
  }
}

Rede::~Rede(){
  delete[] armazens;
  
  for(int i = 0; i < numArmazens; i++){
    delete[] this->conexoes[i];
  }
  
  delete[] this->conexoes;
}

void Rede::addSecao(int idArmazem, int idArmazemDestino){
  armazens[idArmazem].addSecao(idArmazemDestino);
}
