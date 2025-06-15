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
  int idArmazemDestino = pacote.idArmazemDestino;

  while(aux != nullptr && aux->value->idArmazemDestino != idArmazemDestino){
    aux = aux->next;
  }

  // Se encontrou a pilha certa, armazena o pacote
  if(aux != nullptr){
    aux->value->pacotes = aux->value->pacotes->add(pacote);
  }
}

Pacote* Armazem::RecuperarPacote(int idPacote, int idArmazemDestino){
  auto secao = this->secoes;
  while(secao != nullptr && secao->value->idArmazemDestino != idArmazemDestino){
    secao = secao->next;
  }

  if(secao != nullptr){
    auto pacotes = secao->value->pacotes;
    Pilha<Pacote>* pilhaAux = Pilha<Pacote>::createPilha();
    Pacote* pacoteAux = nullptr;

    /**
     * Roda o loop até limpar a pilha
     * Ou até o pacoteAux assumir o valor do pacote que será removido
     */
    while (pacotes->value != nullptr)
    {
      pacoteAux = pacotes->value;
      pacotes = pacotes->remove(false);
      pilhaAux = pilhaAux->add(*pacoteAux);

      if(pacoteAux->id == idPacote){
        break;
      }
    }
    
    if(pacoteAux != nullptr){
      // Removo o pacoteAux da pilhaAux para
      // Não ser adicionado novamente na pilha
      pilhaAux = pilhaAux->remove(false);
      
      while (pilhaAux->value != nullptr)
      {
        auto aux = pilhaAux->value;
        pilhaAux = pilhaAux->remove(false);
        pacotes = pacotes->add(*aux);
      }

      secao->value->pacotes = pacotes;
      return pacoteAux;
    }
  }
  
  return nullptr;
}

void Armazem::addSecao(int idArmazemDestino) {
  if(secoes == nullptr){
    secoes = List<Secao>::createList();    
  }

  Secao* aux = new Secao(idArmazemDestino);
  this->numSecoes++;
  secoes->add(*aux);  
}