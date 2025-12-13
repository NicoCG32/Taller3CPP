#pragma once

#include "grafo/NodoGrafo.h"

/**
 * Gestor de relaciones de herencia entre nodos (grafo).
 * @pre Ninguna.
 * @post Mantiene referencias padre-hijo entre nodos.
 * @author Pablo Guzmán
 */
class Grafo {
public:
    /**
     * Inserta una arista padre->hijo en el grafo.
     * @pre padre y hijo distintos de nulo.
     * @post Establece relación bidireccional.
     * @param padre Nodo padre (progenitor).
     * @param hijo Nodo hijo (descendiente).
     * @throws No lanza.
     */
    void agregar_contenido(NodoGrafo* padre, NodoGrafo* hijo);

    /**
     * Obtiene los identificadores de hijos de un directorio.
     * @pre directorio es un NodoDirectorio.
     * @post No modifica el grafo.
     * @param directorio Nodo padre consultado.
     * @return Arreglo de ids de hijos o 0 si no hay.
     * @throws No lanza.
     */
    int* obtener_hijos_ids(NodoGrafo* directorio);

    /**
     * Obtiene los identificadores de padres de un nodo.
     * @pre Ninguna.
     * @post No modifica el grafo.
     * @param nodo Nodo consultado.
     * @return Arreglo de ids de padres o 0 si no hay.
     * @throws No lanza.
     */
    int* obtener_padres_ids(NodoGrafo* nodo);
};
