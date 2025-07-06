#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "event.hpp"
#include <iostream>

// Classe que representa um pacote no sistema logístico
class Package {
private:
    int id;  // Identificador único do pacote

public:
    // Construtor: inicializa o pacote com um ID
    Package(int id);
    
    // Retorna o ID do pacote
    int getId() const;

    // Retorna uma string representando o status atual do pacote com base no último evento
    std::string getCurrentStatus(const Event& lastEvent) const;
};

#endif // PACKAGE_HPP
