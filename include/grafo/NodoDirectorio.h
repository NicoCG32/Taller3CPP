#pragma once
#include "grafo/NodoGrafo.h"

class NodoDirectorio : public NodoGrafo {
public:
    bool es_directorio() { return true; }
    int* lista_hijos();
};
