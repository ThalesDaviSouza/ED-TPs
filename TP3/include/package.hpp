#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "event.hpp"
#include "list.hpp"
#include <iostream>

class Package {
private:
    int id;
    List<Event> events;

public:
    Package(int id);
    
    void addEvent(const Event& event);
    const List<Event>& getEvents() const;
    Event getLastEvent() const;
    int getId() const;
    
    std::string getCurrentStatus() const;
};

#endif // PACKAGE_HPP