#include "escalonador.hpp"
#include "utils.hpp"

#include <iostream>
using namespace std;

Escalonador::Escalonador(int numPacotes, Rede* rede, int intervaloTransporte, int custoRemocao, int custoTransporte) : 
  eventos(Heap<Evento>(2 * numPacotes)), // Inicializa heap com capacidade dobrada para eventos, garantindo espaço extra
  rede(rede), 
  pacotesAtivos(numPacotes), 
  intervaloTransporte(intervaloTransporte),
  quantidadeEventos(0),
  primeiroPacotePostado(true),
  custoRemocao(custoRemocao),
  custoTransporte(custoTransporte) { }

Escalonador::~Escalonador() {
  // Destrói todos os eventos ainda presentes na heap para evitar vazamentos de memória
  while(!eventos.Vazio()){
    delete eventos.Remover().value;
  }
}

ULLI Escalonador::gerarChave(int tempo, Evento* evento){
  ULLI chave;
  short digitoTipo = 1;
  ULLI digitoMeio = 0;

  // Gera uma chave numérica única combinando o tempo do evento,
  // um dígito representando o tipo do evento, e uma parte intermediária
  // que pode variar conforme o tipo para ordenação do heap conforme enunciado.
  // Essa chave é usada para organizar eventos na heap por prioridade.

  if(evento->tipo == TransportePacotes){
    digitoTipo = 2;
  }
  else if(evento->tipo == TransportePacote){
    int idOrigem = evento->pacote->idArmazemOrigem;
    int idDestino = evento->pacote->idArmazemDestino;
    if(evento->pacote->idArmazemAtual != -1){
      idOrigem = evento->pacote->idArmazemAtual;
    }
    if(evento->pacote->idSecaoAtual != -1){
      idDestino = evento->pacote->idSecaoAtual;
    }
    // Usa IDs de origem e destino para compor parte da chave
    digitoMeio += (idOrigem * 1000);
    digitoMeio += idDestino;

    digitoTipo = 2;
  }
  else{
    // Para os demais eventos, usa o id do pacote para parte da chave
    int idAux = evento->pacote->id;
    digitoMeio = idAux;
  }
  // Combina tempo, parte intermediária e tipo para formar chave
  chave = ((ULLI)tempo * 10000000) + (digitoMeio * 10) + digitoTipo; 
  
  return chave;
}

void Escalonador::addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo){
  HeapItem<Evento>* novo = nullptr;
  Evento* evento = nullptr;
  
  // Cria o evento conforme o tipo solicitado, preenchendo dados necessários.
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
    // Determina o local de origem para armazenamento (seção atual ou armazém origem)
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
    // Evento genérico para processar transporte em lote (sem pacote específico)
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
    // Para transporte individual, determina próximo armazém da rota
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

  // Se evento criado, insere no heap com a chave gerada para manter ordem de prioridade
  if(evento != nullptr){
    ULLI chave = gerarChave(tempoEvento, evento);
    novo = new HeapItem<Evento>(chave, evento);
  }
  
  if(novo != nullptr)
    eventos.Inserir(*novo);

  this->quantidadeEventos++;

  // Loga detalhes do evento transporte de pacote para monitoramento
  if(tipo == TransportePacote){
    _log(*evento);
  }
}

void Escalonador::simularProximoEvento(){
  // Remove o próximo evento com maior prioridade da heap
  HeapItem<Evento> prox = eventos.Remover();
  Evento evento = *prox.value;
  tempoUltimoEvento = prox.value->tempoEvento;

  quantidadeEventos--;

  if(evento.tipo == PostagemPacote){
    // Ao postar pacote, agenda armazenamento
    addEvento(evento.tempoEvento, evento.pacote, ArmazenamentoPacote);
    
    // Caso seja o primeiro pacote, agenda evento para transporte em lote
    if(primeiroPacotePostado){
      primeiroPacotePostado = false; 
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacotes);
    }

    return;
  }
  else if(evento.tipo == ArmazenamentoPacote){
    bool alterarDestinoEvento = false;
    
    // Se rota estiver vazia, indica alteração de destino para evento
    if(evento.pacote->Rotas->isVazio()){
      alterarDestinoEvento = true;
    }

    // Adiciona o pacote na rede na seção adequada
    rede->addPacote(evento.idArmazemOrigem, evento.idArmazemDestino, evento.pacote);

    if(alterarDestinoEvento){
      evento.idArmazemDestino = evento.pacote->idSecaoAtual;
    }
    
    _log(evento);

  }
  else if(evento.tipo == TransportePacotes){
    // Percorre todos armazéns e suas seções para processar transportes
    for(int i = 0; i < rede->numArmazens; i++){
      for(int j = 0; j < rede->armazens[i].numSecoes; j++){
        ProcessarChegadaTransporte(i, j);
      }
    }

    // Agenda próximo evento de transporte enquanto houver pacotes ativos
    if(this->pacotesAtivos > 0){
      addEvento(evento.tempoEvento + intervaloTransporte, nullptr, TransportePacotes);
    }
  }
  else if(evento.tipo == TransportePacote){
    // Evento transporte individual - verifica próxima etapa na rota
    List<int>* proxNoRota = evento.pacote->Rotas;
    int proxArmazem = -1;
    
    while(*proxNoRota->value != evento.pacote->idArmazemAtual){
      proxNoRota = proxNoRota->next;
    }
    proxNoRota = proxNoRota->next;

    // Se ainda não chegou no destino final, agenda armazenamento, senão agenda a entrega
    if(proxNoRota != nullptr && !proxNoRota->isVazio() && *proxNoRota->value != evento.pacote->idArmazemDestino){
      addEvento(evento.tempoEvento + custoTransporte, evento.pacote, ArmazenamentoPacote);
    }
    else{
      addEvento(evento.tempoEvento + custoTransporte, evento.pacote, EntregaPacote);
    }
  }
  else if(evento.tipo == EntregaPacote){
    // Log do evento de entrega e decrementa contagem de pacotes ativos
    _log(evento);
    pacotesAtivos--;
    
    // Libera memória do pacote
    delete evento.pacote;
  }
}

// Função complexa que processa a chegada dos pacotes em transporte em uma seção do armazém
void Escalonador::ProcessarChegadaTransporte(int idArmazemOrigem, int idSecao){
  List<Secao>* secoes = this->rede->armazens[idArmazemOrigem].secoes;
  int count = 0;
  
  // Navega até a seção específica no armazém
  while(count < idSecao){
    secoes = secoes->next;
    count++;
  }
  
  if(secoes != nullptr){
    Pilha<Pacote>* pacotes = secoes->value->pacotes;
    int numRemocoes = 1; // Contador para calcular tempos relativos dos eventos
    int numPacotesEmTransito = 0;
    int tempoUltimaRemocao = 0;
    Pilha<Pacote>* pilhaAux = Pilha<Pacote>::createPilha(); // Pilha auxiliar para manipular pacotes
    Pacote* pacoteAux = nullptr;

    // Loop para remover pacotes da pilha original, adicionando na auxiliar
    // e gerando eventos de remoção com tempo escalonado (incrementa custoRemocao)
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

    // Atualiza pilha de pacotes da seção após remoções
    secoes->value->pacotes = pacotes;

    tempoUltimaRemocao = tempoUltimoEvento + ((numRemocoes-1) * custoRemocao);
    numPacotesEmTransito = 0;

    if(pacoteAux != nullptr){
      // Enquanto houver capacidade e pacotes na pilha auxiliar,
      // agenda transporte dos pacotes
      while(numPacotesEmTransito < rede->capacidadeTransporte && pilhaAux->value != nullptr){
        addEvento(tempoUltimaRemocao, pilhaAux->value, TransportePacote);
        pilhaAux = pilhaAux->remove(false);

        numPacotesEmTransito++;
      }

      // Pacotes que não caberam no transporte são rearmanezados na pilha original
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

      // Atualiza pilha final da seção após rearmazenamento
      secoes->value->pacotes = pacotes;
    }
  }
}
