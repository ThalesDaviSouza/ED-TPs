#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

using namespace std;

enum EventType { 
    RG, 
    AR, 
    RM, 
    UR, 
    TR, 
    EN 
};

class Event {
public:
    int timestamp;
    EventType type;
    int packageId;
    string sender;
    string receiver;
    int originWarehouse;
    int destinationWarehouse;
    int destinationSection;

    Event(int timestamp, EventType type, int packageId, 
          const string& sender = "", const string& receiver = "",
          int originWarehouse = -1, int destinationWarehouse = -1,
          int destinationSection = -1);
    
    // Construtor de cópia
    Event(const Event& other);
    
    static EventType parseEventType(const string& typeStr);
    static Event fromString(const string& line);
};

#endif // EVENT_HPP