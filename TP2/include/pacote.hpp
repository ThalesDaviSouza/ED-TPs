#ifndef PACOTE
#define PACOTE

using namespace std;

#include <string>
#include "list.hpp"

/// @brief Possíveis estados do pacote
enum TipoPacote{
  None = 0,
  Postado = 1,
  Chegou = 2,
  Armazenado = 3,
  Alocado = 4,
  Entregue = 5
};

/// @brief Representa cada no da rota do pacote até o destino
class RotaNo{
public:
  int idArmazem;
  int chegada;
  int partida;
  int espera;
  int tempoTransporte;

  RotaNo(
    int idArmazem, 
    int chegada, 
    int partida, 
    int espera, 
    int tempoTransporte
  ): 
    idArmazem(idArmazem), 
    chegada(chegada), 
    partida(partida), 
    espera(espera), 
    tempoTransporte(tempoTransporte) 
  { }
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
  List<RotaNo>* Rotas;

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
    Rotas(List<RotaNo>::createList()) { }

  ~Pacote();

};



#endif 
