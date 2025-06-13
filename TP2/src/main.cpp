#include <iostream>
#include <fstream>
#include <string>

#include "pacote.hpp"
#include "list.hpp"
#include "pilha.hpp"
#include "armazem.hpp"
#include "heap.hpp"
#include "rede.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char* argv[]){
  if(argc < 2){
    cerr << "Faltaram parâmetros para rodar o programa.";
    return 1;
  }

  std::string nomeArquivo = argv[1];
  std::ifstream arquivo(nomeArquivo);

  if(!arquivo.is_open()){
    cerr << "Houve um erro ao abrir o arquivo";
    return 1;
  }

  int capacidadeTransporte;
  int custoTransporte;
  int intervaloTransporte;
  int custoRemocao;
  int numeroArmazens;
  
  arquivo >> capacidadeTransporte;
  arquivo >> custoTransporte;
  arquivo >> intervaloTransporte;
  arquivo >> custoRemocao;
  arquivo >> numeroArmazens;
  
  _log(capacidadeTransporte);
  _log(custoTransporte);
  _log(intervaloTransporte);
  _log(custoRemocao);
  _log(numeroArmazens);
  
  Rede r(numeroArmazens, capacidadeTransporte);

  for(int i = 0; i < numeroArmazens; i++){
    for(int j = 0; j < numeroArmazens; j++){
      arquivo >> r.conexoes[i][j];
    }
  }

  _log(r);

  // TODO: ler os pacotes

  return 0;
}