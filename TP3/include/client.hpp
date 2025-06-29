#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "list.hpp"
#include <string>

class Client {
private:
    std::string name;
    List<int> senderPackages;
    List<int> receiverPackages;

public:
    Client(const std::string& name);
    
    void addSenderPackage(int packageId);
    void addReceiverPackage(int packageId);
    
    const std::string& getName() const;
    const List<int>& getSenderPackages() const;
    const List<int>& getReceiverPackages() const;
};

#endif // CLIENT_HPP