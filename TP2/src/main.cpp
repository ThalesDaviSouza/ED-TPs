#include <iostream>
#include <fstream>
#include <string>

#include "pacote.hpp"
#include "list.hpp"
#include "pilha.hpp"
#include "heap.hpp"
#include "armazem.hpp"
#include "rede.hpp"
#include "escalonador.hpp"
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
  
  Rede rede(numeroArmazens, capacidadeTransporte);
  
  for(int i = 0; i < numeroArmazens; i++){
    for(int j = 0; j < numeroArmazens; j++){
      arquivo >> rede.conexoes[i][j];

      if(rede.conexoes[i][j] == 1){
        rede.addSecao(i, j);  
      }
    }
  }
  
  // _log(rede);
  
  int numPacotes;
  
  arquivo >> numPacotes;
  
  Escalonador escalonador = Escalonador(numPacotes, &rede, intervaloTransporte, custoRemocao);
  
  for(int i = 0; i < numPacotes; i++){
    int tempInicial;
    int idPacote;
    int idArmazemOriginal;
    int idArmazemDestino;
    // Var para ler as palavras presentes no arquivo de entrada que não serão usadas
    char aux[8];

    arquivo >> tempInicial >> aux >> idPacote >> aux >> idArmazemOriginal >> aux >> idArmazemDestino;
    Pacote* pacote = new Pacote(
      idPacote,
      tempInicial,
      tempInicial,
      "",
      "",
      Postado,
      idArmazemOriginal,
      idArmazemDestino
    );
    
    escalonador.addEvento(tempInicial, pacote, PostagemPacote);
    
  }
  // _log(escalonador);

  while(escalonador.quantidadeEventos > 0){
    escalonador.simularProximoEvento();
    // _log(escalonador);
  }

  // _log(rede);

  // TODO: Simular os eventos

  return 0;
}