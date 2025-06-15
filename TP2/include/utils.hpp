#ifndef UTILS_H
#define UTILS_H

#include <iomanip>

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
  }
  else if constexpr (is_same<T, Pacote>::value){
    cout << setw(7) << setfill('0') << var.tempoUltimoEvento;
    cout << " pacote " << setw(3) << setfill('0') << var.id;
    cout << " origem " << setw(3) << setfill('0') << var.idArmazemOrigem;
    cout << " armazenado em " << setw(3) << setfill('0') << var.idArmazemAtual;
    cout << " destino para " << setw(3) << setfill('0') << var.idArmazemDestino << endl;
  }
  else{
    cout << "demais" << endl;
  }
}

#endif