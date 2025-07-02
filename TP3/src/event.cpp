#include "event.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

Event::Event(
    int timestamp, 
    EventType type, 
    int packageId, 
    const string& sender, 
    const string& receiver,
    int originWarehouse, 
    int destinationWarehouse,
    int destinationSection
): 
    timestamp(timestamp), 
    type(type), 
    packageId(packageId),
    sender(sender), 
    receiver(receiver),
    originWarehouse(originWarehouse), 
    destinationWarehouse(destinationWarehouse),
    destinationSection(destinationSection) 
{}

EventType Event::parseEventType(const string& typeStr) {
    if (typeStr == "RG") return RG;
    if (typeStr == "AR") return AR;
    if (typeStr == "RM") return RM;
    if (typeStr == "UR") return UR;
    if (typeStr == "TR") return TR;
    if (typeStr == "EN") return EN;
    throw invalid_argument("Tipo de evento invalido");
}

Event Event::fromString(const string& line) {
    istringstream iss(line);
    string token;
    
    // Ler timestamp
    getline(iss, token, ' ');
    int timestamp = stoi(token);
    
    // Ler tipo (EV)
    getline(iss, token, ' ');
    
    // Ler tipo de evento
    getline(iss, token, ' ');
    EventType type = parseEventType(token);
    
    // Ler ID do pacote
    getline(iss, token, ' ');
    int packageId = stoi(token);
    
    // Restante dos campos dependem do tipo de evento
    string sender, receiver;
    int originWarehouse = -1;
    int destinationWarehouse = -1;
    int destinationSection = -1;
    
    if (type == RG) {
        getline(iss, sender, ' ');
        getline(iss, receiver, ' ');
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } else if (type == AR) {
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationSection = stoi(token);
    } else if (type == RM || type == UR) {
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } else if (type == TR) {
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } else if (type == EN) {
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    }
    
    Event retorno = Event(
        timestamp, 
        type, 
        packageId, 
        sender, 
        receiver, 
        originWarehouse, 
        destinationWarehouse, 
        destinationSection
    ); 
    
    return retorno;
}

Event::Event(const Event& other) :
    timestamp(other.timestamp),
    type(other.type),
    packageId(other.packageId),
    sender(other.sender),
    receiver(other.receiver),
    originWarehouse(other.originWarehouse),
    destinationWarehouse(other.destinationWarehouse),
    destinationSection(other.destinationSection) {}