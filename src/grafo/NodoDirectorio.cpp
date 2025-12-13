#include "grafo/NodoDirectorio.h"

bool NodoDirectorio::es_directorio() {
    return true;
}

int* NodoDirectorio::lista_hijos() {
    return hijos;
}

int NodoDirectorio::cantidad_hijos() const {
    return num_hijos;
}

void NodoDirectorio::agregar_hijo(int id_hijo) {
    int* nuevo = new int[num_hijos + 1];
    if (hijos != 0) { // Evitar copiar desde puntero nulo
        for (int i = 0; i < num_hijos; ++i) {
            nuevo[i] = hijos[i];
        }
        delete[] hijos;
    }
    nuevo[num_hijos] = id_hijo;
    hijos = nuevo;
    num_hijos += 1;
}

void NodoDirectorio::quitar_hijo(int id_hijo) {
    if (num_hijos == 0 || !hijos) {
        return;
    }

    int nuevo_count = 0;
    for (int i = 0; i < num_hijos; ++i) {
        if (hijos[i] != id_hijo) {
            nuevo_count++;
        }
    }

    int* nuevo;
    if (nuevo_count > 0) {
        nuevo = new int[nuevo_count];
    } else {
        nuevo = 0;
    }

    int j = 0;
    for (int i = 0; i < num_hijos; ++i) {
        if (hijos[i] != id_hijo) {
            nuevo[j] = hijos[i];
            j++;
        }
    }

    delete[] hijos;
    hijos = nuevo;
    num_hijos = nuevo_count;
}
