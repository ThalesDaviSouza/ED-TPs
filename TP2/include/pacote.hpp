#ifndef PACOTE
#define PACOTE

using namespace std;

#include <string>
#include "list.hpp"

enum TipoPacote{
  None = 0,
  Postado = 1,
  Chegou = 2,
  Armazenado = 3,
  Alocado = 4,
  Entregue = 5
};

class Pacote{
public:
  int id; 
  int horaPostagem;
  string nomeRemetente;
  string nomeDestinatario;
  TipoPacote tipo;
  int idArmazemOrigem;
  int idArmazemDestino;
  int idArmazemAtual;
  List<int>* Rotas;

  Pacote(
    int id,
    int horaPostagem, 
    string remetente, 
    string destinatario, 
    TipoPacote tipo, 
    int idArmazemOrigem, 
    int idArmazemDestino
  ): 
    id(id),
    horaPostagem(horaPostagem), 
    nomeRemetente(remetente), 
    nomeDestinatario(destinatario), 
    tipo(tipo), 
    idArmazemOrigem(idArmazemOrigem), 
    idArmazemDestino(idArmazemDestino), 
    idArmazemAtual(-1),
    Rotas(List<int>::createList()) { }

  ~Pacote();

};



#endif 
