#pragma once

#include "grafo/NodoGrafo.h"
#include "bplus/NodoBPlusBase.h"
#include "bplus/NodoBInterno.h"
#include "bplus/NodoBHoja.h"

class ArbolB {
private:
    NodoBPlusBase* raiz = 0;
    int orden = 4;

public:
    void insertar(int clave, NodoGrafo* nodo);
    NodoGrafo* buscar(int clave);
    bool eliminar(int clave);
    int obtener_accesos() const;
};
