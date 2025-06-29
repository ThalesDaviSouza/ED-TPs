#ifndef LOGISTICS_SYSTEM_HPP
#define LOGISTICS_SYSTEM_HPP

#include "avl_tree.hpp"
#include "event.hpp"
#include "package.hpp"
#include "client.hpp"
#include "list.hpp"
#include <string>
#include <utility> // para std::pair

class LogisticsSystem {
private:
    AVLTree<Package*, int> packages;  // Chave: int (packageId), Valor: Package*
    AVLTree<Client*, std::string> clients;  // Chave: std::string (client name), Valor: Client*
    
    Package* getOrCreatePackage(int packageId);
    Client* getOrCreateClient(const std::string& name);
    
public:
    LogisticsSystem();
    ~LogisticsSystem();
    
    void processEvent(const Event& event);
    void processQuery(const std::string& line);
    
    List<Event> getPackageHistory(int packageId) const;
    List<std::pair<Package*, std::string>> getClientPackages(const std::string& clientName) const;
};

#endif // LOGISTICS_SYSTEM_HPP