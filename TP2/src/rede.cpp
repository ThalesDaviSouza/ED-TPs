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

List<int>* Rede::calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino){
  int* visitados = new int[numArmazens];
  int* anterior = new int[numArmazens];

  for(int i = 0; i < numArmazens; i++){
    visitados[i] = naoVisto;
    anterior[i] = -1;
  }

  List<int>* proximos = List<int>::createList();
  proximos->add(idArmazemOrigem);
  visitados[idArmazemOrigem] = visitado;

  while (!proximos->isVazio()) {
    int atual = proximos->removeFirst();
   
    if (atual == idArmazemDestino) {
      break;
    }

    for(int i = 0; i < numArmazens; i++) {
      if (conexoes[atual][i] == 1 && visitados[i] == naoVisto) {
        proximos->add(*new int(i));
        visitados[i] = visitado;
        anterior[i] = atual;
      }
    }
  }

  // Reconstruir o caminho
  List<int>* caminho = List<int>::createList();
  int atual = idArmazemDestino;
  while (atual != -1) {
    caminho = caminho->addFirst(*new int(atual));  // Caminho de trás para frente
    atual = anterior[atual];
  }
  

  if(*caminho->value != idArmazemOrigem) {
    // Não foi possível encontrar um caminho
    caminho->limpar();
    delete caminho;
    caminho = nullptr;
  }
  
  delete[] visitados;
  delete[] anterior;
  proximos->limpar();

  return caminho;
}

void Rede::addPacote(int idArmazem, int idArmazemDestino, Pacote* pacote){
  cout << "Calculando rota pacote" << endl;

  List<int>* rota = calcularRotaPacote(idArmazem, idArmazemDestino);
  List<int>* aux = rota;

  cout << endl << endl;

  while(aux != nullptr){
    cout << *aux->value << endl;
    aux = aux->next;
  }
  cout << endl << endl;

  armazens[idArmazem].ArmazenarPacote(*pacote);
}
