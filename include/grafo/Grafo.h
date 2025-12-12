#pragma once

#include "grafo/NodoGrafo.h"

class Grafo {
public:
    // Inserta una arista padre->hijo en el grafo
    void agregar_contenido(NodoGrafo* padre, NodoGrafo* hijo);
    // Obtiene los hijos de un directorio (puntero a arreglo, segun especificacion)
    int* obtener_hijos_ids(NodoGrafo* directorio);
    // Obtiene los padres de un nodo (puntero a arreglo, segun especificacion)
    int* obtener_padres_ids(NodoGrafo* nodo);
};
