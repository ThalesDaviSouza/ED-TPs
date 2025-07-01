#include "logistics_system.hpp"
#include "event.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    LogisticsSystem system;
    string line;
    
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        if (line.find("EV") != string::npos) {
            try {
                Event event = Event::fromString(line);
                system.processEvent(event);
            } 
            catch (const exception& e) {
                cerr << "Erro ao processar evento: " << e.what() << endl;
                cerr << "Linha: " << line << endl;
            }
        } 
        else if (line.find("PC") != string::npos || line.find("CL") != string::npos) {
            system.processQuery(line);
        }
    }
    
    return 0;
}