#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "heap.hpp"
#include "rede.hpp"

enum TipoEvento{
  PostagemPacote, // quando o pacote acabou de ser postado
  ArmazenamentoPacote, // Pacote chegou no e foi armazenado armázem
  RemocaoPacote, // Pacote foi removida de uma seção do armázem
  TransportePacote, // Pacote está sendo transferido entre armázens
  EntregaPacote // Pacote foi entregue na unidade destino 
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
  Escalonador(int numPacotes, Rede* rede);
  ~Escalonador();

  void simularProximoEvento();
  void addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo);

  Heap<Evento> eventos;
  int quantidadeEventos;

private:
  Rede* rede;

};

#endif