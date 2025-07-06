#ifndef LOGISTICS_SYSTEM_HPP
#define LOGISTICS_SYSTEM_HPP

#include "avl_tree.hpp"
#include "event.hpp"
#include "package.hpp"
#include "client.hpp"
#include "list.hpp"
#include <string>
#include <utility>

using namespace std;

// Classe principal que gerencia o sistema logístico
class LogisticsSystem {
private:
    // Estruturas AVL para armazenar os dados organizados e com busca eficiente
    AVLTree<Package*, int> packages;      // Pacotes indexados por ID
    AVLTree<Client*, string> clients;     // Clientes indexados por nome
    AVLTree<Event*, int> events;          // Eventos indexados por chave baseada no timestamp

    // Cria ou retorna um pacote já existente com o ID fornecido
    Package* getOrCreatePackage(int packageId);

    // Cria ou retorna um cliente já existente com o nome fornecido
    Client* getOrCreateClient(const string& name);
    
public:
    // Construtor
    LogisticsSystem();

    // Destrutor (libera memória dos eventos)
    ~LogisticsSystem();
    
    // Processa e armazena um novo evento no sistema
    void processEvent(const Event& event);

    // Processa uma linha de consulta do tipo PC ou CL
    void processQuery(const string& line);
    
    // Retorna todos os eventos associados a um pacote
    List<Event> getPackageHistory(int packageId) const;

    // Retorna todos os pacotes associados a um cliente (como remetente ou destinatário)
    List<pair<Package*, string>> getClientPackages(const string& clientName) const;
};

#endif // LOGISTICS_SYSTEM_HPP
