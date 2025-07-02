#include "logistics_system.hpp"
#include "event.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << endl;
        return 1;
    }

    LogisticsSystem system;
    string line;
    ifstream inputFile(argv[1]); // Abre o arquivo de entrada

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << argv[1] << endl;
        return 1;
    }

    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        if (line.find("EV") != string::npos) {
            try {
                Event event = Event::fromString(line);
                system.processEvent(event);
            } 
            catch (const exception& e) {
                cerr << "Erro ao processar evento: " << e.what() << endl;
                cerr << "Linha: " << line << endl;
            }
        } 
        else if (line.find("PC") != string::npos || line.find("CL") != string::npos) {
            system.processQuery(line);
        }
    }

    inputFile.close(); // Fecha o arquivo
    return 0;
}