#ifndef ARMAZEM_H
#define ARMAZEM_H

#include "pilha.hpp"
#include "list.hpp"
#include "pacote.hpp"

class Secao{
public:
  int idArmazemDestino;
  Pilha<Pacote>* pacotes;

  Secao(int idArmazemDestino)
  : idArmazemDestino(idArmazemDestino), pacotes(Pilha<Pacote>::createPilha()) { }
};

class Armazem{
public:
  int numSecoes;
  List<Secao>* secoes;

  Armazem() : numSecoes(0), secoes(nullptr) { }
  Armazem(int numSecoes, int* armazensDestino);
  ~Armazem();

  void addSecao(int idArmazemDestino);
  void ArmazenarPacote(Pacote& pacote);
  Pacote* RecuperarPacote(int idPacote, int idArmazemDestino);
};

#endif