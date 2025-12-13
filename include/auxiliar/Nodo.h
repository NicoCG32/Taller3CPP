#pragma once

/**
 * Nodo simple usado en estructuras enlazadas.
 * @pre Ninguna.
 * @post Se instancia un contenedor con puntero al siguiente.
 * @tparam T Tipo del dato almacenado.
 * @author Pablo Guzmán
 */
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;

    /**
     * Construye un nodo vacío.
     * @pre Ninguna.
     * @post El nodo apunta a nulo y dato se inicializa por defecto.
     * @throws No lanza.
     */
    Nodo() : dato(), siguiente(0) {}

    /**
     * Construye un nodo con dato inicial.
     * @pre Ninguna.
     * @post El nodo almacena el valor y apunta a nulo.
     * @param valor Dato a almacenar.
     * @throws No lanza.
     */
    Nodo(const T& valor) : dato(valor), siguiente(0) {}
};
