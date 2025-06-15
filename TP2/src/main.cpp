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
#include "escalonador.hpp"

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
  
  
  // TODO: Adicionar armázens lidos na rede
  Rede rede(numeroArmazens, capacidadeTransporte);
  
  for(int i = 0; i < numeroArmazens; i++){
    for(int j = 0; j < numeroArmazens; j++){
      arquivo >> rede.conexoes[i][j];
    }
  }
    
  int numPacotes;

  arquivo >> numPacotes;
  
  Escalonador escalonador = Escalonador(numPacotes, &rede);
  
  for(int i = 0; i < numPacotes; i++){
    int tempInicial;
    int idPacote;
    int idArmazemOriginal;
    int idArmazemDestino;
    // Var para ler as palavras presentes no arquivo de entrada que não serão usadas
    char aux[8];

    arquivo >> tempInicial >> aux >> idPacote >> aux >> idArmazemOriginal >> aux >> idArmazemDestino;
    Pacote pacote = Pacote(idPacote, tempInicial, tempInicial, "", "", Postado, idArmazemOriginal, idArmazemDestino);
    
    // TODO: Adicionar o evento no escalonador
    // TODO: A partir do evento no escalonador, adicionar o pacote na rede
    escalonador.addEvento(new Evento(pacote.id, pacote.horaPostagem, pacote.idArmazemOrigem, -1, pacote.idArmazemDestino, PostagemPacote), tempInicial);

  }

  // TODO: Simular os eventos

  return 0;
}