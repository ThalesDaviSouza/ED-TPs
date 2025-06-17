#ifndef UTILS_H
#define UTILS_H

#include <iomanip>
#include <iostream>

using namespace std;

template<typename T>
void _log(const T& var){
  if constexpr (is_same<T, int>::value){
    cout << "[int]: " << var << endl;
  }
  else if constexpr (is_same<T, string>::value){
    cout << "[string]: " << var << endl;
  }
  else if constexpr (is_same<T, Rede>::value){
    cout << "[Rede]" << endl;
    cout << "CapacidadeTransporte: " << var.capacidadeTransporte;
    cout << " NumArmazens: " << var.numArmazens << endl;
    cout << "Conexoes: " << endl;

    for(int i = 0; i < var.numArmazens; i++){
      for(int j = 0; j < var.numArmazens; j++){
        cout << var.conexoes[i][j] << " ";
      }
      cout << endl;
    }

    cout << "Armazens: " << endl;
    for(int i = 0; i < var.numArmazens; i++){
      _log(var.armazens[i]);
    }

  }
  else if constexpr (is_same<T, Pacote>::value){
    int idAux = var.id % 1100;
    cout << setw(7) << setfill('0') << var.tempoUltimoEvento;
    cout << " pacote " << setw(3) << setfill('0') << idAux;
    cout << " origem " << setw(3) << setfill('0') << var.idArmazemOrigem;
    cout << " armazenado em " << setw(3) << setfill('0') << var.idArmazemAtual;
    cout << " destino para " << setw(3) << setfill('0') << var.idArmazemDestino << endl;
  }
  else if constexpr (is_same<T, Armazem>::value){
    cout << "[Armazem] num secoes: " << var.numSecoes << endl;
    
    if(var.secoes != nullptr){
      List<Secao>* aux = var.secoes;
      for(int i = 0; i < var.numSecoes; i++){
        // cout << "idDestino: " << aux->value->idArmazemDestino << endl;
        _log(*aux->value);
        aux = aux->next;
      }
    }
  }
  else if constexpr (is_same<T, Secao>::value){
    cout << "[Secao] Armazem Destino: " << var.idArmazemDestino << endl;
    Pilha<Pacote>* aux = var.pacotes;

    if(aux->value == nullptr){
      cout << "sem pacotes na pilha" << endl;
    }
    
    while(aux != nullptr && aux->value != nullptr){
      _log(*aux->value);
      aux = aux->next;
    }
    
  }
  else if constexpr (is_same<T, Escalonador>::value){
    cout << "[Escalonador] num eventos: " << var.quantidadeEventos << endl;
    
    for(int i = 0; i < var.quantidadeEventos; i++){
      Evento* aux = var.eventos.dados[i].value;
      _log(*aux);
    }
  }
  else if constexpr (is_same<T, Evento>::value){
    if(var.tipo == PostagemPacote){
      cout << "[Evento]"; 
      cout << " idPacote: " << var.idPacote;
      cout << " tempo evento: " << var.tempoEvento << endl;
    }
    else if(var.tipo == ArmazenamentoPacote){
      int idAux = var.idPacote % 1100;
      cout << setw(7) << setfill('0') << var.tempoEvento;
      cout << " pacote " << setw(3) << setfill('0') << idAux;
      cout << " armazenado em " << setw(3) << setfill('0') << var.idArmazemOrigem;
      cout << " na secao " << setw(3) << setfill('0') << var.idArmazemDestino << endl;
    }
  }
  else{
    cout << "demais" << endl;
  }
}

#endif