#pragma once
#include "NodoBPlusBase.h"

class NodoBInterno : public NodoBPlusBase {
private:
    NodoBPlusBase** punteros; // vector del tipo NodoBPlusBase*

public:
    // función que dado un id de NodoGrafo indica a cual Nodo del árbol B hay que moverse.
    // Devuelve el índice de vector punteros.
    int buscar_siguiente();
};
