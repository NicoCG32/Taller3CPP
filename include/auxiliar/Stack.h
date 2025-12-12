#pragma once

#include "auxiliar/Nodo.h"

// Pila para recorrido DFS.
template <typename T>
class Stack {
private:
    Nodo<T>* head;

public:
    Stack() : head(0) {}
    ~Stack() {
        while (!empty()) {
            Nodo<T>* n = pop();
            delete n;
        }
    }

    bool empty() const { return head == 0; }

    void push(Nodo<T>* value) {
        if (!value) return;
        value->siguiente = head;
        head = value;
    }
    Nodo<T>* pop() {
        if (empty()) return 0;
        Nodo<T>* n = head;
        head = head->siguiente;
        n->siguiente = 0;
        return n;
    }
    
    Nodo<T>* top() const { return head; }
};
