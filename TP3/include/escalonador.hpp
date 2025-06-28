#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "heap.hpp"
#include "rede.hpp"

/// Enumeração que representa os tipos possíveis de eventos que ocorrem no sistema logístico.
/// Esses eventos são utilizados na simulação com base no modelo de eventos discretos.
enum TipoEvento{
  PostagemPacote,       ///< Quando o pacote é postado inicialmente no sistema.
  ArmazenamentoPacote,  ///< Quando o pacote é armazenado em uma seção do armazém.
  RemocaoPacote,        ///< Quando o pacote é removido de uma seção para ser transportado.
  RealocacaoPacote,     ///< Quando o pacote é movido para uma pilha auxiliar por falta de espaço no transporte.
  TransportePacotes,    ///< Evento global que processa todos os transportes no tempo atual. Agenda o próximo transporte.
  TransportePacote,     ///< Quando um pacote está sendo transferido de um armazém para outro.
  EntregaPacote         ///< Quando o pacote é finalmente entregue no armazém de destino.
};

/// Classe que representa um evento na fila de eventos do sistema.
/// Contém todos os dados necessários para executar e reagendar os próximos passos da simulação.
class Evento{
public:
  int idPacote;            ///< ID do pacote associado ao evento.
  int tempoEvento;         ///< Tempo (em horas desde referência) em que o evento deve ocorrer.
  int idArmazemOrigem;     ///< ID do armazém de origem (usado em transporte, remoção, etc).
  int idSecao;             ///< ID da seção associada (útil em eventos de armazenamento e remoção).
  int idArmazemDestino;    ///< ID do armazém de destino (para eventos de transporte e entrega).
  TipoEvento tipo;         ///< Tipo do evento (enum).
  Pacote* pacote;          ///< Ponteiro para o pacote envolvido no evento (usado na postagem).

  /// Construtor básico do evento, sem pacote associado (exceto quando necessário).
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

  /// Construtor com pacote associado.
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

/// Classe responsável pela simulação baseada em eventos discretos.
/// Controla o relógio do sistema e a fila de eventos priorizada por tempo.
class Escalonador{
public:
  /// Construtor que inicializa o escalonador com os parâmetros do sistema e referência à rede de armazéns.
  Escalonador(int numPacotes, Rede* rede, int intervaloTransporte, int custoRemocao, int custoTransporte);

  ~Escalonador();

  /// Executa o próximo evento da fila, avançando o tempo do sistema.
  void simularProximoEvento();

  /// Adiciona um novo evento à fila de eventos.
  void addEvento(int tempoEvento, Pacote* pacote, TipoEvento tipo);

  Heap<Evento> eventos;       ///< Fila de prioridade dos eventos (implementada como min-heap).
  int quantidadeEventos;      ///< Número total de eventos já processados ou adicionados.
  int pacotesAtivos;          ///< Contador de pacotes ainda em trânsito (não entregues).
  int intervaloTransporte;    ///< Intervalo entre ciclos de transporte.
  int custoRemocao;           ///< Custo associado à remoção de pacotes de uma pilha.
  int tempoUltimoEvento;      ///< Marca o tempo do último evento processado.
  int custoTransporte;        ///< Tempo de transporte entre dois armazéns (latência).

private:
  Rede* rede;                 ///< Referência para a rede de armazéns (grafo).
  bool primeiroPacotePostado;///< Indica se já houve a postagem de algum pacote (usado para iniciar transporte recorrente).

  /// Gera uma chave única para o evento, usada na ordenação da fila de prioridade.
  ULLI gerarChave(int tempo, Evento* evento);

  /// Processa a chegada de um transporte entre dois armazéns.
  void ProcessarChegadaTransporte(int idArmazemOrigem, int idArmazemDestino);
};

#endif
