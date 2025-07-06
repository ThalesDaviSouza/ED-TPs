#include "package.hpp"

using namespace std;

// Construtor: inicializa o pacote com o ID fornecido
Package::Package(int id) : id(id) {}

// Retorna o ID do pacote
int Package::getId() const {
    return id;
}

// Retorna uma string representando o status atual do pacote com base no último evento
string Package::getCurrentStatus(const Event& lastEvent) const {
    switch (lastEvent.type) {
        case RG: 
            // Registro do pacote
            return "Registrado";
        case AR: 
            // Armazenamento no destino especificado
            return "Armazenado no armazem " + to_string(lastEvent.destinationWarehouse) + 
                   ", secao " + to_string(lastEvent.destinationSection);
        case RM: 
            // Remoção do armazém de origem
            return "Removido do armazem " + to_string(lastEvent.originWarehouse);
        case UR: 
            // Rearmazenamento em outro armazém
            return "Rearmazenado no armazem " + to_string(lastEvent.destinationWarehouse);
        case TR: 
            // Em trânsito entre armazéns
            return "Em transito do armazem " + to_string(lastEvent.originWarehouse) + 
                   " para o armazem " + to_string(lastEvent.destinationWarehouse);
        case EN: 
            // Entrega no armazém de destino
            return "Entregue no armazem " + to_string(lastEvent.destinationWarehouse);
        default: 
            // Caso não reconhecido
            return "Status desconhecido";
    }
}
