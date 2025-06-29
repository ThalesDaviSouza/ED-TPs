#include "../include/logistics_system.hpp"
#include "../include/event.hpp"
#include <iostream>
#include <string>

int main() {
    LogisticsSystem system;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        
        if (line.find("EV") != std::string::npos) {
            Event event = Event::fromString(line);
            system.processEvent(event);
        } else if (line.find("PC") != std::string::npos || line.find("CL") != std::string::npos) {
            system.processQuery(line);
        }
    }
    
    return 0;
}