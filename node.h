#ifndef NODE_H
#define NODE_H

template <typename T>
class BSTree; 

template <typename T>
class Iterator; 

template <typename T>
class Node {
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    explicit Node(T _data): data{_data}, left{nullptr}, right{nullptr}, parent{nullptr} {}

    template<class>
    friend class BSTree;

    template<class>
    friend class Iterator;

    void killSelf();
};

template <typename T>
void Node<T>::killSelf() {
    if (this->left)
        this->left->killSelf();
    else if (this->right)
        this->right->killSelf();

    delete this;
}

#endif