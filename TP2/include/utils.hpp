#ifndef UTILS_H
#define UTILS_H

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
  else{
    cout << "demais" << endl;
  }
}

#endif