#pragma once
#include "bplus/NodoBPlusBase.h"
#include "grafo/NodoGrafo.h"

class NodoBHoja : public NodoBPlusBase {
private:
    NodoGrafo** datos;
    NodoBHoja* siguiente_hoja;
};
