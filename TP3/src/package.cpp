#include "package.hpp"

using namespace std;

Package::Package(int id) : id(id) {}

void Package::addEvent(const Event& event) {
    events.push_back(event);
}

const List<Event>& Package::getEvents() const {
    return events;
}

Event Package::getLastEvent() const {
    if (events.getSize() == 0) {
        // Retorna um evento inválido/vazio em vez de lançar exceção
        return Event(0, RG, -1);  // Timestamp 0, tipo RG, ID -1
    }

    try {
        auto lastNode = events.getLastNode();
        return lastNode->data;
    } catch (const exception& e) {
        cerr << "Erro ao acessar último evento: " << e.what() << endl;
        throw;
    }
}

int Package::getId() const {
    return id;
}

string Package::getCurrentStatus() const {
    if (events.getSize() == 0) 
        return "Sem eventos";
    
    Event last = getLastEvent();
    if (last.packageId == -1) 
        return "Pacote inválido";
    
    switch (last.type) {
        case RG: 
            return "Registrado";
        case AR: 
            return "Armazenado no armazem " + to_string(last.destinationWarehouse) + 
                    ", secao " + to_string(last.destinationSection);
        case RM: 
            return "Removido do armazem " + to_string(last.originWarehouse);
        case UR: 
            return "Rearmazenado no armazem " + to_string(last.destinationWarehouse);
        case TR: 
            return "Em transito do armazem " + to_string(last.originWarehouse) + 
                    " para o armazem " + to_string(last.destinationWarehouse);
        case EN: 
            return "Entregue no armazem " + to_string(last.destinationWarehouse);
        default: 
            return "Status desconhecido";
    }
}