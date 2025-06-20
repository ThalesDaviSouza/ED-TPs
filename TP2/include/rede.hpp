#ifndef REDE_H
#define REDE_H

#include "list.hpp"
#include "pacote.hpp"
#include "armazem.hpp"

/// @brief Status de visitação usado na busca de rotas.
/// Utilizado para evitar ciclos na busca de caminhos entre armazéns.
enum VisitadoStatus{
  naoVisto = -1,  ///< Armazém ainda não visitado na busca.
  visitado = 1    ///< Armazém já visitado.
};

/// @brief Representa a rede logística dos armazéns, funcionando como um grafo.
/// Armazena conexões, armazéns e lógica de roteamento dos pacotes.
class Rede{
public:
  int capacidadeTransporte;   ///< Quantidade máxima de pacotes transportados por ciclo.
  int numArmazens;            ///< Quantidade total de armazéns na rede.
  Armazem* armazens;          ///< Vetor com todos os armazéns da rede.
  int** conexoes;             ///< Matriz de adjacência (0/1) representando as conexões entre armazéns.

  /// Construtor da rede.
  /// @param numArmazens Quantidade de armazéns na rede.
  /// @param capacidadeTransporte Capacidade de transporte por operação.
  Rede(int numArmazens, int capacidadeTransporte);

  /// Destrutor da rede: libera memória dos armazéns e da matriz de conexões.
  ~Rede();

  /// Adiciona uma seção no armazém indicado, ligando-o ao destino.
  /// Essa seção representa uma pilha onde pacotes destinados ao armazém destino serão armazenados.
  void addSecao(int idArmazem, int idArmazemDestino);

  /// Adiciona um pacote a um armazém de origem e define sua rota até o destino.
  void addPacote(int idArmazem, int idArmazemDestino, Pacote* pacote);

private:
  /// Calcula a rota (lista encadeada) entre dois armazéns.
  /// Algoritmo de busca usado: DFS ou BFS com marcação de visitados (implementado com pilha).
  List<int>* calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino);

  /// Função auxiliar recursiva que realiza a busca de rota.
  /// Retorna uma pilha com o caminho do destino até a origem (que depois pode ser invertido).
  Pilha<int>* _calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino, int* visitados);
};

#endif
