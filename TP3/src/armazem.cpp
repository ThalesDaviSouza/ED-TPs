#include "armazem.hpp"

#include <iostream>

Armazem::Armazem(int numSecoes, int* armazensDestino){
  this->numSecoes = numSecoes;
  this->secoes = List<Secao>::createList();
  List<Secao>* aux = this->secoes;

  // Adiciona cada seção conforme os armazéns de destino passados
  for(int i = 0; i < numSecoes; i++){
    Secao* novaSecao = new Secao(armazensDestino[i]);
    aux->add(*novaSecao);
  }  
}

Armazem::~Armazem(){
  // Libera memória da lista de seções e seus elementos
  if(secoes != nullptr){
    this->secoes->limpar();
  }
}

void Armazem::ArmazenarPacote(Pacote& pacote){
  auto aux = this->secoes;

  // Atualiza id do armazém atual e seção atual no pacote conforme a rota
  // Se ainda não começou a rota (idSecaoAtual == -1), define o armazém atual para o primeiro da rota
  if(pacote.idSecaoAtual == -1){
    pacote.idArmazemAtual = *pacote.Rotas->value;
  }
  else{
    // Avança na rota para atualizar o armazém atual para o próximo da lista
    auto rota = pacote.Rotas;
    while (rota->hasValue()){
      if(*rota->value == pacote.idArmazemAtual && rota->next->hasValue()){
        pacote.idArmazemAtual = *rota->next->value;
        break;
      }
      rota = rota->next;
    }
  }
  
  // Define a seção atual baseada no próximo nó da rota a partir do armazém atual
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

  // Procura a seção correta dentro do armazém para armazenar o pacote
  while(aux != nullptr && aux->value->idArmazemDestino != idSecaoDestino){
    aux = aux->next;
  }

  // Se encontrou a seção destino, adiciona o pacote na pilha dessa seção
  if(aux != nullptr){
    aux->value->pacotes = aux->value->pacotes->add(pacote);
  }
}

void Armazem::addSecao(int idArmazemDestino) {
  // Cria a lista de seções caso ainda não exista
  if(secoes == nullptr){
    secoes = List<Secao>::createList();    
  }

  Secao* aux = new Secao(idArmazemDestino);
  this->numSecoes++;
  secoes->add(*aux);  
}
