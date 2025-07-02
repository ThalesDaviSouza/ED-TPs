#include "avl_tree.hpp"
#include "package.hpp"
#include "client.hpp"

using namespace std;

int max(int n1, int n2){
    if(n1 >= n2){
        return n1;
    }
    else{
        return n2;
    }
}

// Construtor
template <typename T, typename K>
AVLTree<T, K>::AVLTree(K (*keyFunc)(T)) : 
    root(nullptr), keyFunc(keyFunc), count(0) {}  // Inicializa count

// Destrutor
template <typename T, typename K>
AVLTree<T, K>::~AVLTree() {
    clear(root);
}

// Limpeza da árvore
template <typename T, typename K>
void AVLTree<T, K>::clear(AVLNode<T>* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Altura de um nó
template <typename T, typename K>
int AVLTree<T, K>::height(AVLNode<T>* node) const {
    return node ? node->height : 0;
}

// Fator de balanceamento
template <typename T, typename K>
int AVLTree<T, K>::balanceFactor(AVLNode<T>* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

// Atualiza altura de um nó
template <typename T, typename K>
void AVLTree<T, K>::updateHeight(AVLNode<T>* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

// Rotação à direita
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::rightRotate(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação à esquerda
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::leftRotate(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balanceamento
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::balance(AVLNode<T>* node) {
    updateHeight(node);
    int balance = balanceFactor(node);

    // Caso esquerda-esquerda
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    // Caso esquerda-direita
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso direita-direita
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    // Caso direita-esquerda
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Inserção
template <typename T, typename K>
void AVLTree<T, K>::insert(T data) {
    root = insert(root, data);
    count++;
}

template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::insert(AVLNode<T>* node, T data) {
    if (!node) return new AVLNode<T>(data);

    K currentKey = keyFunc(node->data);
    K newKey = keyFunc(data);

    if (newKey < currentKey)
        node->left = insert(node->left, data);
    else if (newKey > currentKey)
        node->right = insert(node->right, data);
    else
        return node; // Chaves iguais não são permitidas

    return balance(node);
}

// Busca
template <typename T, typename K>
T AVLTree<T, K>::search(K key) const {
    AVLNode<T>* node = search(root, key);
    return node ? node->data : T();
}

template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::search(AVLNode<T>* node, K key) const {
    if (!node) return nullptr;

    K currentKey = keyFunc(node->data);

    if (key == currentKey)
        return node;
    else if (key < currentKey)
        return search(node->left, key);
    else
        return search(node->right, key);
}

// Remoção
template <typename T, typename K>
void AVLTree<T, K>::remove(K key) {
    root = remove(root, key);
    count--;
}

template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::remove(AVLNode<T>* node, K key) {
    if (!node) return nullptr;

    K currentKey = keyFunc(node->data);

    if (key < currentKey)
        node->left = remove(node->left, key);
    else if (key > currentKey)
        node->right = remove(node->right, key);
    else {
        if (!node->left || !node->right) {
            AVLNode<T>* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, keyFunc(temp->data));
        }
    }

    if (!node) return nullptr;

    return balance(node);
}

// Nó com menor valor
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::minValueNode(AVLNode<T>* node) const {
    AVLNode<T>* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Percorrimento em ordem
template <typename T, typename K>
void AVLTree<T, K>::inOrder(void (*visit)(T)) const {
    inOrder(root, visit);
}

template <typename T, typename K>
void AVLTree<T, K>::inOrder(AVLNode<T>* node, void (*visit)(T)) const {
    if (node) {
        inOrder(node->left, visit);
        visit(node->data);
        inOrder(node->right, visit);
    }
}

template <typename T, typename K>
void AVLTree<T, K>::inOrderWithCallback(void (*visit)(T, void*), void* context) const {
    inOrderWithCallback(root, visit, context);
}

template <typename T, typename K>
void AVLTree<T, K>::inOrderWithCallback(AVLNode<T>* node, void (*visit)(T, void*), void* context) const {
    if (node) {
        inOrderWithCallback(node->left, visit, context);
        visit(node->data, context);
        inOrderWithCallback(node->right, visit, context);
    }
}

// Instanciações explícitas
template class AVLTree<Package*, int>;
template class AVLTree<Client*, string>;
template class AVLTree<Event*, int>;