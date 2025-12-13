#include "grafo/NodoGrafo.h"

NodoGrafo::NodoGrafo() : id(-1), padres(0), num_padres(0) {
}

NodoGrafo::NodoGrafo(int _id) : id(_id), padres(0), num_padres(0) {
}

NodoGrafo::~NodoGrafo() {
	if (padres != 0) {
		delete[] padres; // Corregido: Fuga de memoria - array padres no se liberaba
		padres = 0;
	}
}

int NodoGrafo::obtener_id() const {
    return id;
}

void NodoGrafo::establecer_id(int nuevo_id) {
    id = nuevo_id;
}

int* NodoGrafo::lista_padres() {
    return padres;
}

int NodoGrafo::cantidad_padres() const {
    return num_padres;
}

void NodoGrafo::agregar_padre(int id_padre) {
    int* nuevo = new int[num_padres + 1];
    for (int i = 0; i < num_padres; ++i) {
        nuevo[i] = padres[i];
    }
    nuevo[num_padres] = id_padre;
    delete[] padres;
    padres = nuevo;
    num_padres += 1;
}

void NodoGrafo::quitar_padre(int id_padre) {
    if (num_padres == 0 || !padres) {
        return;
    }
    int nuevo_count = 0;
    for (int i = 0; i < num_padres; ++i) {
        if (padres[i] != id_padre) {
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
    for (int i = 0; i < num_padres; ++i) {
        if (padres[i] != id_padre) {
            nuevo[j] = padres[i];
            j++;
        }
    }
    delete[] padres;
    padres = nuevo;
    num_padres = nuevo_count;
}
