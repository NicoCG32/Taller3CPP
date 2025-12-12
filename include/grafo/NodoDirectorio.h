#pragma once
#include "grafo/NodoGrafo.h"

class NodoDirectorio : public NodoGrafo {
public:
    bool es_directorio() { return true; }
    int* lista_hijos();
    int cantidad_hijos() const { return num_hijos; }
    void agregar_hijo(int id_hijo) {
        int* nuevo = new int[num_hijos + 1];
        for (int i = 0; i < num_hijos; ++i) nuevo[i] = hijos[i];
        nuevo[num_hijos] = id_hijo;
        delete[] hijos;
        hijos = nuevo;
        num_hijos += 1;
    }
    void quitar_hijo(int id_hijo) {
        if (num_hijos == 0 || !hijos) return;
        int nuevo_count = 0;
        for (int i = 0; i < num_hijos; ++i) if (hijos[i] != id_hijo) nuevo_count++;
        int* nuevo = nuevo_count ? new int[nuevo_count] : 0;
        int j = 0;
        for (int i = 0; i < num_hijos; ++i) if (hijos[i] != id_hijo) { nuevo[j++] = hijos[i]; }
        delete[] hijos;
        hijos = nuevo;
        num_hijos = nuevo_count;
    }

private:
    int* hijos = 0;
    int num_hijos = 0;
};
