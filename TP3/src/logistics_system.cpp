#include "../include/logistics_system.hpp"
#include <iomanip>
#include <sstream>

// Funções auxiliares para extração de chaves
int packageKeyFunc(Package* p) { return p->getId(); }
std::string clientKeyFunc(Client* c) { return c->getName(); }

LogisticsSystem::LogisticsSystem() 
    : packages(packageKeyFunc), clients(clientKeyFunc) {}

LogisticsSystem::~LogisticsSystem() {
    // Limpeza de memória para Packages
    auto deletePackage = [](Package* p) { delete p; };
    packages.inOrder(deletePackage);
    
    // Limpeza de memória para Clients
    auto deleteClient = [](Client* c) { delete c; };
    clients.inOrder(deleteClient);
}

Package* LogisticsSystem::getOrCreatePackage(int packageId) {
    Package* pkg = packages.search(packageId);
    if (!pkg) {
        pkg = new Package(packageId);
        packages.insert(pkg);
    }
    return pkg;
}

Client* LogisticsSystem::getOrCreateClient(const std::string& name) {
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

void LogisticsSystem::processQuery(const std::string& line) {
    std::istringstream iss(line);
    int timestamp;
    std::string type;
    
    iss >> timestamp >> type;
    
    // Imprime a linha da consulta
    std::cout << line << std::endl;
    
    if (type == "PC") {
        int packageId;
        iss >> packageId;
        List<Event> history = getPackageHistory(packageId);
        
        // Imprime o número de eventos
        std::cout << history.getSize() << std::endl;
        
        // Imprime cada evento
        for (const Event& event : history) {
            std::cout << std::setfill('0') << std::setw(7) << event.timestamp << " EV ";
            
            switch (event.type) {
                case RG: std::cout << "RG "; break;
                case AR: std::cout << "AR "; break;
                case RM: std::cout << "RM "; break;
                case UR: std::cout << "UR "; break;
                case TR: std::cout << "TR "; break;
                case EN: std::cout << "EN "; break;
            }
            
            std::cout << std::setfill('0') << std::setw(3) << event.packageId;
            
            if (event.type == RG) {
                std::cout << " " << event.sender << " " << event.receiver
                          << " " << std::setfill('0') << std::setw(3) << event.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << event.destinationWarehouse;
            } else if (event.type == AR) {
                std::cout << " " << std::setfill('0') << std::setw(3) << event.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << event.destinationWarehouse
                          << " " << std::setfill('0') << std::setw(3) << event.destinationSection;
            } else if (event.type == RM || event.type == UR || event.type == TR) {
                std::cout << " " << std::setfill('0') << std::setw(3) << event.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << event.destinationWarehouse;
            } else if (event.type == EN) {
                std::cout << " " << std::setfill('0') << std::setw(3) << event.destinationWarehouse;
            }
            
            std::cout << std::endl;
        }
    } else if (type == "CL") {
        std::string clientName;
        iss >> clientName;
        List<std::pair<Package*, std::string>> packages = getClientPackages(clientName);

        // Imprime o número de pacotes
        std::cout << packages.getSize() << std::endl;
        
        // Imprime cada pacote
        for (const auto& pair : packages) {
            Package* pkg = pair.first;
            // const std::string& role = pair.second;
            Event lastEvent = pkg->getLastEvent();
            
            std::cout << std::setfill('0') << std::setw(7) << lastEvent.timestamp << " EV ";
            
            switch (lastEvent.type) {
                case RG: std::cout << "RG "; break;
                case AR: std::cout << "AR "; break;
                case RM: std::cout << "RM "; break;
                case UR: std::cout << "UR "; break;
                case TR: std::cout << "TR "; break;
                case EN: std::cout << "EN "; break;
            }
            
            std::cout << std::setfill('0') << std::setw(3) << pkg->getId();
            
            if (lastEvent.type == RG) {
                std::cout << " " << lastEvent.sender << " " << lastEvent.receiver
                          << " " << std::setfill('0') << std::setw(3) << lastEvent.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << lastEvent.destinationWarehouse;
            } else if (lastEvent.type == AR) {
                std::cout << " " << std::setfill('0') << std::setw(3) << lastEvent.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << lastEvent.destinationWarehouse
                          << " " << std::setfill('0') << std::setw(3) << lastEvent.destinationSection;
            } else if (lastEvent.type == RM || lastEvent.type == UR || lastEvent.type == TR) {
                std::cout << " " << std::setfill('0') << std::setw(3) << lastEvent.originWarehouse
                          << " " << std::setfill('0') << std::setw(3) << lastEvent.destinationWarehouse;
            } else if (lastEvent.type == EN) {
                std::cout << " " << std::setfill('0') << std::setw(3) << lastEvent.destinationWarehouse;
            }
            
            std::cout << std::endl;
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

List<std::pair<Package*, std::string>> LogisticsSystem::getClientPackages(const std::string& clientName) const {
    List<std::pair<Package*, std::string>> result;
    Client* client = clients.search(clientName);
    
    if (client) {
        // Pacotes onde o cliente é remetente
        for (int pkgId : client->getSenderPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                result.push_back(std::make_pair(pkg, "sender"));
            }
        }
        
        // Pacotes onde o cliente é destinatário
        for (int pkgId : client->getReceiverPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                result.push_back(std::make_pair(pkg, "receiver"));
            }
        }
    }
    
    return result;
}
