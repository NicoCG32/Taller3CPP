#pragma once

#include "auxiliar/Nodo.h"

/**
 * Cola enlazada utilizada para recorridos BFS.
 * @pre Ninguna.
 * @post Gestiona nodos enlazados en orden FIFO.
 * @tparam T Tipo de dato almacenado en cada nodo.
 * @author Pablo Guzmán
 */
template <typename T>
class Queue {
private:
    Nodo<T>* head;
    Nodo<T>* tail; // Puntero al último nodo para inserción O(1)

public:
    /**
     * Crea una cola vacía.
     * @pre Ninguna.
     * @post La cola queda sin elementos.
     * @throws No lanza.
     */
    Queue() : head(0), tail(0) {}

    /**
     * Libera todos los nodos de la cola.
     * @pre Ninguna.
     * @post La cola queda vacía y se libera memoria.
     * @throws No lanza.
     */
    ~Queue() {
        while (!empty()) {
            Nodo<T>* n = pop();
            delete n;
        }
    }

    /**
     * Indica si la cola está vacía.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return true si no hay elementos.
     * @throws No lanza.
     */
    bool empty() const { 
        return head == 0;
    }

    /**
     * Inserta un nodo al final de la cola.
     * @pre value distinto de nulo.
     * @post El nodo se coloca como nuevo tail.
     * @param value Nodo a encolar.
     * @throws No lanza.
     */
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

    /**
     * Extrae el nodo al frente de la cola.
     * @pre Ninguna.
     * @post El nodo extraído queda desvinculado.
     * @return Nodo removido o 0 si estaba vacía.
     * @throws No lanza.
     */
    Nodo<T>* pop() {
        if (empty()) return 0;
        Nodo<T>* n = head;
        head = head->siguiente;
        if (!head) tail = 0;
        n->siguiente = 0;
        return n;
    }

    /**
     * Consulta el nodo al frente sin extraerlo.
     * @pre Ninguna.
     * @post No modifica la cola.
     * @return Nodo en cabeza o 0 si está vacía.
     * @throws No lanza.
     */
    Nodo<T>* front() const { return head; }
};
