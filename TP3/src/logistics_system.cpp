#include "logistics_system.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

// Funções auxiliares para extração de chaves
int packageKeyFunc(Package* p) { 
    return p->getId(); 
}

string clientKeyFunc(Client* c) { 
    return c->getName(); 
}

LogisticsSystem::LogisticsSystem() : 
    packages(packageKeyFunc), 
    clients(clientKeyFunc) {}

LogisticsSystem::~LogisticsSystem() { }

Package* LogisticsSystem::getOrCreatePackage(int packageId) {
    Package* pkg = packages.search(packageId);
    if (!pkg) {
        pkg = new Package(packageId);
        packages.insert(pkg);
    }
    
    return pkg;
}

Client* LogisticsSystem::getOrCreateClient(const string& name) {
    Client* client = clients.search(name);
    if (!client) {
        client = new Client(name);
        clients.insert(client);
    }
    return client;
}

void LogisticsSystem::processEvent(const Event& event) {
    Package* pkg = getOrCreatePackage(event.packageId);
    pkg->addEvent(event);

    
    if (event.type == RG) {
        Client* sender = getOrCreateClient(event.sender);
        sender->addSenderPackage(event.packageId);
        
        Client* receiver = getOrCreateClient(event.receiver);
        receiver->addReceiverPackage(event.packageId);
    }
}

void LogisticsSystem::processQuery(const string& line) {
    istringstream iss(line);
    int timestamp;
    string type;
    
    iss >> timestamp >> type;
    
    // Imprime a linha da consulta
    cout << line << endl;
    
    if (type == "PC") {
        int packageId;
        iss >> packageId;
        List<Event> history = getPackageHistory(packageId);
        
        // Imprime o número de eventos
        cout << history.getSize() << endl;
        
        // Imprime cada evento
        for (const Event& event : history) {
            cout << setfill('0') << setw(7) << event.timestamp << " EV ";
            
            switch (event.type) {
                case RG: 
                    cout << "RG ";
                    break;
                case AR: 
                    cout << "AR ";
                    break;
                case RM: 
                    cout << "RM ";
                    break;
                case UR: 
                    cout << "UR ";
                    break;
                case TR: 
                    cout << "TR ";
                    break;
                case EN: 
                    cout << "EN ";
                    break;
            }
            
            cout << setfill('0') << setw(3) << event.packageId;
            
            if (event.type == RG) {
                cout << " " << event.sender << " " << event.receiver
                    << " " << setfill('0') << setw(3) << event.originWarehouse
                    << " " << setfill('0') << setw(3) << event.destinationWarehouse;
            } else if (event.type == AR) {
                cout << " " << setfill('0') << setw(3) << event.originWarehouse
                    << " " << setfill('0') << setw(3) << event.destinationWarehouse
                    << " " << setfill('0') << setw(3) << event.destinationSection;
            } else if (event.type == RM || event.type == UR || event.type == TR) {
                cout << " " << setfill('0') << setw(3) << event.originWarehouse
                    << " " << setfill('0') << setw(3) << event.destinationWarehouse;
            } else if (event.type == EN) {
                cout << " " << setfill('0') << setw(3) << event.destinationWarehouse;
            }
            
            cout << endl;
        }
    } else if (type == "CL") {
        string clientName;
        iss >> clientName;
        List<pair<Package*, string>> packages = getClientPackages(clientName);

        // Imprime o número de pacotes
        cout << packages.getSize() << endl;
        
        // Imprime cada pacote
        for (const auto& pair : packages) {
            Package* pkg = pair.first;
            Event lastEvent = pkg->getLastEvent();
            
            cout << setfill('0') << setw(7) << lastEvent.timestamp << " EV ";
            
            switch (lastEvent.type) {
                case RG: 
                    cout << "RG ";
                    break;
                case AR: 
                    cout << "AR ";
                    break;
                case RM: 
                    cout << "RM ";
                    break;
                case UR: 
                    cout << "UR ";
                    break;
                case TR: 
                    cout << "TR ";
                    break;
                case EN: 
                    cout << "EN ";
                    break;
            }
            
            cout << setfill('0') << setw(3) << pkg->getId();
            
            if (lastEvent.type == RG) {
                cout << " " << lastEvent.sender << " " << lastEvent.receiver
                    << " " << setfill('0') << setw(3) << lastEvent.originWarehouse
                    << " " << setfill('0') << setw(3) << lastEvent.destinationWarehouse;
            } else if (lastEvent.type == AR) {
                cout << " " << setfill('0') << setw(3) << lastEvent.originWarehouse
                    << " " << setfill('0') << setw(3) << lastEvent.destinationWarehouse
                    << " " << setfill('0') << setw(3) << lastEvent.destinationSection;
            } else if (lastEvent.type == RM || lastEvent.type == UR || lastEvent.type == TR) {
                cout << " " << setfill('0') << setw(3) << lastEvent.originWarehouse
                    << " " << setfill('0') << setw(3) << lastEvent.destinationWarehouse;
            } else if (lastEvent.type == EN) {
                cout << " " << setfill('0') << setw(3) << lastEvent.destinationWarehouse;
            }
            
            cout << endl;
        }
    }
}

List<Event> LogisticsSystem::getPackageHistory(int packageId) const {
    Package* pkg = packages.search(packageId);
    if (pkg) {
        return pkg->getEvents();
    }
    return List<Event>();
}

List<pair<Package*, string>> LogisticsSystem::getClientPackages(const string& clientName) const {
    List<pair<Package*, string>> result;
    Client* client = clients.search(clientName);
    
    if (client) {
        // Pacotes onde o cliente é remetente
        for (int pkgId : client->getSenderPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg && pkg->getEvents().getSize() > 0) { 
                result.push_back(make_pair(pkg, "sender"));
            }
        }
        
        // Pacotes onde o cliente é destinatário
        for (int pkgId : client->getReceiverPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg && pkg->getEvents().getSize() > 0) { 
                result.push_back(make_pair(pkg, "receiver"));
            }
        }
    }
    
    return result;
}
