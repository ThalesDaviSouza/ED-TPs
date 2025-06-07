#include "armazem.hpp"

#include <iostream>

Armazem::Armazem(int numSecoes, int* armazensDestino){
  this->numSecoes = numSecoes;
  this->secoes = List<Secao>::createList();
  List<Secao>* aux = this->secoes;

  for(int i = 0; i < numSecoes; i++){
    Secao* novaSecao = new Secao(armazensDestino[i]);
    aux->add(*novaSecao);
  }  
}

Armazem::~Armazem(){
  this->secoes->limpar();
}

void Armazem::ArmazenarPacote(Pacote& pacote){
  auto aux = this->secoes;
  int idArmazemDestino = pacote.idArmazemDestino;

  while(aux != nullptr && aux->value->idArmazemDestino != idArmazemDestino){
    aux = aux->next;
  }

  // Se encontrou a pilha certa, armazena o pacote
  if(aux != nullptr){
    aux->value->pacotes = aux->value->pacotes->add(pacote);
  }
}