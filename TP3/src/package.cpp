#include "../include/package.hpp"

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

    // Método 1: Usando getLastNode()
    try {
        auto lastNode = events.getLastNode();
        return lastNode->data;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao acessar último evento: " << e.what() << std::endl;
        throw;
    }

    // Método alternativo: Usando iteradores
    /*
    auto it = events.begin();
    if (!it.isValid()) {
        throw std::runtime_error("Iterador inválido para pacote " + std::to_string(id));
    }
    return *it;
    */
}

int Package::getId() const {
    return id;
}

std::string Package::getCurrentStatus() const {
    if (events.getSize() == 0) return "Sem eventos";
    
    Event last = getLastEvent();
    if (last.packageId == -1) return "Pacote inválido";
    
    switch (last.type) {
        case RG: return "Registrado";
        case AR: return "Armazenado no armazem " + std::to_string(last.destinationWarehouse) + 
                       ", secao " + std::to_string(last.destinationSection);
        case RM: return "Removido do armazem " + std::to_string(last.originWarehouse);
        case UR: return "Rearmazenado no armazem " + std::to_string(last.destinationWarehouse);
        case TR: return "Em transito do armazem " + std::to_string(last.originWarehouse) + 
                      " para o armazem " + std::to_string(last.destinationWarehouse);
        case EN: return "Entregue no armazem " + std::to_string(last.destinationWarehouse);
        default: return "Status desconhecido";
    }
}