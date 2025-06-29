#include "../include/event.hpp"
#include <sstream>
#include <stdexcept>

Event::Event(int timestamp, EventType type, int packageId, 
             const std::string& sender, const std::string& receiver,
             int originWarehouse, int destinationWarehouse,
             int destinationSection)
    : timestamp(timestamp), type(type), packageId(packageId),
      sender(sender), receiver(receiver),
      originWarehouse(originWarehouse), destinationWarehouse(destinationWarehouse),
      destinationSection(destinationSection) {}

EventType Event::parseEventType(const std::string& typeStr) {
    if (typeStr == "RG") return RG;
    if (typeStr == "AR") return AR;
    if (typeStr == "RM") return RM;
    if (typeStr == "UR") return UR;
    if (typeStr == "TR") return TR;
    if (typeStr == "EN") return EN;
    throw std::invalid_argument("Invalid event type");
}

Event Event::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    
    // Ler timestamp
    std::getline(iss, token, ' ');
    int timestamp = std::stoi(token);
    
    // Ler tipo (EV)
    std::getline(iss, token, ' ');
    
    // Ler tipo de evento
    std::getline(iss, token, ' ');
    EventType type = parseEventType(token);
    
    // Ler ID do pacote
    std::getline(iss, token, ' ');
    int packageId = std::stoi(token);
    
    // Restante dos campos dependem do tipo de evento
    std::string sender, receiver;
    int originWarehouse = -1, destinationWarehouse = -1, destinationSection = -1;
    
    if (type == RG) {
        std::getline(iss, sender, ' ');
        std::getline(iss, receiver, ' ');
        std::getline(iss, token, ' ');
        originWarehouse = std::stoi(token);
        std::getline(iss, token, ' ');
        destinationWarehouse = std::stoi(token);
    } else if (type == AR) {
        std::getline(iss, token, ' ');
        originWarehouse = std::stoi(token);
        std::getline(iss, token, ' ');
        destinationWarehouse = std::stoi(token);
        std::getline(iss, token, ' ');
        destinationSection = std::stoi(token);
    } else if (type == RM || type == UR) {
        std::getline(iss, token, ' ');
        originWarehouse = std::stoi(token);
        std::getline(iss, token, ' ');
        destinationWarehouse = std::stoi(token);
    } else if (type == TR) {
        std::getline(iss, token, ' ');
        originWarehouse = std::stoi(token);
        std::getline(iss, token, ' ');
        destinationWarehouse = std::stoi(token);
    } else if (type == EN) {
        std::getline(iss, token, ' ');
        destinationWarehouse = std::stoi(token);
    }
    
    return Event(timestamp, type, packageId, sender, receiver, 
                originWarehouse, destinationWarehouse, destinationSection);
}