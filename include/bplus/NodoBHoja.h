#pragma once
#include "bplus/NodoBPlusBase.h"
#include "grafo/NodoGrafo.h"

class NodoBHoja : public NodoBPlusBase {
private:
    NodoGrafo** datos;
    NodoBHoja* siguiente_hoja;
public:
    NodoBHoja(int _orden);
    ~NodoBHoja();
    void establecer_dato(int idx, NodoGrafo* g);
    NodoGrafo* obtener_dato(int idx) const;
    NodoBHoja* obtener_siguiente() const;
    void establecer_siguiente(NodoBHoja* s);
};
