#ifndef ARMAZEM_H
#define ARMAZEM_H

#include "pilha.hpp"
#include "list.hpp"
#include "pacote.hpp"

/// Representa uma seção de um armazém, responsável por armazenar pacotes com destino a um armazém específico.
/// Cada seção funciona como uma pilha (LIFO) de pacotes.
class Secao{
public:
  int idArmazemDestino;  ///< ID do armazém para o qual os pacotes dessa seção serão enviados.
  Pilha<Pacote>* pacotes; ///< Pilha de pacotes armazenados na seção.

  /// Construtor da seção, recebe o ID do armazém de destino e inicializa a pilha de pacotes.
  Secao(int idArmazemDestino)
  : idArmazemDestino(idArmazemDestino), pacotes(Pilha<Pacote>::createPilha()) { }
};

/// Representa um armazém da rede, contendo múltiplas seções.
/// Cada seção está associada a um armazém vizinho no grafo e gerencia pacotes com destino a ele.
class Armazem{
public:
  int numSecoes;           ///< Número de seções (ou seja, de conexões com outros armazéns).
  List<Secao>* secoes;     ///< Lista encadeada de seções (cada uma ligada a um armazém vizinho).

  /// Construtor padrão: cria um armazém vazio, sem seções.
  Armazem() : numSecoes(0), secoes(nullptr) { }

  /// Construtor que inicializa o armazém com as seções baseadas no vetor de armazéns de destino (grafo de conexões).
  Armazem(int numSecoes, int* armazensDestino);

  /// Destrutor responsável por liberar memória alocada para as seções e suas pilhas.
  ~Armazem();

  /// Adiciona uma nova seção ao armazém, ligada a um armazém de destino.
  void addSecao(int idArmazemDestino);

  /// Armazena um pacote na seção correspondente ao seu próximo armazém na rota.
  /// Se a seção ainda não existir, o comportamento dependerá da implementação (provavelmente ignora ou adiciona).
  void ArmazenarPacote(Pacote& pacote);
};

#endif
