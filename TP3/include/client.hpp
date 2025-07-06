#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "list.hpp"
#include <string>

using namespace std;

// Classe que representa um cliente no sistema logístico
class Client {
private:
    string name;                   // Nome do cliente
    List<int> senderPackages;      // Lista de IDs de pacotes enviados por este cliente
    List<int> receiverPackages;    // Lista de IDs de pacotes recebidos por este cliente

public:
    // Construtor: inicializa o cliente com um nome
    Client(const string& name);
    
    // Adiciona um pacote à lista de pacotes enviados
    void addSenderPackage(int packageId);

    // Adiciona um pacote à lista de pacotes recebidos
    void addReceiverPackage(int packageId);
    
    // Retorna o nome do cliente
    const string& getName() const;

    // Retorna a lista de pacotes enviados
    const List<int>& getSenderPackages() const;

    // Retorna a lista de pacotes recebidos
    const List<int>& getReceiverPackages() const;
};

#endif // CLIENT_HPP
