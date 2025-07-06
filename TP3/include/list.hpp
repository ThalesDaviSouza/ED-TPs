#ifndef LIST_HPP
#define LIST_HPP

#include <stdexcept>
#include <iostream>

using namespace std;

// Lista encadeada simples genérica
template <typename T>
class List {
private:
    // Estrutura de nó da lista
    struct Node {
        T data;        // Valor armazenado
        Node* next;    // Ponteiro para o próximo nó
        Node(const T& data) : data(data), next(nullptr) {}
    };
    
    Node* head;  // Início da lista
    Node* tail;  // Fim da lista
    int size;    // Quantidade de elementos

    // Função auxiliar para liberar todos os nós da lista
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
    // Construtor padrão
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Destrutor
    ~List() {
        clear(); // Libera memória dos nós
    }

    // Construtor de cópia
    List(const List& other) {
        head = tail = nullptr;
        size = 0;
        for (Node* current = other.head; current != nullptr; current = current->next) {
            push_back(current->data);
        }
    }

    // Operador de atribuição por cópia
    List& operator=(const List& other) {
        if (this != &other) {
            clear(); // Limpa a lista atual
            for (Node* current = other.head; current != nullptr; current = current->next) {
                push_back(current->data);
            }
        }
        return *this;
    }

    // Adiciona elemento ao final da lista
    void push_back(const T& data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode; // Primeiro elemento
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Retorna a quantidade de elementos da lista
    int getSize() const {
        return size;
    }

    // Verifica se a lista está vazia
    bool empty() const {
        return size == 0;
    }

    // Retorna o último nó da lista
    Node* getLastNode() const {
        if (!tail) {
            throw runtime_error("Tentativa de acessar último nó de lista vazia");
        }
        return tail;
    }

    // Retorna o primeiro nó da lista
    Node* getFirstNode() const {
        if (!head) {
            throw runtime_error("Tentativa de acessar primeiro nó de lista vazia");
        }
        return head;
    }

    // Classe interna de iterador para percorrer a lista
    class Iterator {
    public:
        Iterator(Node* node) : current(node) {}
        
        // Verifica se o iterador ainda é válido
        bool isValid() const {
            return current != nullptr;
        }

        // Acesso ao conteúdo do nó atual
        T& operator*() {
            if (!current) {
                throw runtime_error("Tentativa de dereferenciar iterador inválido");
            }
            return current->data;
        }

        // Avança o iterador (pré-incremento)
        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        // Verifica desigualdade entre iteradores
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // Acesso ao nó (útil para depuração)
        Node* node() const {
            return current;
        }

    private:
        Node* current;
    };

    // Retorna iterador para o início da lista
    Iterator begin() const {
        return Iterator(head);
    }

    // Retorna iterador para o fim da lista (nullptr)
    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // LIST_HPP
