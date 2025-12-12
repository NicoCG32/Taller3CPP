#pragma once

#include "auxiliar/Nodo.h"

// Pila genérica sin STL. Declaración de interfaz (sin implementación).
template <typename T>
class Stack {
private:
    int topIndex;
    Nodo<T>** data; // almacena punteros a Nodo<T>
public:
    Stack();
    ~Stack();

    bool empty() const;

    void push(Nodo<T>* value);
    Nodo<T>* pop();
    Nodo<T>* top() const;
};
