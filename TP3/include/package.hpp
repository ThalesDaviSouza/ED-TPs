#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "event.hpp"
#include <iostream>

class Package {
private:
    int id;

public:
    Package(int id);
    
    int getId() const;
    std::string getCurrentStatus(const Event& lastEvent) const;
};

#endif // PACKAGE_HPP