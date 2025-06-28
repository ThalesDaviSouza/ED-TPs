#include "rede.hpp"
#include <iostream>

// Construtor da rede
// Aloca memória para o vetor de armazéns e para a matriz de conexões
Rede::Rede(int numArmazens, int capacidadeTransporte){
  this->numArmazens = numArmazens;
  this->capacidadeTransporte = capacidadeTransporte;
  this->armazens = new Armazem[numArmazens];
  
  this->conexoes = new int*[numArmazens];
  for(int i = 0; i < numArmazens; i++){
    this->conexoes[i] = new int[numArmazens];
  }
}

// Destrutor da rede
// Libera memória alocada para os armazéns e para a matriz de conexões
Rede::~Rede(){
  delete[] armazens;
  
  for(int i = 0; i < numArmazens; i++){
    delete[] this->conexoes[i];
  }
  
  delete[] this->conexoes;
}

// Adiciona uma seção ao armazém especificado
// Cada seção aponta para outro armazém (representa uma conexão)
void Rede::addSecao(int idArmazem, int idArmazemDestino){
  armazens[idArmazem].addSecao(idArmazemDestino);
}

// Função auxiliar para reconstruir a rota do pacote usando BFS
List<int>* Rede::calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino){
  int* visitados = new int[numArmazens];
  int* anterior = new int[numArmazens]; // Armazena o caminho percorrido

  // Inicializa os vetores
  for(int i = 0; i < numArmazens; i++){
    visitados[i] = naoVisto;
    anterior[i] = -1;
  }
  
  // Inicializa a fila para BFS
  List<int>* proximos = List<int>::createList();
  proximos->add(idArmazemOrigem);
  visitados[idArmazemOrigem] = visitado;
  
  // BFS para encontrar caminho mais curto entre origem e destino
  while (!proximos->isVazio()) {
    int atual = proximos->removeFirst();
   
    if (atual == idArmazemDestino) {
      break; // Paramos ao encontrar o destino
    }

    for(int i = 0; i < numArmazens; i++) {
      if (conexoes[atual][i] == 1 && visitados[i] == naoVisto) {
        proximos->add(*new int(i)); // Adiciona vizinho ainda não visitado
        visitados[i] = visitado;
        anterior[i] = atual; // Marca o caminho por onde veio
      }
    }
  }

  // Reconstrói o caminho da origem até o destino usando o vetor `anterior`
  List<int>* caminho = List<int>::createList();
  int atual = idArmazemDestino;
  while (atual != -1) {
    caminho = caminho->addFirst(*new int(atual));  // Caminho é reconstruído ao contrário
    atual = anterior[atual];
  }
  
  // Verifica se o caminho começa da origem, senão, significa que não achou rota
  if(*caminho->value != idArmazemOrigem) {
    caminho->limpar();
    caminho = nullptr;
  }
  
  // Libera memória temporária
  delete[] visitados;
  delete[] anterior;
  proximos->limpar();

  return caminho;
}

// Associa o pacote a uma rota, se necessário, e armazena no armazém
void Rede::addPacote(int idArmazem, int idArmazemDestino, Pacote* pacote){
  if(pacote->Rotas->isVazio()){
    List<int>* rota = calcularRotaPacote(idArmazem, idArmazemDestino);
    List<int>* aux = rota;
    
    pacote->Rotas = rota;
  }

  // Armazena fisicamente o pacote na estrutura de seções do armazém
  armazens[idArmazem].ArmazenarPacote(*pacote);
}
