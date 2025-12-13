#pragma once
#include "bplus/NodoBPlusBase.h"

/**
 * Nodo interno del árbol B+ que almacena punteros a hijos.
 * Me inspiré en una implementación genérica debido al tiempo tardío en que empecé el taller, lamento eso.
 * @pre Orden mayor que cero.
 * @post Mantiene arreglo de claves y punteros hijo.
 * 
 * @author Pablo Guzmán
 */
class NodoBInterno : public NodoBPlusBase {
private:
    NodoBPlusBase** punteros;
public:
    /**
     * Construye un nodo interno.
     * @pre _orden > 0.
     * @post Reserva punteros a hijos y los inicializa.
     * @param _orden Capacidad de claves del nodo.
     * @throws No lanza.
     */
    NodoBInterno(int _orden);

    /**
     * Libera memoria de punteros.
     * @pre Ninguna.
     * @post Memoria asociada liberada.
     * @throws No lanza.
     */
    ~NodoBInterno();

    /**
     * Retorna el índice después de la última clave usada.
     * @pre Ninguna.
     * @post No modifica el nodo.
     * @return Índice del siguiente puntero válido.
     * @throws No lanza.
     */
    int buscar_siguiente();

    /**
     * Define un puntero hijo en la posición indicada.
     * @pre 0 <= idx < orden + 1.
     * @post El puntero queda asociado a la posición.
     * @param idx Índice donde colocar el hijo.
     * @param nodo Nodo hijo a enlazar.
     * @throws No lanza.
     */
    void establecer_puntero(int idx, NodoBPlusBase* nodo);

    /**
     * Obtiene un puntero hijo.
     * @pre 0 <= idx < orden + 1.
     * @post No modifica el nodo.
     * @param idx Índice consultado.
     * @return Puntero al hijo o 0 si está fuera de rango.
     * @throws No lanza.
     */
    NodoBPlusBase* obtener_puntero(int idx) const;
};
