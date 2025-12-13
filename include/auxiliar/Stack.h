#pragma once

#include "auxiliar/Nodo.h"

/**
 * Pila enlazada utilizada para recorridos DFS.
 * @pre Ninguna.
 * @post Gestiona nodos enlazados de forma LIFO.
 * @tparam T Tipo de dato almacenado en cada nodo.
 * @author Pablo Guzmán
 */
template <typename T>
class Stack {
private:
    Nodo<T>* head;

public:
    /**
     * Crea una pila vacía.
     * @pre Ninguna.
     * @post La pila queda inicializada sin elementos.
     * @throws No lanza.
     */
    Stack() : head(0) {}

    /**
     * Libera todos los nodos de la pila.
     * @pre Ninguna.
     * @post La pila queda vacía y su memoria liberada.
     * @throws No lanza.
     */
    ~Stack() {
        while (!empty()) {
            Nodo<T>* n = pop();
            delete n;
        }
    }

    /**
     * Indica si la pila está vacía.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return true si no hay elementos.
     * @throws No lanza.
     */
    bool empty() const { return head == 0; }

    /**
     * Inserta un nodo en la cima.
     * @pre value distinto de nulo.
     * @post El nodo se convierte en la nueva cabeza.
     * @param value Nodo a apilar.
     * @throws No lanza.
     */
    void push(Nodo<T>* value) {
        if (!value) return;
        value->siguiente = head;
        head = value;
    }

    /**
     * Extrae el nodo en la cima.
     * @pre Ninguna.
     * @post El nodo extraído queda desvinculado.
     * @return Nodo removido o 0 si estaba vacía.
     * @throws No lanza.
     */
    Nodo<T>* pop() {
        if (empty()) return 0;
        Nodo<T>* n = head;
        head = head->siguiente;
        n->siguiente = 0;
        return n;
    }
    
    /**
     * Consulta el nodo en la cima sin extraerlo.
     * @pre Ninguna.
     * @post No modifica la pila.
     * @return Nodo en cabeza o 0 si está vacía.
     * @throws No lanza.
     */
    Nodo<T>* top() const { return head; }
};
