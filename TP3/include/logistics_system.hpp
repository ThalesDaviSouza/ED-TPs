#ifndef LOGISTICS_SYSTEM_HPP
#define LOGISTICS_SYSTEM_HPP

#include "avl_tree.hpp"
#include "event.hpp"
#include "package.hpp"
#include "client.hpp"
#include "list.hpp"
#include <string>
#include <utility> // para std::pair

using namespace std;

class LogisticsSystem {
private:
    AVLTree<Package*, int> packages;  // Chave: int (packageId), Valor: Package*
    AVLTree<Client*, string> clients;  // Chave: string (client name), Valor: Client*
    
    Package* getOrCreatePackage(int packageId);
    Client* getOrCreateClient(const string& name);
    
public:
    LogisticsSystem();
    ~LogisticsSystem();
    
    void processEvent(const Event& event);
    void processQuery(const string& line);
    
    List<Event> getPackageHistory(int packageId) const;
    List<pair<Package*, string>> getClientPackages(const string& clientName) const;
};

#endif // LOGISTICS_SYSTEM_HPP