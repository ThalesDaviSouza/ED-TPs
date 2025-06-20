#ifndef PACOTE
#define PACOTE

using namespace std;

#include <string>
#include "list.hpp"

/// @brief Enumeração representando os possíveis estados de um pacote durante sua jornada logística.
enum TipoPacote{
  None = 0,        ///< Estado inicial, o pacote ainda não foi postado.
  Postado = 1,     ///< Pacote foi postado, mas ainda não chegou ao armazém.
  Chegou = 2,      ///< Pacote chegou em um armazém mas ainda não foi armazenado.
  Armazenado = 3,  ///< Pacote armazenado em uma seção do armazém.
  Alocado = 4,     ///< Pacote alocado para transporte (na fila de saída).
  Entregue = 5     ///< Pacote chegou ao destino final.
};

/// @brief Representa um pacote que será roteado entre os armazéns.
/// Contém todas as informações necessárias para controlar o fluxo, status e rota do pacote.
class Pacote{
public:
  int id;                   ///< ID sequencial único (gerado internamente).
  int idAux;                ///< ID auxiliar (informado no arquivo de entrada).
  int horaPostagem;         ///< Hora em que o pacote foi postado (referência do relógio).
  int tempoUltimoEvento;    ///< Hora do último evento processado para este pacote.
  string nomeRemetente;     ///< Nome do remetente.
  string nomeDestinatario;  ///< Nome do destinatário.
  TipoPacote tipo;          ///< Estado atual do pacote (enum TipoPacote).
  int idArmazemOrigem;      ///< ID do armazém onde o pacote foi postado.
  int idArmazemDestino;     ///< ID do armazém de destino final.
  int idArmazemAtual;       ///< ID do armazém atual onde o pacote se encontra (ou -1 se ainda não iniciou).
  int idSecaoAtual;         ///< ID da seção atual onde o pacote está armazenado (ou -1 se ainda não armazenado).
  List<int>* Rotas;         ///< Lista encadeada com os IDs dos armazéns que compõem a rota até o destino.

  /// Construtor do pacote.
  /// Inicializa todos os dados e cria a lista de rota vazia.
  Pacote(
    int id,
    int idAux,
    int horaPostagem, 
    int tempoUltimoEvento, 
    string remetente, 
    string destinatario, 
    TipoPacote tipo, 
    int idArmazemOrigem, 
    int idArmazemDestino
  ): 
    id(id),
    idAux(idAux),
    horaPostagem(horaPostagem), 
    tempoUltimoEvento(tempoUltimoEvento), 
    nomeRemetente(remetente), 
    nomeDestinatario(destinatario), 
    tipo(tipo), 
    idArmazemOrigem(idArmazemOrigem), 
    idArmazemDestino(idArmazemDestino), 
    idArmazemAtual(-1),      // Inicialmente, não se encontra em nenhum armazém
    idSecaoAtual(-1),        // Também não está armazenado em nenhuma seção
    Rotas(List<int>::createList()) { }

  ~Pacote(); // Pode ser implementado para limpar a lista de rotas, se necessário.
};

#endif
