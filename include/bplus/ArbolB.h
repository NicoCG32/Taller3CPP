#pragma once

#include "grafo/NodoGrafo.h"
#include "bplus/NodoBPlusBase.h"
#include "bplus/NodoBInterno.h"
#include "bplus/NodoBHoja.h"

class ArbolB {
public:
    // Inserta un Nodo en la hoja
    void insertar(int clave, NodoGrafo* nodo);
    // Busca desde la raiz y entrega el Nodo
    NodoGrafo* buscar(int clave);
    // Devuelve el numero de accesos simulados al B+
    int obtener_accesos() const;
    // Nota: Estas funciones requieren la estructura y lógica de un Árbol B+.
    // En particular:
    // - Descenso por nodos internos usando las claves para seleccionar punteros.
    // - Inserción ordenada en hojas y manejo de overflow mediante split.
    // - Promoción de claves hacia nodos internos y posibles splits recursivos.
    // - Uso de la lista enlazada de hojas para recorridos secuenciales.
};
