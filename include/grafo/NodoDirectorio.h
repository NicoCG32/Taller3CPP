#pragma once
#include "NodoGrafo.h"

class NodoDirectorio : public NodoGrafo {
public:
    bool es_directorio() { return true; }

    // Retorna un vector (puntero) con los ids de los hijos
    int* lista_hijos();
};
