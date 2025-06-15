#include "escalonador.hpp"

#include <iostream>
using namespace std;

Escalonador::Escalonador(int numPacotes, Rede* rede) 
: eventos(Heap<Evento>(numPacotes)), rede(rede) {
  quantidadeEventos = 0;
}

Escalonador::~Escalonador() {
  while(!eventos.Vazio()){
    delete eventos.Remover().value;
  }
}

void Escalonador::addEvento(Evento *evento, int tempoEvento){
  HeapItem<Evento> novo(tempoEvento, evento);
  eventos.Inserir(novo);
  this->quantidadeEventos++;
}