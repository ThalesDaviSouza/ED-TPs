#ifndef REDE_H
#define REDE_H

#include "armazem.hpp"
#include "pacote.hpp"
#include "list.hpp"

enum VisitadoStatus{
  naoVisto = -1,
  visitado = 1,
};

class Rede{
public:
  int capacidadeTransporte;
  int numArmazens;  
  Armazem* armazens;
  int** conexoes;

  Rede(int numArmazens, int capacidadeTransporte);
  ~Rede();

  void addSecao(int idArmazem, int idArmazemDestino);
  void addPacote(int idArmazem, int idArmazemDestino, Pacote* pacote);

private:
  List<int>* calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino);
  Pilha<int>* _calcularRotaPacote(int idArmazemOrigem, int idArmazemDestino, int* visitados);

};

#endif