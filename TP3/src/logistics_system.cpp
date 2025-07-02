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

int eventKeyFunc(Event* e) {
    // Cria uma string única combinando timestamp, packageId e tipo de evento
    stringstream ss;
    ss << e->timestamp 
       << setw(3) << setfill('0') << e->packageId 
       << static_cast<int>(e->type);
    
    // Converte a string para um número inteiro (pode ser um hash se a string for muito longa)
    string keyStr = ss.str();
    return stoi(keyStr);
}
LogisticsSystem::LogisticsSystem() : 
    packages(packageKeyFunc), 
    clients(clientKeyFunc),
    events(eventKeyFunc) {}

LogisticsSystem::~LogisticsSystem() { 
    // Limpar eventos
    auto clearEvents = [](Event* e) { delete e; };
    events.inOrder(clearEvents);
}

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
    getOrCreatePackage(event.packageId);
    // Armazenar o evento na AVL tree
    Event* newEvent = new Event(event);
    events.insert(newEvent);

    
    if (event.type == RG) {
        Client* sender = getOrCreateClient(event.sender);
        sender->addSenderPackage(event.packageId);
        
        Client* receiver = getOrCreateClient(event.receiver);
        receiver->addReceiverPackage(event.packageId);
    }
}

// Estrutura auxiliar para passar os parâmetros para a função de callback
struct PackageHistoryContext {
    List<Event>* result;
    int packageId;
};

// Função de callback para coletar eventos de um pacote específico
void collectPackageEvents(Event* event, void* context) {
    PackageHistoryContext* ctx = static_cast<PackageHistoryContext*>(context);
    
    // Verifica se é um evento do pacote
    if (event->packageId == ctx->packageId) {
        ctx->result->push_back(*event);
    }
}

List<Event> LogisticsSystem::getPackageHistory(int packageId) const {
    List<Event> result;
    PackageHistoryContext context = {&result, packageId};
    
    events.inOrderWithCallback(collectPackageEvents, &context);
    
    return result;
}


// Função para imprimir os eventos em ordem
void printEvent(Event* e) {
    cout << setfill('0') << setw(7) << e->timestamp << " EV ";
    
    switch (e->type) {
        case RG: cout << "RG "; break;
        case AR: cout << "AR "; break;
        case RM: cout << "RM "; break;
        case UR: cout << "UR "; break;
        case TR: cout << "TR "; break;
        case EN: cout << "EN "; break;
    }
    
    cout << setfill('0') << setw(3) << e->packageId;
    
    if (e->type == RG) {
        cout << " " << e->sender << " " << e->receiver
            << " " << setfill('0') << setw(3) << e->originWarehouse
            << " " << setfill('0') << setw(3) << e->destinationWarehouse;
    } else if (e->type == AR) {
        cout << " " << setfill('0') << setw(3) << e->originWarehouse
            << " " << setfill('0') << setw(3) << e->destinationWarehouse;
    } else if (e->type == RM || e->type == UR || e->type == TR) {
        cout << " " << setfill('0') << setw(3) << e->originWarehouse
            << " " << setfill('0') << setw(3) << e->destinationWarehouse;
    } else if (e->type == EN) {
        cout << " " << setfill('0') << setw(3) << e->destinationWarehouse;
    }
    
    cout << endl;
};

// Limpeza dos eventos alocados
void deleteEvent(Event* e) {
    delete e; 
}

void LogisticsSystem::processQuery(const string& line) {
    istringstream iss(line);
    int timestamp;
    string type;
    
    iss >> timestamp >> type;
    
    // Formata o timestamp com exatamente 6 dígitos
    string formattedTimestamp = to_string(timestamp);
    while (formattedTimestamp.length() < 6) {
        formattedTimestamp = "0" + formattedTimestamp;
    }
    formattedTimestamp = formattedTimestamp.substr(formattedTimestamp.length() - 6);
    
    // Imprime a linha formatada
    cout << formattedTimestamp << " " << type;

    if (type == "PC") {
        int packageId;
        iss >> packageId;
        cout << " " << setfill('0') << setw(3) << packageId << endl;

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
                    << " " << setfill('0') << setw(3) << event.destinationWarehouse;
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
        cout << " " << clientName << endl;

        List<pair<Package*, string>> packages = getClientPackages(clientName);

        // AVL tree para armazenar e ordenar automaticamente os eventos relevantes
        AVLTree<Event*, int> relevantEvents(eventKeyFunc);

        for (const auto& pair : packages) {
            Package* pkg = pair.first;
            List<Event> packageEvents = getPackageHistory(pkg->getId());
            

            if (packageEvents.getSize() == 0) {
                continue;
            }

            Event* rgEvent = nullptr;       // Evento de RG (Registro)
            Event* lastRelevantEvent = nullptr; // Último evento AR, EN ou UR

            for (const Event& ev : packageEvents) {
                // Captura o evento RG
                if (ev.type == RG) {
                    if (rgEvent) delete rgEvent; // Libera o anterior se existir
                    rgEvent = new Event(ev);
                }
                else {
                    if (lastRelevantEvent) delete lastRelevantEvent; // Libera o anterior
                    lastRelevantEvent = new Event(ev);
                }
            }

            // Adiciona o evento RG à árvore
            if (rgEvent) {
                relevantEvents.insert(rgEvent);
            }
            // Adiciona o último evento relevante (AR, EN ou UR) à árvore
            if (lastRelevantEvent) {
                relevantEvents.insert(lastRelevantEvent);
            }
        }

        // Imprime o número de eventos relevantes (RG + último AR/EN/UR de cada pacote)
        cout << relevantEvents.size() << endl;

        // Percorre a árvore em ordem (ordenada por timestamp) e imprime os eventos
        relevantEvents.inOrder(printEvent);

        // Limpa a memória alocada para os eventos
        relevantEvents.inOrder(deleteEvent);
    }
}


List<pair<Package*, string>> LogisticsSystem::getClientPackages(const string& clientName) const {
    List<pair<Package*, string>> result;
    Client* client = clients.search(clientName);
    
    if (client) {
        // Pacotes onde o cliente é remetente
        for (int pkgId : client->getSenderPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                // Verifica se existem eventos para este pacote
                List<Event> pkgEvents = getPackageHistory(pkgId);
                if (pkgEvents.getSize() > 0) {
                    result.push_back(make_pair(pkg, "sender"));
                }
            }
        }
        
        // Pacotes onde o cliente é destinatário
        for (int pkgId : client->getReceiverPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                // Verifica se existem eventos para este pacote
                List<Event> pkgEvents = getPackageHistory(pkgId);
                if (pkgEvents.getSize() > 0) {
                    result.push_back(make_pair(pkg, "receiver"));
                }
            }
        }
    }
    
    return result;
}
