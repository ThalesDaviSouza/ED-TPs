#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "heap.hpp"
#include "rede.hpp"

enum TipoEvento{
  // quando o pacote acabou de ser postado
  PostagemPacote, 
  // Pacote chegou e foi armazenado no armázem
  ArmazenamentoPacote, 
  // Pacote foi removida de uma seção do armázem
  RemocaoPacote, 
  // Pacote foi pra pilha auxiliar mas não teve espaço no transporte
  RealocacaoPacote,
  // Transporte de Todos os pacotes 
  // Toda vez que é executado, agenda outro automaticamente para o próximo ciclo
  TransportePacotes, 
  // Pacote está sendo transferido entre armázens
  TransportePacote, 
  // Pacote foi entregue na unidade destino 
  EntregaPacote 
};

class Evento{
public:
  int idPacote;
  int tempoEvento;
  int idArmazemOrigem;
  int idSecao; // Para eventos de armazenamento e remoção
  int idArmazemDestino;
  TipoEvento tipo;
  Pacote* pacote; // Auxiliar para caso de postagem de pacote

  Evento(
    int idPacote,
    int tempoEvento,
    int idArmazemOrigem,
    int idSecao,
    int idArmazemDestino,
    TipoEvento tipo
  ) :
  idPacote(idPacote),
  tempoEvento(tempoEvento),
  idArmazemOrigem(idArmazemOrigem),
  idSecao(idSecao),
  idArmazemDestino(idArmazemDestino),
  tipo(tipo) { }

  Evento(
    int idPacote,
    int tempoEvento,
    int idArmazemOrigem,
    int idSecao,
    int idArmazemDestino,
    TipoEvento tipo,
    Pacote* pacote
  ) :
  idPacote(idPacote),
  tempoEvento(tempoEvento),
  idArmazemOrigem(idArmazemOrigem),
  idSecao(idSecao),
  idArmazemDestino(idArmazemDestino),
  tipo(tipo),
  pacote(pacote) { }

  ~Evento() { }
};

class Escalonador{
public:
  Escalonador(int numPacotes, Rede* rede, int intervaloTransporte, int custoRemocao, int custoTransporte);
  ~Escalonador();

  void simularProximoEvento();
  void addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo);

  Heap<Evento> eventos;
  int quantidadeEventos;
  int pacotesAtivos;
  int intervaloTransporte;
  int custoRemocao;
  int tempoUltimoEvento;
  int custoTransporte;
  
private:
  Rede* rede;
  bool primeiroPacotePostado;

  ULLI gerarChave(int tempo, Evento* evento);
  void ProcessarChegadaTransporte(int idArmazemOrigem, int idArmazemDestino);

};

#endif