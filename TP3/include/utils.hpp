#ifndef UTILS_H
#define UTILS_H

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

/// Função de log genérica: usada como caso genérico para tipos não tratados.
template<typename T>
inline void _log(const T&) {
  cout << "demais" << endl;
}

/// Log específico para inteiros.
inline void _log(const int& var) {
  cout << "[int]: " << var << endl;
}

/// Log específico para strings.
inline void _log(const string& var) {
  cout << "[string]: " << var << endl;
}

/// Log completo de um pacote.
/// Exibe informações do pacote como: tempo do último evento, id, origem, armazém atual e destino.
inline void _log(const Pacote& var) {
  cout << setw(7) << setfill('0') << var.tempoUltimoEvento;
  cout << " pacote " << setw(3) << setfill('0') << var.id;
  cout << " origem " << setw(3) << setfill('0') << var.idArmazemOrigem;
  cout << " armazenado em " << setw(3) << setfill('0') << var.idArmazemAtual;
  cout << " destino para " << setw(3) << setfill('0') << var.idArmazemDestino << endl;
}

/// Log de um armazém e suas seções.
/// Para cada seção, imprime o log correspondente.
inline void _log(const Armazem& var) {
  cout << "[Armazem] num secoes: " << var.numSecoes << endl;

  if (var.secoes != nullptr) {
    List<Secao>* aux = var.secoes;
    for (int i = 0; i < var.numSecoes; i++) {
      _log(*aux->value);
      aux = aux->next;
    }
  }
}

/// Log de uma seção (pilha de pacotes).
/// Imprime o armazém destino e todos os pacotes contidos na pilha.
inline void _log(const Secao& var) {
  cout << "[Secao] Armazem Destino: " << var.idArmazemDestino << endl;
  Pilha<Pacote>* aux = var.pacotes;

  if (aux->value == nullptr) {
    cout << "sem pacotes na pilha" << endl;
  }

  while (aux != nullptr && aux->value != nullptr) {
    _log(*aux->value);
    aux = aux->next;
  }
}

/// Log geral da rede.
/// Mostra a capacidade, quantidade de armazéns, a matriz de conexões e os dados dos armazéns.
inline void _log(const Rede& var) {
  cout << "[Rede]" << endl;
  cout << "CapacidadeTransporte: " << var.capacidadeTransporte;
  cout << " NumArmazens: " << var.numArmazens << endl;
  cout << "Conexoes: " << endl;

  for (int i = 0; i < var.numArmazens; i++) {
    for (int j = 0; j < var.numArmazens; j++) {
      cout << var.conexoes[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Armazens: " << endl;
  for (int i = 0; i < var.numArmazens; i++) {
    _log(var.armazens[i]);
  }
}

/// Log dos eventos presentes no escalonador.
/// Percorre a heap de eventos e imprime cada um.
inline void _log(const Escalonador& var) {
  cout << "[Escalonador] num eventos: " << var.quantidadeEventos << endl;

  for (int i = 0; i < var.quantidadeEventos; i++) {
    Evento* aux = var.eventos.dados[i].value;
    _log(*aux);
  }
}

/// Log de um evento individual, variando conforme o tipo do evento.
inline void _log(const Evento& var) {
  if (var.tipo == PostagemPacote) {
    // Evento de postagem de um novo pacote
    cout << "[Evento]";
    cout << " idPacote: " << var.idPacote;
    cout << " tempo evento: " << var.tempoEvento << endl;
  }
  else if (var.tipo == ArmazenamentoPacote) {
    // Evento de armazenamento do pacote em seção de armazém
    int idArmazemAtual = (var.pacote->idArmazemAtual == -1) ? var.pacote->idArmazemOrigem : var.pacote->idArmazemAtual;
    int idSecaoAtual = (var.pacote->idSecaoAtual == -1) ? var.pacote->idArmazemDestino : var.pacote->idSecaoAtual;

    cout << setw(7) << setfill('0') << var.tempoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.idPacote;
    cout << " armazenado em " << setw(3) << setfill('0') << idArmazemAtual;
    cout << " na secao " << setw(3) << setfill('0') << idSecaoAtual << endl;
  }
  else if (var.tipo == RemocaoPacote) {
    // Evento de remoção do pacote da seção para transporte
    cout << setw(7) << setfill('0') << var.tempoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.idPacote;
    cout << " removido de " << setw(3) << setfill('0') << var.pacote->idArmazemAtual;
    cout << " na secao " << setw(3) << setfill('0') << var.pacote->idSecaoAtual << endl;
  }
  else if (var.tipo == TransportePacote) {
    // Evento de pacote em trânsito entre armazéns
    cout << setw(7) << setfill('0') << var.tempoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.idPacote;
    cout << " em transito de " << setw(3) << setfill('0') << var.pacote->idArmazemAtual;
    cout << " para " << setw(3) << setfill('0') << var.idArmazemDestino << endl;
  }
  else if (var.tipo == RealocacaoPacote) {
    // Evento de tentativa de transporte falha, pacote volta à seção
    cout << setw(7) << setfill('0') << var.tempoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.idPacote;
    cout << " rearmazenado em " << setw(3) << setfill('0') << var.pacote->idArmazemAtual;
    cout << " na secao " << setw(3) << setfill('0') << var.pacote->idSecaoAtual << endl;
  }
  else if (var.tipo == EntregaPacote) {
    // Evento final: entrega do pacote ao destino
    cout << setw(7) << setfill('0') << var.tempoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.idPacote;
    cout << " entregue em " << setw(3) << setfill('0') << var.pacote->idSecaoAtual << endl;
  }
  else {
    // caso genérico para tipos de evento não tratados
    cout << "[Evento]";
    cout << " idPacote: " << var.idPacote;
    cout << " tempo evento: " << var.tempoEvento << endl;
  }
}

#endif
