#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>
#include <queue>
#include <deque>
template<typename T>
class Iterator {
private:
    Node<T> *current;
    stack<Node<T> *> descendingStack;
    stack<Node<T> *> ascendingStack;
public:
    Iterator() {
        this->current = nullptr;
    }

    explicit Iterator(Node<T> *node) {
        insertSorted(node);

        while ( !descendingStack.empty() ) {
            ascendingStack.push(descendingStack.top() );
            descendingStack.pop();
        }
        descendingStack.push(ascendingStack.top() );
        ascendingStack.pop();

        this->current = descendingStack.top();
    }

    Iterator<T> &operator=(const Iterator<T> &other) {
        this->current = other->current;
        return (*this);
    }

    bool operator!=(Iterator<T> other) {
        return this->current != other.current;
    }

    Iterator<T> &operator++() {
        if ( ascendingStack.empty() ) {
            this->current = nullptr;
            return (*this);
        }

        descendingStack.push(ascendingStack.top() );
        ascendingStack.pop();
        this->current = descendingStack.top();

        return (*this);
    }

    Iterator<T> &operator--() {
        if(descendingStack.empty())
        {
            this->current = nullptr;
            return (*this);
        }
        ascendingStack.push(descendingStack.top());
        descendingStack.pop();
        this->current = ascendingStack.top();
        return (*this);
    }

    T operator*() {
        if(!this->current)
            throw out_of_range("No nodes in tree");

        return this->current->data;
    }

    void insertSorted(Node<T> *node){
        if (!node)
            return;

        insertSorted(node->left);
        descendingStack.push(node);
        insertSorted(node->right);
    }

};

#endif
