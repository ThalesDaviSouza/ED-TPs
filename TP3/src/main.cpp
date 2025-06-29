#include "../include/logistics_system.hpp"
#include "../include/event.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << argv[1] << std::endl;
        return 1;
    }
    else
    {
        LogisticsSystem system;
        std::string line;
        
        while (std::getline(inputFile, line)) {
            if (line.empty()) continue;
            
            if (line.find("EV") != std::string::npos) {
                try {
                    Event event = Event::fromString(line);
                    system.processEvent(event);
                } 
                catch (const std::exception& e) {
                    std::cerr << "Erro ao processar evento: " << e.what() << std::endl;
                    std::cerr << "Linha: " << line << std::endl;
                }
            } 
            else if (line.find("PC") != std::string::npos || line.find("CL") != std::string::npos) {
                system.processQuery(line);
            }
        }
        
    }

    inputFile.close();
    return 0;
}