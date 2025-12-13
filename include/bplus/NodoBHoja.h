#pragma once
#include "bplus/NodoBPlusBase.h"
#include "grafo/NodoGrafo.h"

/**
 * Nodo hoja del árbol B+ que almacena claves y referencias a nodos del grafo.
 * @pre Orden mayor que cero.
 * @post Mantiene datos y enlace al siguiente nodo hoja.
 * @author Pablo Guzmán
 */
class NodoBHoja : public NodoBPlusBase {
private:
    NodoGrafo** datos;
    NodoBHoja* siguiente_hoja;
public:
    /**
     * Construye una hoja B+.
     * @pre _orden > 0.
     * @post Inicializa arreglo de datos y enlace siguiente.
     * @param _orden Capacidad de claves del nodo.
     * @throws No lanza.
     */
    NodoBHoja(int _orden);

    /**
     * Libera los arreglos internos.
     * @pre Ninguna.
     * @post Memoria liberada.
     * @throws No lanza.
     */
    ~NodoBHoja();

    /**
     * Asigna un dato en la posición dada.
     * @pre 0 <= idx < orden.
     * @post El dato se almacena en el índice.
     * @param idx Posición destino.
     * @param g Nodo de grafo asociado.
     * @throws No lanza.
     */
    void establecer_dato(int idx, NodoGrafo* g);

    /**
     * Obtiene el dato almacenado en un índice.
     * @pre 0 <= idx < orden.
     * @post No modifica el nodo.
     * @param idx Posición a consultar.
     * @return Nodo asociado o 0 si está fuera de rango.
     * @throws No lanza.
     */
    NodoGrafo* obtener_dato(int idx) const;

    /**
     * Devuelve la hoja siguiente en la lista.
     * @pre Ninguna.
     * @post No modifica el nodo.
     * @return Puntero a la siguiente hoja o 0.
     * @throws No lanza.
     */
    NodoBHoja* obtener_siguiente() const;

    /**
     * Establece el enlace a la hoja siguiente.
     * @pre Ninguna.
     * @post Actualiza la referencia a la siguiente hoja.
     * @param s Nodo hoja siguiente.
     * @throws No lanza.
     */
    void establecer_siguiente(NodoBHoja* s);
};
