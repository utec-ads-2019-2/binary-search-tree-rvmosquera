#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

using namespace std;
template<typename T>
class BSTree {
    Node<T> *root;
private:
    bool find(T data, Node<T> *node)
    {
        if (!node)
            return false;

        else if (data == node->data)
            return true;
        else if(data < node->data)
            return this->find(data, node->left);
        else
            return this->find(data, node->right);
    }

    bool insert(T data, Node<T> *&node)
    {
        if (!node) {
            node = new Node<T>{data};
            return true;
        } else if (data <= node->data)
            return this->insert(data, node->left);
        else
            return this->insert(data, node->right);
    }

    Node<T>* maximum(Node<T> *&node) {
        if ( node->right )
            return maximum(node->right);

        return node;
    }

    bool remove(T &data, Node<T> *&current) {
        if ( !current )
            return false;
        else if (data < current->data)
            return this->remove(data, current->left);
        else if (data > current->data)
            return this->remove(data, current->right);

        /* Two children */
        if (current->left && current->right) {
            auto temp = this->maximum(current->left); // Finding Left Rightmost Node
            swap(current->data, temp->data);

            return this->remove(temp->data, current->left);
        }
        /* One child ( also included no child: leaf Node ) */
        auto prevCurrent = current;

        if (current->left)
            current = current->left;
        else
            current = current->right;

        delete prevCurrent;

        return true;
    }

    size_t size(Node<T> *traverseNode) {
        if (!traverseNode)
            return 0;

        return (this->size(traverseNode->left) + 1 + this->size(traverseNode->right) );
    }

    size_t height(Node<T> *current) {
        if (!current) { return 0; }
        int left = height(current->left);
        int right = height(current->right);
        return std::max( left, right ) + 1;
    }

    void traversePreOrder(Node<T> *traverse){
        if (!traverse) return;

        cout << traverse->data << " ";
        traversePreOrder(traverse->left);
        traversePreOrder(traverse->right);
    }

    void privateTraverseInOrder(Node<T>* traverse) {
        if (!traverse) return;
        privateTraverseInOrder(traverse->left);
        cout << traverse->data << " ";
        privateTraverseInOrder(traverse->right);
    }

    void traversePostOrder(Node<T> *traverse) {
        if (!traverse) return;

        traversePostOrder(traverse->left);
        traversePostOrder(traverse->right);
        cout << traverse->data << " ";
    }

public:
    BSTree() : root(nullptr) {};

    bool find(T data) {
        return this->find(data, this->root);
    }

    bool insert(T data) {
        return this->insert(data, this->root);
    }

    bool remove(T data) {
        return this->remove(data, this->root);
    }


    size_t size() {
        return this->size(this->root);
    }

    size_t height() {
        return height(this->root);
    }

    void traversePreOrder() {
        this->traversePreOrder(this->root);
    }

    void traverseInOrder() {
        this->traverseInOrder(this->root);
    }

    void traverseInOrder(Node<T> *node) {
        if (node) {
            this->sortInOrder(node->left);
            cout << node->data << " ";
            this->sortInOrder(node->right);
        }
    }

    void traversePostOrder() {
        this->traversePostOrder(this->root);
    }

    Iterator<T> begin() {
        if (!this->root)
            return Iterator<T>();

        return Iterator<T>(this->root);
    }

    Iterator<T> end() {
        return Iterator<T>();
    }

    ~BSTree() {
        if (!this->root)
            return;
        else
            this->root->killSelf();
    }
};

#endif
