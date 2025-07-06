#include "client.hpp"

using namespace std;

/**
 * Inicializa um novo cliente com o nome especificado
 */
Client::Client(const string& name) : name(name) {}

/**
 * Armazena o ID de um pacote onde este cliente é o remetente
 */
void Client::addSenderPackage(int packageId) {
    senderPackages.push_back(packageId);
}

/**
 * Armazena o ID de um pacote onde este cliente é o destinatário
 */
void Client::addReceiverPackage(int packageId) {
    receiverPackages.push_back(packageId);
}

/**
 * Permite acesso ao nome do cliente sem possibilidade de modificação
 */
const string& Client::getName() const {
    return name;
}

/**
 * Retorna todos os pacotes onde este cliente é o remetente
 */
const List<int>& Client::getSenderPackages() const {
    return senderPackages;
}

/**
 * Retorna todos os pacotes onde este cliente é o destinatário
 */
const List<int>& Client::getReceiverPackages() const {
    return receiverPackages;
}