#pragma once
#include "grafo/NodoGrafo.h"

class NodoDirectorio : public NodoGrafo {
    
public:
    bool es_directorio();

    int* lista_hijos();

    int cantidad_hijos() const;

    void agregar_hijo(int id_hijo);
    
    void quitar_hijo(int id_hijo);

private:
    int* hijos = 0;
    int num_hijos = 0;
};
