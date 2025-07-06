#include "event.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

// Construtor que inicializa todos os atributos de um evento
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

// Converte string para o tipo de evento correspondente
EventType Event::parseEventType(const string& typeStr) {
    if (typeStr == "RG") return RG;       // Registro
    if (typeStr == "AR") return AR;       // Armazenamento
    if (typeStr == "RM") return RM;       // Remoção
    if (typeStr == "UR") return UR;       // Re-armazenamento
    if (typeStr == "TR") return TR;       // Transporte
    if (typeStr == "EN") return EN;       // Entrega
    throw invalid_argument("Tipo de evento invalido");
}

// Cria um Event a partir de uma string formatada
Event Event::fromString(const string& line) {
    istringstream iss(line);
    string token;
    
    // Extrai os campos básicos que todos os eventos têm
    getline(iss, token, ' ');
    int timestamp = stoi(token);
    
    getline(iss, token, ' ');
    
    getline(iss, token, ' ');
    EventType type = parseEventType(token);
    
    getline(iss, token, ' ');
    int packageId = stoi(token);
    
    // Inicializa campos opcionais com valores padrão
    string sender, receiver;
    int originWarehouse = -1;
    int destinationWarehouse = -1;
    int destinationSection = -1;
    
    // Extrai campos específicos para cada tipo de evento
    if (type == RG) {
        // RG tem remetente, destinatário e armazéns de origem/destino
        getline(iss, sender, ' ');
        getline(iss, receiver, ' ');
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } 
    else if (type == AR) {
        // AR tem armazéns e seção de destino
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationSection = stoi(token);
    } 
    else if (type == RM || type == UR) {
        // RM/UR tem apenas armazéns
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } 
    else if (type == TR) {
        // TR tem armazéns de origem/destino
        getline(iss, token, ' ');
        originWarehouse = stoi(token);
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    } 
    else if (type == EN) {
        // EN tem apenas armazém de destino
        getline(iss, token, ' ');
        destinationWarehouse = stoi(token);
    }
    
    // Cria e retorna o evento com os dados extraídos
    return Event(
        timestamp, 
        type, 
        packageId, 
        sender, 
        receiver, 
        originWarehouse, 
        destinationWarehouse, 
        destinationSection
    );
}

// Construtor de cópia - copia todos os campos do outro evento
Event::Event(const Event& other) :
    timestamp(other.timestamp),
    type(other.type),
    packageId(other.packageId),
    sender(other.sender),
    receiver(other.receiver),
    originWarehouse(other.originWarehouse),
    destinationWarehouse(other.destinationWarehouse),
    destinationSection(other.destinationSection) {}