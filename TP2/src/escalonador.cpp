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

ULLI Escalonador::gerarChave(int tempo, Evento* evento){
  ULLI chave;
  short digitoTipo = (evento->tipo == TransportePacotes) ? 2 : 1;
  ULLI digitoMeio = 0;

  if(evento->tipo == TransportePacotes){
    digitoMeio = 0;
  }
  else if(evento->tipo == TransportePacote){
    digitoMeio += (evento->pacote->idArmazemOrigem * 100);
    digitoMeio += evento->pacote->idArmazemDestino;
  }
  else{
    digitoMeio = evento->pacote->id;
  }

  chave = (tempo * 10000000) + (digitoMeio * 10) + digitoTipo; 

  return chave;
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
  else if(tipo == TransportePacotes){
    evento = new Evento(
      -1, 
      tempoEvento, 
      -1, 
      -1, 
      -1, 
      TransportePacotes,
      nullptr
    );
  }

  if(evento != nullptr){
    ULLI chave = gerarChave(tempoEvento, evento);
    novo = new HeapItem<Evento>(chave, evento);
  }
  
  if(novo != nullptr)
    eventos.Inserir(*novo);

  this->quantidadeEventos++;
}

void Escalonador::simularProximoEvento(){
  HeapItem<Evento> prox = eventos.Remover();
  Evento evento = *prox.value;

  quantidadeEventos--;

  if(evento.tipo == PostagemPacote){
    cout << "1" << endl;
    addEvento(evento.tempoEvento, evento.pacote, ArmazenamentoPacote);
    
    if(primeiroPacotePostado){
      primeiroPacotePostado = false; 
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacotes);
    }
  }
  else if(evento.tipo == ArmazenamentoPacote){
    cout << "2" << endl;
    // TODO: validar se o pacote chegou no armazem destino (gerar evento de entrega) 
    //       ou em um armazém de transporte (gerar evento de armazenamento)
    rede->addPacote(evento.idArmazemOrigem, evento.idArmazemDestino, evento.pacote);
    // _log(*rede);
  }
  else if(evento.tipo == TransportePacotes){
    cout << "3" << endl;
    // cout << "Transporte: " << evento.tempoEvento << endl;
  }

}