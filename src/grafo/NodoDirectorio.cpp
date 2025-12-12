#include "grafo/NodoDirectorio.h"

bool NodoDirectorio::es_directorio() { return true; }

int* NodoDirectorio::lista_hijos() {
    return hijos;
}

int NodoDirectorio::cantidad_hijos() const { return num_hijos; }

void NodoDirectorio::agregar_hijo(int id_hijo) {
    int* nuevo = new int[num_hijos + 1];
    for (int i = 0; i < num_hijos; ++i) nuevo[i] = hijos[i];
    nuevo[num_hijos] = id_hijo;
    delete[] hijos;
    hijos = nuevo;
    num_hijos += 1;
}

void NodoDirectorio::quitar_hijo(int id_hijo) {
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
