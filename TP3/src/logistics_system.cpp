#include "logistics_system.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

// Funções auxiliares para extração de chaves
int packageKeyFunc(Package* p) { 
    return p->getId(); // Usa o ID do pacote como chave na AVL
}

string clientKeyFunc(Client* c) { 
    return c->getName(); // Usa o nome do cliente como chave na AVL
}

int eventKeyFunc(Event* e) {
    // Cria uma chave única baseada em timestamp, ID do pacote e tipo do evento
    stringstream ss;
    ss << e->timestamp 
       << setw(3) << setfill('0') << e->packageId 
       << static_cast<int>(e->type);

    // Converte a string formada em inteiro (pode causar exceção se string for muito longa)
    string keyStr = ss.str();
    return stoi(keyStr);
}

// Construtor: inicializa as árvores com suas respectivas funções de chave
LogisticsSystem::LogisticsSystem() : 
    packages(packageKeyFunc), 
    clients(clientKeyFunc),
    events(eventKeyFunc) {}

// Destrutor: libera memória dos eventos armazenados
LogisticsSystem::~LogisticsSystem() { 
    auto clearEvents = [](Event* e) { delete e; };
    events.inOrder(clearEvents); // Libera todos os eventos da AVL
}

// Busca ou cria pacote com ID fornecido
Package* LogisticsSystem::getOrCreatePackage(int packageId) {
    Package* pkg = packages.search(packageId);
    if (!pkg) {
        pkg = new Package(packageId);
        packages.insert(pkg); // Insere novo pacote se não existir
    }
    return pkg;
}

// Busca ou cria cliente com nome fornecido
Client* LogisticsSystem::getOrCreateClient(const string& name) {
    Client* client = clients.search(name);
    if (!client) {
        client = new Client(name);
        clients.insert(client); // Insere novo cliente se não existir
    }
    return client;
}

// Processa evento recebido e atualiza estruturas internas
void LogisticsSystem::processEvent(const Event& event) {
    getOrCreatePackage(event.packageId); // Garante que o pacote existe
    Event* newEvent = new Event(event);
    events.insert(newEvent); // Insere evento na árvore

    // Se for evento de registro (RG), associa remetente e destinatário ao pacote
    if (event.type == RG) {
        Client* sender = getOrCreateClient(event.sender);
        sender->addSenderPackage(event.packageId);
        
        Client* receiver = getOrCreateClient(event.receiver);
        receiver->addReceiverPackage(event.packageId);
    }
}

// Contexto auxiliar para buscar histórico de pacote
struct PackageHistoryContext {
    List<Event>* result;
    int packageId;
};

// Função de callback chamada durante o percurso in-order para coletar eventos de um pacote
void collectPackageEvents(Event* event, void* context) {
    PackageHistoryContext* ctx = static_cast<PackageHistoryContext*>(context);
    
    if (event->packageId == ctx->packageId) {
        ctx->result->push_back(*event); // Adiciona evento à lista de resultado
    }
}

// Retorna lista de eventos de um pacote específico, em ordem de tempo
List<Event> LogisticsSystem::getPackageHistory(int packageId) const {
    List<Event> result;
    PackageHistoryContext context = {&result, packageId};
    events.inOrderWithCallback(collectPackageEvents, &context);
    return result;
}

// Função para impressão formatada de um evento
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

    // Impressão dos campos adicionais conforme o tipo do evento
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
}

// Função auxiliar para deletar eventos
void deleteEvent(Event* e) {
    delete e; 
}

// Processa uma linha de consulta (query)
void LogisticsSystem::processQuery(const string& line) {
    istringstream iss(line);
    int timestamp;
    string type;
    
    iss >> timestamp >> type;

    // Formata timestamp com exatamente 6 dígitos
    string formattedTimestamp = to_string(timestamp);
    while (formattedTimestamp.length() < 6)
        formattedTimestamp = "0" + formattedTimestamp;
    formattedTimestamp = formattedTimestamp.substr(formattedTimestamp.length() - 6);

    cout << formattedTimestamp << " " << type;

    // Consulta de histórico de pacote
    if (type == "PC") {
        int packageId;
        iss >> packageId;
        cout << " " << setfill('0') << setw(3) << packageId << endl;

        List<Event> history = getPackageHistory(packageId);
        cout << history.getSize() << endl; // Número de eventos

        for (const Event& event : history) {
            cout << setfill('0') << setw(7) << event.timestamp << " EV ";

            switch (event.type) {
                case RG: cout << "RG "; break;
                case AR: cout << "AR "; break;
                case RM: cout << "RM "; break;
                case UR: cout << "UR "; break;
                case TR: cout << "TR "; break;
                case EN: cout << "EN "; break;
            }

            cout << setfill('0') << setw(3) << event.packageId;

            // Impressão de dados adicionais dependendo do tipo
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
    } 
    // Consulta de pacotes relacionados a um cliente
    else if (type == "CL") {
        string clientName;
        iss >> clientName;
        cout << " " << clientName << endl;

        List<pair<Package*, string>> packages = getClientPackages(clientName);

        // Cria árvore AVL para eventos relevantes (RG e último AR/EN/UR de cada pacote)
        AVLTree<Event*, int> relevantEvents(eventKeyFunc);

        for (const auto& pair : packages) {
            Package* pkg = pair.first;
            List<Event> packageEvents = getPackageHistory(pkg->getId());

            if (packageEvents.getSize() == 0)
                continue;

            Event* rgEvent = nullptr;
            Event* lastRelevantEvent = nullptr;

            for (const Event& ev : packageEvents) {
                if (ev.type == RG) {
                    if (rgEvent) delete rgEvent;
                    rgEvent = new Event(ev); // Armazena evento RG
                } else {
                    if (lastRelevantEvent) delete lastRelevantEvent;
                    lastRelevantEvent = new Event(ev); // Armazena o último evento relevante
                }
            }

            if (rgEvent) relevantEvents.insert(rgEvent);
            if (lastRelevantEvent) relevantEvents.insert(lastRelevantEvent);
        }

        // Imprime os eventos relevantes em ordem
        cout << relevantEvents.size() << endl;
        relevantEvents.inOrder(printEvent);
        relevantEvents.inOrder(deleteEvent); // Libera memória dos eventos criados dinamicamente
    }
}

// Retorna todos os pacotes com eventos relacionados ao cliente dado
List<pair<Package*, string>> LogisticsSystem::getClientPackages(const string& clientName) const {
    List<pair<Package*, string>> result;
    Client* client = clients.search(clientName);

    if (client) {
        // Verifica pacotes onde é remetente
        for (int pkgId : client->getSenderPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                List<Event> pkgEvents = getPackageHistory(pkgId);
                if (pkgEvents.getSize() > 0)
                    result.push_back(make_pair(pkg, "sender"));
            }
        }

        // Verifica pacotes onde é destinatário
        for (int pkgId : client->getReceiverPackages()) {
            Package* pkg = packages.search(pkgId);
            if (pkg) {
                List<Event> pkgEvents = getPackageHistory(pkgId);
                if (pkgEvents.getSize() > 0)
                    result.push_back(make_pair(pkg, "receiver"));
            }
        }
    }

    return result;
}
