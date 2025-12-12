#pragma once

#include "auxiliar/Nodo.h"

// Cola genérica sin STL. Declaración de interfaz (sin implementación).
template <typename T>
class Queue {
private:
    int head;
    int tail;
    int count;
    Nodo<T>** data; // almacena punteros a Nodo<T>
public:
    Queue();
    ~Queue();

    bool empty() const;

    void push(Nodo<T>* value);
    Nodo<T>* pop();
    Nodo<T>* front() const;
};
