#pragma once

// Nodo genérico para recorridos y estructuras auxiliares.
// Contiene datos de tipo T y puede enlazarse mediante punteros.
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo();
    Nodo(const T& valor);
};
