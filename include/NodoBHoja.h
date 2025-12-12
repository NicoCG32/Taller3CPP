#pragma once
#include "NodoBPlusBase.h"

class NodoBHoja : public NodoBPlusBase {
private:
    NodoGrafo** datos;      // vector del tipo NodoGrafo*
    NodoBHoja* siguiente_hoja; // puntero del tipo NodoBHoja*
};
