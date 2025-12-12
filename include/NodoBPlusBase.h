#pragma once
#include "NodoGrafo.h"

class NodoBPlusBase {
private:
    int* claves; // vector de ids de NodoGrafo
    int orden;   // factor m de árbol
    bool es_hoja; // indica si es nodo interno o hoja del árbol
};
