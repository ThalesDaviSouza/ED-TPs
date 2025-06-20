#include "escalonador.hpp"
#include "utils.hpp"

#include <iostream>
using namespace std;

Escalonador::Escalonador(int numPacotes, Rede* rede, int intervaloTransporte, int custoRemocao, int custoTransporte) : 
  eventos(Heap<Evento>(3 * numPacotes)), // 3 vezes a quantidade de pacotes para ter uma folga 
  rede(rede), 
  pacotesAtivos(numPacotes), 
  intervaloTransporte(intervaloTransporte),
  quantidadeEventos(0),
  primeiroPacotePostado(true),
  custoRemocao(custoRemocao),
  custoTransporte(custoTransporte) { }

Escalonador::~Escalonador() {
  while(!eventos.Vazio()){
    delete eventos.Remover().value;
  }
}

ULLI Escalonador::gerarChave(int tempo, Evento* evento){
  ULLI chave;
  short digitoTipo = 1;
  ULLI digitoMeio = 0;

  if(evento->tipo == TransportePacotes){
    digitoTipo = 2;
  }
  else if(evento->tipo == TransportePacote){
    digitoMeio += (evento->pacote->idArmazemOrigem * 1000);
    digitoMeio += evento->pacote->idArmazemDestino;

    digitoTipo = 2;
  }
  else if(evento->tipo == RemocaoPacote){
    digitoMeio = 0;
    digitoTipo = 1;
  }
  else{
    int idAux = evento->pacote->id;
    digitoMeio = idAux;
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
    int idOrigem = -1;
    if(pacote->idSecaoAtual != -1){
      idOrigem = pacote->idSecaoAtual;
    }
    else{
      idOrigem = pacote->idArmazemOrigem;
    }

    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      idOrigem, 
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
  else if(tipo == RemocaoPacote){
    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemDestino, 
      RemocaoPacote,
      pacote
    );
  }
  else if(tipo == TransportePacote){
    List<int>* proxNoRota = pacote->Rotas;
    int proxArmazem = -1;

    while(*proxNoRota->value != pacote->idArmazemAtual){
      proxNoRota = proxNoRota->next;
    }
    proxNoRota = proxNoRota->next;
    proxArmazem = *proxNoRota->value;

    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      proxArmazem, 
      TransportePacote,
      pacote
    );
  }
  else if(tipo == RealocacaoPacote){
    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemAtual, 
      RealocacaoPacote,
      pacote
    );
  }
  else if(tipo == EntregaPacote){
    evento = new Evento(
      pacote->id, 
      tempoEvento, 
      pacote->idArmazemOrigem, 
      pacote->idArmazemDestino, 
      pacote->idArmazemAtual, 
      EntregaPacote,
      pacote
    );
  }

  if(evento != nullptr){
    ULLI chave = gerarChave(tempoEvento, evento);
    novo = new HeapItem<Evento>(chave, evento);
  }
  
  if(novo != nullptr)
    eventos.Inserir(*novo);

  this->quantidadeEventos++;

  if(tipo == TransportePacote){
    _log(*evento);
  }
}

void Escalonador::simularProximoEvento(){
  HeapItem<Evento> prox = eventos.Remover();
  Evento evento = *prox.value;
  tempoUltimoEvento = prox.value->tempoEvento;

  // _log(evento);

  quantidadeEventos--;

  if(evento.tipo == PostagemPacote){
    addEvento(evento.tempoEvento, evento.pacote, ArmazenamentoPacote);
    
    if(primeiroPacotePostado){
      primeiroPacotePostado = false; 
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacotes);
    }

    return;
  }
  else if(evento.tipo == ArmazenamentoPacote){

    bool alterarDestinoEvento = false;
    
    if(evento.pacote->Rotas->isVazio()){
      alterarDestinoEvento = true;
    }

    rede->addPacote(evento.idArmazemOrigem, evento.idArmazemDestino, evento.pacote);

    if(alterarDestinoEvento){
      evento.idArmazemDestino = evento.pacote->idSecaoAtual;
    }
    
    _log(evento);

  }
  else if(evento.tipo == TransportePacotes){
    // cout << "Transporte: " << evento.tempoEvento << endl;

    for(int i = 0; i < rede->numArmazens; i++){
      for(int j = 0; j < rede->armazens[i].numSecoes; j++){
        ProcessarChegadaTransporte(i, j);
      }
    }

    if(this->pacotesAtivos > 0){
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacotes);
    }
  }
  else if(evento.tipo == TransportePacote){
  
    List<int>* proxNoRota = evento.pacote->Rotas;
    int proxArmazem = -1;

    while(*proxNoRota->value != evento.pacote->idArmazemAtual){
      proxNoRota = proxNoRota->next;
    }
    proxNoRota = proxNoRota->next;
    if(proxNoRota != nullptr && !proxNoRota->isVazio() && *proxNoRota->value != evento.pacote->idArmazemDestino){
      addEvento(evento.tempoEvento + custoTransporte, evento.pacote, ArmazenamentoPacote);
    }
    else{
      addEvento(evento.tempoEvento + custoTransporte, evento.pacote, EntregaPacote);
    }
  }
  else if(evento.tipo == EntregaPacote){
    _log(evento);
    pacotesAtivos--;
  }

  // cout << "chave: " << prox.chave << " ";
  // _log(evento);

}

void Escalonador::ProcessarChegadaTransporte(int idArmazemOrigem, int idSecao){
  List<Secao>* secoes = this->rede->armazens[idArmazemOrigem].secoes;
  int count = 0;
  while(count < idSecao){
    secoes = secoes->next;
    count++;
  }

  if(secoes != nullptr){
    auto pacotes = secoes->value->pacotes;
    int numRemocoes = 1;
    int numPacotesEmTransito = 0;
    int tempoUltimaRemocao = 0;
    Pilha<Pacote>* pilhaAux = Pilha<Pacote>::createPilha();
    Pacote* pacoteAux = nullptr;

    /**
     * Roda o loop até limpar a pilha e cria os eventos de remoção
     */
    while (pacotes->value != nullptr)
    {
      pacoteAux = pacotes->value;
      pacotes = pacotes->remove(false);
      pilhaAux = pilhaAux->add(*pacoteAux);
            
      Evento evento = Evento(
        pacoteAux->id, 
        tempoUltimoEvento + (numRemocoes * custoRemocao), 
        pacoteAux->idArmazemOrigem, 
        pacoteAux->idArmazemDestino, 
        pacoteAux->idArmazemDestino, 
        RemocaoPacote,
        pacoteAux
      );
      
      _log(evento);

      numRemocoes++;
    }

    tempoUltimaRemocao = tempoUltimoEvento + ((numRemocoes-1) * custoRemocao);
    numPacotesEmTransito = 0;

    if(pacoteAux != nullptr){
      // Removo o pacoteAux da pilhaAux
      // para ser colocado em trânsito
      while(numPacotesEmTransito < rede->capacidadeTransporte){
        addEvento(tempoUltimaRemocao, pilhaAux->value, TransportePacote);
        pilhaAux = pilhaAux->remove(false);
        
        numPacotesEmTransito++;
      }

      // Quem não foi colocado em transito
      // é reamazenado
      while (pilhaAux->value != nullptr)
      {
        auto aux = pilhaAux->value;
        pilhaAux = pilhaAux->remove(false);
        pacotes = pacotes->add(*aux);

        Evento evento = Evento(
          aux->id, 
          tempoUltimaRemocao, 
          aux->idArmazemOrigem, 
          aux->idArmazemDestino, 
          aux->idArmazemAtual, 
          RealocacaoPacote,
          aux
        );

        _log(evento);

      }
    }
  }
}
