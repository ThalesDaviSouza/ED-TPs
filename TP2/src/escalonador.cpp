#include "escalonador.hpp"
#include "utils.hpp"

#include <iostream>
using namespace std;

Escalonador::Escalonador(int numPacotes, Rede* rede, int intervaloTransporte) : 
  eventos(Heap<Evento>(2 * numPacotes)), 
  rede(rede), 
  pacotesAtivos(numPacotes), 
  intervaloTransporte(intervaloTransporte),
  quantidadeEventos(0),
  primeiroPacotePostado(true) { }

Escalonador::~Escalonador() {
  while(!eventos.Vazio()){
    delete eventos.Remover().value;
  }
}

void Escalonador::addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo){
  HeapItem<Evento>* novo = nullptr;
  Evento* evento = nullptr;
  
  if(tipo == PostagemPacote){
    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemDestino, 
      PostagemPacote,
      pacote
    );

  }
  else if(tipo == ArmazenamentoPacote){
    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemDestino, 
      ArmazenamentoPacote,
      pacote
    );
  }
  else if(tipo == TransportePacote){
    evento = new Evento(
      -1, 
      tempoEvento, 
      -1, 
      -1, 
      -1, 
      TransportePacote,
      nullptr
    );
  }

  if(evento != nullptr)
    novo = new HeapItem<Evento>(tempoEvento, evento);
  
  if(novo != nullptr)
    eventos.Inserir(*novo);

  this->quantidadeEventos++;
}

void Escalonador::simularProximoEvento(){
  HeapItem<Evento> prox = eventos.Remover();
  Evento evento = *prox.value;

  quantidadeEventos--;

  if(evento.tipo == PostagemPacote){
    // TODO: Calcular a rota do pacote antes de armazenar ele

    addEvento(evento.tempoEvento, evento.pacote, ArmazenamentoPacote);

    if(primeiroPacotePostado){
      primeiroPacotePostado = false; 
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacote);
    }
  }
  else if(evento.tipo == ArmazenamentoPacote){
    rede->armazens[evento.idArmazemOrigem].ArmazenarPacote(*evento.pacote);
    _log(evento);
  }
  else if(evento.tipo == TransportePacote){
    cout << "Transporte: " << evento.tempoEvento << endl;
  }

}