#include "bplus/NodoBPlusBase.h"

NodoBPlusBase::NodoBPlusBase(int _orden, bool _hoja)
    : claves(0), orden(_orden), num_claves(0), hoja(_hoja) {
    if (orden > 0) {
        claves = new int[orden];
        // Inicializar claves a cero para evitar basura en memoria
        for (int i = 0; i < orden; ++i) {
            claves[i] = 0;
        }
    }
}

NodoBPlusBase::~NodoBPlusBase() {
    if (claves != 0) { // Seguridad: verificar antes de liberar
        delete[] claves;
        claves = 0;
    }
}

int NodoBPlusBase::obtener_orden() const {
    return orden;
}

int NodoBPlusBase::obtener_num_claves() const {
    return num_claves;
}

bool NodoBPlusBase::es_hoja() const {
    return hoja;
}

int* NodoBPlusBase::obtener_claves() const {
    return claves;
}

bool NodoBPlusBase::insertar_clave(int clave) {
    if (num_claves >= orden) {
        return false;
    }
    int pos = 0;
    while (pos < num_claves && claves[pos] < clave) {
        pos++;
    }
    for (int i = num_claves; i > pos; --i) {
        claves[i] = claves[i - 1];
    }
    claves[pos] = clave;
    num_claves++;
    return true;
}

void NodoBPlusBase::decrementar_num_claves() {
    if (num_claves > 0) {
        num_claves -= 1;
    }
}
