#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

enum EventType { RG, AR, RM, UR, TR, EN };

class Event {
public:
    int timestamp;
    EventType type;
    int packageId;
    std::string sender;
    std::string receiver;
    int originWarehouse;
    int destinationWarehouse;
    int destinationSection;

    Event(int timestamp, EventType type, int packageId, 
          const std::string& sender = "", const std::string& receiver = "",
          int originWarehouse = -1, int destinationWarehouse = -1,
          int destinationSection = -1);
    
    static EventType parseEventType(const std::string& typeStr);
    static Event fromString(const std::string& line);
};

#endif // EVENT_HPP