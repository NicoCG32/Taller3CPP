#pragma once

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo() : dato(), siguiente(0) {}
    Nodo(const T& valor) : dato(valor), siguiente(0) {}
};
