#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

using namespace std;

// Tipos possíveis de eventos logísticos
enum EventType { 
    RG, // Registro
    AR, // Armazenamento
    RM, // Remoção
    UR, // Rearmazenamento
    TR, // Transferência
    EN  // Entrega
};

// Classe que representa um evento relacionado a um pacote
class Event {
public:
    int timestamp;                  // Momento do evento (formato numérico)
    EventType type;                 // Tipo do evento
    int packageId;                  // ID do pacote relacionado

    // Campos específicos dependendo do tipo do evento:
    string sender;                  // Nome do remetente (para RG)
    string receiver;                // Nome do destinatário (para RG)
    int originWarehouse;           // Armazém de origem (usado em vários tipos)
    int destinationWarehouse;      // Armazém de destino (usado em vários tipos)
    int destinationSection;        // Seção do armazém de destino (usado em AR)

    // Construtor completo com valores padrão para campos opcionais
    Event(int timestamp, EventType type, int packageId, 
          const string& sender = "", const string& receiver = "",
          int originWarehouse = -1, int destinationWarehouse = -1,
          int destinationSection = -1);
    
    // Construtor de cópia
    Event(const Event& other);

    // Converte uma string como "RG", "AR", etc. em EventType
    static EventType parseEventType(const string& typeStr);

    // Cria um evento a partir de uma linha de entrada (string)
    static Event fromString(const string& line);
};

#endif // EVENT_HPP
