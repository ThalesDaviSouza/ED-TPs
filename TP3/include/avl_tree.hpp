#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

template <typename T, typename K>
class AVLTree {
public:
    AVLTree(K (*keyFunc)(T));
    ~AVLTree();

    void insert(T data);
    void remove(K key);
    T search(K key) const;
    void inOrder(void (*visit)(T)) const;

private:
    AVLNode<T>* root;
    K (*keyFunc)(T);

    AVLNode<T>* insert(AVLNode<T>* node, T data);
    AVLNode<T>* remove(AVLNode<T>* node, K key);
    AVLNode<T>* search(AVLNode<T>* node, K key) const;
    void inOrder(AVLNode<T>* node, void (*visit)(T)) const;
    void clear(AVLNode<T>* node);

    int height(AVLNode<T>* node) const;
    int balanceFactor(AVLNode<T>* node) const;
    AVLNode<T>* rightRotate(AVLNode<T>* y);
    AVLNode<T>* leftRotate(AVLNode<T>* x);
    AVLNode<T>* minValueNode(AVLNode<T>* node) const;
    AVLNode<T>* balance(AVLNode<T>* node);

    void updateHeight(AVLNode<T>* node);
};

#endif // AVL_TREE_HPP