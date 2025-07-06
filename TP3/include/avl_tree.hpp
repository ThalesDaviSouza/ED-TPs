#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

// Estrutura de nó da árvore AVL
template <typename T>
struct AVLNode {
    T data;                 // Dado armazenado no nó
    AVLNode* left;          // Ponteiro para o filho esquerdo
    AVLNode* right;         // Ponteiro para o filho direito
    int height;             // Altura do nó na árvore

    AVLNode(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

// Classe de árvore AVL genérica com chave derivada por função
template <typename T, typename K>
class AVLTree {
public:
    // Construtor: recebe uma função que extrai a chave do tipo T
    AVLTree(K (*keyFunc)(T));

    // Destrutor
    ~AVLTree();

    // Insere um novo elemento na árvore
    void insert(T data);

    // Remove um elemento com a chave fornecida
    void remove(K key);

    // Busca um elemento pela chave
    T search(K key) const;

    // Percorre a árvore em ordem, chamando uma função sem contexto
    void inOrder(void (*visit)(T)) const;

    // Percorre a árvore em ordem, chamando uma função com contexto adicional
    void inOrderWithCallback(void (*visit)(T, void*), void* context) const;

    // Retorna o número de elementos na árvore
    int size() const { return count; } 
    
private:
    AVLNode<T>* root;           // Raiz da árvore
    K (*keyFunc)(T);            // Função para extrair a chave de um objeto do tipo T
    int count;                  // Contador de elementos na árvore

    // Métodos auxiliares privados para as operações da árvore

    AVLNode<T>* insert(AVLNode<T>* node, T data);
    AVLNode<T>* remove(AVLNode<T>* node, K key);
    AVLNode<T>* search(AVLNode<T>* node, K key) const;
    void inOrder(AVLNode<T>* node, void (*visit)(T)) const;
    void clear(AVLNode<T>* node); // Libera memória da árvore recursivamente

    int height(AVLNode<T>* node) const; // Retorna a altura de um nó
    int balanceFactor(AVLNode<T>* node) const; // Calcula o fator de balanceamento

    // Rotações para balanceamento
    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* leftRotate(AVLNode<T>* x);

    // Retorna o nó com o menor valor (usado na remoção)
    AVLNode<T>* minValueNode(AVLNode<T>* node) const;

    // Balanceia a árvore após inserção ou remoção
    AVLNode<T>* balance(AVLNode<T>* node);

    // Atualiza a altura de um nó com base em seus filhos
    void updateHeight(AVLNode<T>* node);

    // Versão interna do percurso in-order com função que recebe contexto
    void inOrderWithCallback(AVLNode<T>* node, void (*visit)(T, void*), void* context) const;
};

#endif // AVL_TREE_HPP
