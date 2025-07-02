#include "package.hpp"

using namespace std;

Package::Package(int id) : id(id) {}

int Package::getId() const {
    return id;
}

string Package::getCurrentStatus(const Event& lastEvent) const {
    switch (lastEvent.type) {
        case RG: 
            return "Registrado";
        case AR: 
            return "Armazenado no armazem " + to_string(lastEvent.destinationWarehouse) + 
                    ", secao " + to_string(lastEvent.destinationSection);
        case RM: 
            return "Removido do armazem " + to_string(lastEvent.originWarehouse);
        case UR: 
            return "Rearmazenado no armazem " + to_string(lastEvent.destinationWarehouse);
        case TR: 
            return "Em transito do armazem " + to_string(lastEvent.originWarehouse) + 
                    " para o armazem " + to_string(lastEvent.destinationWarehouse);
        case EN: 
            return "Entregue no armazem " + to_string(lastEvent.destinationWarehouse);
        default: 
            return "Status desconhecido";
    }
}