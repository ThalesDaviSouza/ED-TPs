#include "logistics_system.hpp"
#include "event.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    // Verificação básica dos argumentos de linha de comando
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << endl;
        return 1;
    }

    // Sistema principal que armazenará os eventos e processará consultas
    LogisticsSystem system;
    string line;
    
    // Tenta abrir o arquivo especificado
    ifstream inputFile(argv[1]);

    // Verifica se o arquivo foi aberto com sucesso
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << argv[1] << endl;
        return 1;
    }

    // Processa cada linha do arquivo de entrada
    while (getline(inputFile, line)) {
        // Ignora linhas vazias para evitar processamento desnecessário
        if (line.empty()) continue;
        
        // Identifica e processa linhas de evento (começam com EV)
        if (line.find("EV") != string::npos) {
            try {
                // Converte a string para um objeto Event e adiciona ao sistema
                Event event = Event::fromString(line);
                system.processEvent(event);
            } 
            catch (const exception& e) {
                // Trata erros na conversão ou processamento de eventos
                cerr << "Erro ao processar evento: " << e.what() << endl;
                cerr << "Linha: " << line << endl;
            }
        } 
        // Identifica e processa linhas de consulta (começam com PC ou CL)
        else if (line.find("PC") != string::npos || line.find("CL") != string::npos) {
            // Encaminha a consulta diretamente para o sistema
            system.processQuery(line);
        }
    }

    // Fechamento do arquivo
    inputFile.close();
    return 0;
}