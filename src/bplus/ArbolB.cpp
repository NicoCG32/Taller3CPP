#include "bplus/ArbolB.h"

static int accesos_bplus = 0;

void ArbolB::insertar(int clave, NodoGrafo* nodo) {
    // Simulacion: incrementar accesos por escritura
    accesos_bplus += 1;
}

NodoGrafo* ArbolB::buscar(int clave) {
    // Simulacion: incrementar accesos por lectura
    accesos_bplus += 1;
    return nullptr;
}

int ArbolB::obtener_accesos() const {
    return accesos_bplus;
}
