#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "list.hpp"
#include <string>

using namespace std;

class Client {
private:
    string name;
    List<int> senderPackages;
    List<int> receiverPackages;

public:
    Client(const string& name);
    
    void addSenderPackage(int packageId);
    void addReceiverPackage(int packageId);
    
    const string& getName() const;
    const List<int>& getSenderPackages() const;
    const List<int>& getReceiverPackages() const;
};

#endif // CLIENT_HPP