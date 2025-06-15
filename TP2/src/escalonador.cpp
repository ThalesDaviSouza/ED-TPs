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

void Escalonador::addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo){
  if(tipo == PostagemPacote){
    Evento* evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemDestino, 
      PostagemPacote
    );
    
    HeapItem<Evento> novo(tempoEvento, evento);
    eventos.Inserir(novo);
    this->quantidadeEventos++;
  }
}