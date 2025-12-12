#pragma once

#include "auxiliar/Nodo.h"

// Cola para recorrido BFS.
template <typename T>
class Queue {
private:
    Nodo<T>* head;
    //Con tail para facilitar inserciones al final
    Nodo<T>* tail;

public:
    Queue() : head(0), tail(0) {}
    ~Queue() {
        while (!empty()) {
            Nodo<T>* n = pop();
            delete n;
        }
    }

    bool empty() const { 
        return head == 0;
    }

    void push(Nodo<T>* value) {
        if (!value) return;
        value->siguiente = 0;
        if (tail) {
            tail->siguiente = value;
            tail = value;
        } else {
            head = tail = value;
        }
    }

    Nodo<T>* pop() {
        if (empty()) return 0;
        Nodo<T>* n = head;
        head = head->siguiente;
        if (!head) tail = 0;
        n->siguiente = 0;
        return n;
    }

    Nodo<T>* front() const { return head; }
};
