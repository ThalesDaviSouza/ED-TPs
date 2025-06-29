#include "../include/package.hpp"

Package::Package(int id) : id(id) {}

void Package::addEvent(const Event& event) {
    events.push_back(event);
}

const List<Event>& Package::getEvents() const {
    return events;
}

Event Package::getLastEvent() const {
    if(events.empty()) {
        throw std::runtime_error("Pacote " + std::to_string(id) + " não possui eventos");
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
    if (events.getSize() == 0) return "No events";
    
    Event last = getLastEvent();
    switch (last.type) {
        case RG: return "Registered";
        case AR: return "Stored in warehouse " + std::to_string(last.destinationWarehouse) + 
                       ", section " + std::to_string(last.destinationSection);
        case RM: return "Removed from warehouse " + std::to_string(last.originWarehouse);
        case UR: return "Restored in warehouse " + std::to_string(last.destinationWarehouse);
        case TR: return "In transit from warehouse " + std::to_string(last.originWarehouse) + 
                      " to warehouse " + std::to_string(last.destinationWarehouse);
        case EN: return "Delivered to warehouse " + std::to_string(last.destinationWarehouse);
        default: return "Unknown status";
    }
}