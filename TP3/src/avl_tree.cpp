#include "avl_tree.hpp"
#include "package.hpp"
#include "client.hpp"

using namespace std;

// Função utilitária para obter o máximo entre dois inteiros
int max(int n1, int n2) {
    return (n1 >= n2) ? n1 : n2;
}

/* Construtor - Inicializa árvore vazia com função de extração de chave */
template <typename T, typename K>
AVLTree<T, K>::AVLTree(K (*keyFunc)(T)) : 
    root(nullptr), keyFunc(keyFunc), count(0) {}

/* Destrutor - Remove todos os nós recursivamente */
template <typename T, typename K>
AVLTree<T, K>::~AVLTree() {
    clear(root);
}

/* Limpa a árvore em pós-ordem */
template <typename T, typename K>
void AVLTree<T, K>::clear(AVLNode<T>* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

/* Retorna altura do nó (0 para nullptr) */
template <typename T, typename K>
int AVLTree<T, K>::height(AVLNode<T>* node) const {
    return node ? node->height : 0;
}

/* Calcula fator de balanceamento (altura esquerda - altura direita) */
template <typename T, typename K>
int AVLTree<T, K>::balanceFactor(AVLNode<T>* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

/* Atualiza altura do nó baseado nos filhos */
template <typename T, typename K>
void AVLTree<T, K>::updateHeight(AVLNode<T>* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}

/* Rotação à direita para caso de desbalanceamento esquerda-esquerda */
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

/* Rotação à esquerda para caso de desbalanceamento direita-direita */
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

/* Balanceia o nó e retorna nova raiz da subárvore */
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::balance(AVLNode<T>* node) {
    updateHeight(node);
    int balance = balanceFactor(node);

    // Casos pesados à esquerda
    if (balance > 1) {
        if (balanceFactor(node->left) >= 0)  // Caso esquerda-esquerda
            return rightRotate(node);
        else {                              // Caso esquerda-direita
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    
    // Casos pesados à direita
    if (balance < -1) {
        if (balanceFactor(node->right) <= 0) // Caso direita-direita
            return leftRotate(node);
        else {                              // Caso direita-esquerda
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

/* Inserção pública - incrementa contador */
template <typename T, typename K>
void AVLTree<T, K>::insert(T data) {
    root = insert(root, data);
    count++;
}

/* Inserção recursiva com balanceamento automático */
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
        return node; // Chaves duplicadas não são permitidas

    return balance(node);
}

/* Busca pública - retorna dado ou T padrão */
template <typename T, typename K>
T AVLTree<T, K>::search(K key) const {
    AVLNode<T>* node = search(root, key);
    return node ? node->data : T();
}

/* Busca recursiva por chave */
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

/* Remoção pública - decrementa contador */
template <typename T, typename K>
void AVLTree<T, K>::remove(K key) {
    root = remove(root, key);
    count--;
}

/* Remoção recursiva com balanceamento */
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::remove(AVLNode<T>* node, K key) {
    if (!node) return nullptr;

    K currentKey = keyFunc(node->data);

    if (key < currentKey)
        node->left = remove(node->left, key);
    else if (key > currentKey)
        node->right = remove(node->right, key);
    else {
        // Nó encontrado - trata casos de remoção
        if (!node->left || !node->right) {
            // Caso com um filho
            AVLNode<T>* temp = node->left ? node->left : node->right;
            if (!temp) {
                // Sem filhos
                temp = node;
                node = nullptr;
            } else {
                // Um filho - copia conteúdo
                *node = *temp;
            }
            delete temp;
        } else {
            // Dois filhos - encontra sucessor in-order
            AVLNode<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, keyFunc(temp->data));
        }
    }

    if (!node) return nullptr;

    return balance(node);
}

/* Encontra nó mais à esquerda (valor mínimo) da subárvore */
template <typename T, typename K>
AVLNode<T>* AVLTree<T, K>::minValueNode(AVLNode<T>* node) const {
    while (node && node->left) node = node->left;
    return node;
}

/* Travessia in-order pública com callback simples */
template <typename T, typename K>
void AVLTree<T, K>::inOrder(void (*visit)(T)) const {
    inOrder(root, visit);
}

/* Travessia in-order recursiva */
template <typename T, typename K>
void AVLTree<T, K>::inOrder(AVLNode<T>* node, void (*visit)(T)) const {
    if (node) {
        inOrder(node->left, visit);
        visit(node->data);
        inOrder(node->right, visit);
    }
}

/* Travessia in-order pública com parâmetro de contexto */
template <typename T, typename K>
void AVLTree<T, K>::inOrderWithCallback(void (*visit)(T, void*), void* context) const {
    inOrderWithCallback(root, visit, context);
}

/* Travessia in-order recursiva com contexto */
template <typename T, typename K>
void AVLTree<T, K>::inOrderWithCallback(AVLNode<T>* node, void (*visit)(T, void*), void* context) const {
    if (node) {
        inOrderWithCallback(node->left, visit, context);
        visit(node->data, context);
        inOrderWithCallback(node->right, visit, context);
    }
}

// Instanciações explícitas para os tipos necessários
template class AVLTree<Package*, int>;
template class AVLTree<Client*, string>;
template class AVLTree<Event*, int>;