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
  // Verifica se foi passado o nome do arquivo como argumento
  if(argc < 2){
    cerr << "Faltaram parâmetros para rodar o programa.";
    return 1;
  }

  std::string nomeArquivo = argv[1];
  std::ifstream arquivo(nomeArquivo);

  // Verifica se o arquivo abriu corretamente
  if(!arquivo.is_open()){
    cerr << "Houve um erro ao abrir o arquivo";
    return 1;
  }

  // Lê parâmetros iniciais do arquivo: capacidade de transporte, custos, intervalo e número de armazéns
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
  
  // Inicializa a rede com a quantidade de armazéns e capacidade de transporte
  Rede rede(numeroArmazens, capacidadeTransporte);
  
  // Lê a matriz de conexões entre os armazéns, 1 indicando conexão direta
  for(int i = 0; i < numeroArmazens; i++){
    for(int j = 0; j < numeroArmazens; j++){
      arquivo >> rede.conexoes[i][j];

      if(rede.conexoes[i][j] == 1){
        // Adiciona uma seção na rede representando essa conexão
        rede.addSecao(i, j);  
      }
    }
  }
  
  int numPacotes;
  arquivo >> numPacotes;
  
  // Cria o escalonador, que irá controlar e simular os eventos da rede
  Escalonador escalonador = Escalonador(numPacotes, &rede, intervaloTransporte, custoRemocao, custoTransporte);
  
  // Lê os dados de cada pacote e agenda o evento de postagem inicial para cada um
  for(int i = 0; i < numPacotes; i++){
    int tempInicial;
    int idPacote;
    int idArmazemOriginal;
    int idArmazemDestino;
    // Variável auxiliar para ler palavras irrelevantes no arquivo
    char aux[8];

    // O arquivo possui linhas com o formato:
    // tempoInicial <alguma_palavra> idPacote <alguma_palavra> idArmazemOriginal <alguma_palavra> idArmazemDestino
    arquivo >> tempInicial >> aux >> idPacote >> aux >> idArmazemOriginal >> aux >> idArmazemDestino;

    // Cria um novo pacote com os dados lidos, status inicial Postado
    Pacote* pacote = new Pacote(
      i,
      idPacote,
      tempInicial,
      tempInicial,
      "", // remetente vazio por enquanto
      "", // destinatário vazio por enquanto
      Postado,
      idArmazemOriginal,
      idArmazemDestino
    );
    
    // Adiciona evento de postagem do pacote no tempo inicial indicado
    escalonador.addEvento(tempInicial, pacote, PostagemPacote);
  }

  // Loop principal que simula enquanto houver eventos na fila do escalonador
  while(escalonador.quantidadeEventos > 0){
    escalonador.simularProximoEvento();
  }

  return 0;
}
