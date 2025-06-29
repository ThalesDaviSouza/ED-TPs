#include "../include/package.hpp"

Package::Package(int id) : id(id) {}

void Package::addEvent(const Event& event) {
    events.push_back(event);
}

const List<Event>& Package::getEvents() const {
    return events;
}

// Event Package::getLastEvent() const {
//     std::cout << "DEU RUIM" << std::endl;
//     if (events.getSize() == 0) {
//         throw std::runtime_error("No events for package");
//     }
//     std::cout << "DEU RUIM2" << std::endl;
//     std::cout << "Quantidade de eventos: " << events.getSize() << std::endl;
    
//     // Inicializamos com o primeiro evento
//     auto test = events.begin();
//     std::cout << "DEU RUIM 1/2" << std::endl;
//     auto test2 = *events.begin();
//     std::cout << "DEU RUIM 2/2" << std::endl;
    
//     Event lastEvent = *events.begin();  // Usando o iterador para acessar o primeiro elemento
//     std::cout << "DEU RUIM3" << std::endl;
    
//     // Percorremos o restante da lista
//     for (const auto& event : events) {
//         lastEvent = event;  // Atualizamos lastEvent a cada iteração
//     }

//     return lastEvent;
// }

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