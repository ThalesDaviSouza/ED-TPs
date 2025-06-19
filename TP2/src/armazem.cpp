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
  if(secoes != nullptr){
    this->secoes->limpar();
  }
}

void Armazem::ArmazenarPacote(Pacote& pacote){
  auto aux = this->secoes;

  // Uma vez que o pacote chegou no armazém
  // Atualizamos o id do armazém atual e da seção atual
  // Se o id for -1, então ainda não tinha começado
  if(pacote.idSecaoAtual == -1){
    pacote.idArmazemAtual = *pacote.Rotas->value;
  }
  else{
    auto rota = pacote.Rotas;
    while (rota->hasValue()){
      if(*rota->value == pacote.idArmazemAtual && rota->next->hasValue()){
        pacote.idArmazemAtual = *rota->next->value;
        break;
      }
      rota = rota->next;
    }
  }
  
  auto posicaoRota = pacote.Rotas;

  while(posicaoRota->hasValue()){
    if(*posicaoRota->value == pacote.idArmazemAtual){
      auto next = posicaoRota->next;

      if(next->hasValue()){
        pacote.idSecaoAtual = *next->value;
        break;
      }
    }
    posicaoRota = posicaoRota->next;
  }

  int idSecaoDestino = pacote.idSecaoAtual;

  while(aux != nullptr && aux->value->idArmazemDestino != idSecaoDestino){
    aux = aux->next;
  }

  // Se encontrou a pilha certa, armazena o pacote
  if(aux != nullptr){
    aux->value->pacotes = aux->value->pacotes->add(pacote);
  }
}

void Armazem::addSecao(int idArmazemDestino) {
  if(secoes == nullptr){
    secoes = List<Secao>::createList();    
  }

  Secao* aux = new Secao(idArmazemDestino);
  this->numSecoes++;
  secoes->add(*aux);  
}