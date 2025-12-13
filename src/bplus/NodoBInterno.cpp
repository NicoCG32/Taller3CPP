#include "bplus/NodoBInterno.h"

int NodoBInterno::buscar_siguiente() {
    if (obtener_num_claves() == 0) {
        return 0;
    }
    return obtener_num_claves();
}

NodoBInterno::NodoBInterno(int _orden) : NodoBPlusBase(_orden, false), punteros(0) {
    if (_orden > 0) {
        punteros = new NodoBPlusBase*[_orden + 1];
    }
    for (int i = 0; i < _orden + 1; ++i) {
        punteros[i] = 0;
    }
}

NodoBInterno::~NodoBInterno() {
    if (punteros != 0) { // Seguridad: verificar antes de liberar
        delete[] punteros;
        punteros = 0;
    }
}

void NodoBInterno::establecer_puntero(int idx, NodoBPlusBase* nodo) {
    if (idx >= 0 && idx < obtener_orden() + 1) {
        punteros[idx] = nodo;
    }
}

NodoBPlusBase* NodoBInterno::obtener_puntero(int idx) const {
    if (idx >= 0 && idx < obtener_orden() + 1) {
        return punteros[idx];
    }
    return 0;
}
