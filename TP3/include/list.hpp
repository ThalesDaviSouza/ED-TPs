#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <iostream>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;

    // Método auxiliar para limpar a lista
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

public:
    // Construtor
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Destrutor
    ~List() {
        clear();
    }

    List(const List& other) {
        // Implementação do construtor de cópia
        head = tail = nullptr;
        size = 0;
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* current = other.head; current != nullptr; current = current->next) {
                push_back(current->data);
            }
        }
        return *this;
    }

    // Adiciona elemento no final
    void push_back(const T& data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Retorna o tamanho da lista
    int getSize() const {
        return size;
    }

    // Verifica se a lista está vazia
    bool empty() const {
        return size == 0;
    }

    // Obtém o último nó (solução alternativa para getLastEvent)
    Node* getLastNode() const {
        if (!tail) {
            throw std::runtime_error("Tentativa de acessar último nó de lista vazia");
        }
        return tail;
    }

    // Obtém o primeiro nó
    Node* getFirstNode() const {
        if (!head) {
            throw std::runtime_error("Tentativa de acessar primeiro nó de lista vazia");
        }
        return head;
    }

    // Iterador seguro
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}
        
        // Verifica se o iterador é válido
        bool isValid() const {
            return current != nullptr;
        }

        // Operador de dereferenciamento seguro
        T& operator*() {
            if (!current) {
                throw std::runtime_error("Tentativa de dereferenciar iterador inválido");
            }
            return current->data;
        }

        // Operador de pré-incremento
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        // Operador de desigualdade
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // Acesso direto ao nó atual (para depuração)
        Node* node() const {
            return current;
        }

    private:
        Node* current;
    };

    // Iteradores
    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    
};

#endif // LIST_HPP