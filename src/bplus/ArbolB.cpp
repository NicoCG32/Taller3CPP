#include "bplus/ArbolB.h"

static int contador_accesos_bplus = 0;

void ArbolB::insertar(int clave, NodoGrafo* nodo_grafo) {
    if (!raiz) {
        NodoBHoja* nodo_hoja = new NodoBHoja(orden);
        nodo_hoja->insertar_clave(clave);
        nodo_hoja->establecer_dato(0, nodo_grafo);
        raiz = nodo_hoja;
        contador_accesos_bplus += 1;
        return;
    }

    contador_accesos_bplus += 1;
    NodoBPlusBase* nodo_actual = raiz;
    while (!nodo_actual->es_hoja()) {
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
        contador_accesos_bplus += 1;
    }

    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);

    if (nodo_hoja->insertar_clave(clave)) {
        int* claves = nodo_hoja->obtener_claves();
        int cantidad_claves = nodo_hoja->obtener_num_claves();
        int posicion_insercion = 0;
        while (posicion_insercion < cantidad_claves && claves[posicion_insercion] != clave) {
            posicion_insercion++;
        }
        nodo_hoja->establecer_dato(posicion_insercion, nodo_grafo);
        contador_accesos_bplus += 1;
        return;
    }

    NodoBHoja* nodo_hoja_nueva = new NodoBHoja(orden);

    int cantidad_claves = nodo_hoja->obtener_num_claves();
    int* claves_temporales = new int[cantidad_claves + 1];
    NodoGrafo** datos_temporales = new NodoGrafo*[cantidad_claves + 1];
    int* claves = nodo_hoja->obtener_claves();
    for (int i = 0; i < cantidad_claves; ++i) {
        claves_temporales[i] = claves[i];
        datos_temporales[i] = nodo_hoja->obtener_dato(i);
    }
    int posicion_insercion = 0;
    while (posicion_insercion < cantidad_claves && claves_temporales[posicion_insercion] < clave) {
        posicion_insercion++;
    }
    for (int i = cantidad_claves; i > posicion_insercion; --i) {
        claves_temporales[i] = claves_temporales[i - 1];
        datos_temporales[i] = datos_temporales[i - 1];
    }
    claves_temporales[posicion_insercion] = clave;
    datos_temporales[posicion_insercion] = nodo_grafo;

    int mitad = (cantidad_claves + 1) / 2;

    for (int i = 0; i < nodo_hoja->obtener_orden(); ++i) {
        nodo_hoja->establecer_dato(i, 0);
    }
    while (nodo_hoja->obtener_num_claves() > 0) {
        nodo_hoja->decrementar_num_claves();
    }

    for (int i = 0; i < mitad; ++i) {
        nodo_hoja->insertar_clave(claves_temporales[i]);
        nodo_hoja->establecer_dato(i, datos_temporales[i]);
    }
    for (int i = mitad; i < cantidad_claves + 1; ++i) {
        nodo_hoja_nueva->insertar_clave(claves_temporales[i]);
        nodo_hoja_nueva->establecer_dato(i - mitad, datos_temporales[i]);
    }

    nodo_hoja_nueva->establecer_siguiente(nodo_hoja->obtener_siguiente());
    nodo_hoja->establecer_siguiente(nodo_hoja_nueva);

    int clave_promocion = claves_temporales[mitad];

    delete[] claves_temporales;
    delete[] datos_temporales;

    if (nodo_hoja == raiz) {
        NodoBInterno* nueva_raiz = new NodoBInterno(orden);
        nueva_raiz->insertar_clave(clave_promocion);
        nueva_raiz->establecer_puntero(0, nodo_hoja);
        nueva_raiz->establecer_puntero(1, nodo_hoja_nueva);
        raiz = nueva_raiz;
    }

    contador_accesos_bplus += 2; // uno para el nodo hoja y otro para la nueva raiz
}

NodoGrafo* ArbolB::buscar(int clave) {
    if (!raiz) {
        return 0;
    }

    contador_accesos_bplus += 1;
    NodoBPlusBase* nodo_actual = raiz;

    while (!nodo_actual->es_hoja()) {
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
        contador_accesos_bplus += 1;
    }

    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);
    int* claves = nodo_hoja->obtener_claves();
    int cantidad_claves = nodo_hoja->obtener_num_claves();
    for (int i = 0; i < cantidad_claves; ++i) {
        if (claves[i] == clave) {
            return nodo_hoja->obtener_dato(i);
        }
    }
    return 0;
}

bool ArbolB::eliminar(int clave) {
    NodoBPlusBase* nodo_actual = raiz;
    if (!nodo_actual) {
        return false;
    }

    while (!nodo_actual->es_hoja()) {
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
    }

    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);
    int* claves = nodo_hoja->obtener_claves();
    int cantidad_claves = nodo_hoja->obtener_num_claves();

    int posicion_eliminar = -1;
    for (int i = 0; i < cantidad_claves; ++i) {
        if (claves[i] == clave) {
            posicion_eliminar = i;
            break;
        }
    }
    if (posicion_eliminar == -1) {
        return false;
    }

    for (int i = posicion_eliminar; i < cantidad_claves - 1; ++i) {
        claves[i] = claves[i + 1];
        nodo_hoja->establecer_dato(i, nodo_hoja->obtener_dato(i + 1));
    }

    nodo_hoja->establecer_dato(cantidad_claves - 1, 0);
    nodo_hoja->decrementar_num_claves();

    contador_accesos_bplus += 1;
    return true;
}

int ArbolB::obtener_accesos() const {
    return contador_accesos_bplus;
}
