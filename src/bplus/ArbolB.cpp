#include "bplus/ArbolB.h"

static int accesos_bplus = 0;

void ArbolB::insertar(int clave, NodoGrafo* nodo) {
    accesos_bplus += 1;
}

NodoGrafo* ArbolB::buscar(int clave) {
    accesos_bplus += 1;
    return nullptr;
}

int ArbolB::obtener_accesos() const {
    return accesos_bplus;
}
