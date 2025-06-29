#include "../include/list.hpp"
#include "event.hpp"
#include "package.hpp"

// template <typename T>
// List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

// template <typename T>
// List<T>::~List() {
//     Node* current = head;
//     while (current) {
//         Node* next = current->next;
//         delete current;
//         current = next;
//     }
// }

// template <typename T>
// void List<T>::push_back(const T& data) {
//     Node* newNode = new Node(data);
//     if (!head) {
//         head = tail = newNode;
//     } else {
//         tail->next = newNode;
//         tail = newNode;
//     }
//     size++;
// }

// template <typename T>
// int List<T>::getSize() const {
//     return size;
// }

// Instanciações explícitas para os tipos que serão usados
template class List<Event>;
template class List<int>;
template class List<std::pair<Package*, std::string>>;