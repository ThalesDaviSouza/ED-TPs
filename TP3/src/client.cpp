#include "client.hpp"

using namespace std;

Client::Client(const string& name) : name(name) {}

void Client::addSenderPackage(int packageId) {
    senderPackages.push_back(packageId);
}

void Client::addReceiverPackage(int packageId) {
    receiverPackages.push_back(packageId);
}

const string& Client::getName() const {
    return name;
}

const List<int>& Client::getSenderPackages() const {
    return senderPackages;
}

const List<int>& Client::getReceiverPackages() const {
    return receiverPackages;
}