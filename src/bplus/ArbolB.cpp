#include "bplus/ArbolB.h"

static int contador_accesos_bplus = 0;

void ArbolB::insertar(int clave, NodoGrafo* nodo_grafo) {
    // Caso 1: Árbol vacío - crear primera hoja como raíz
    if (!raiz) {
        NodoBHoja* nodo_hoja = new NodoBHoja(orden);
        nodo_hoja->insertar_clave(clave);
        nodo_hoja->establecer_dato(0, nodo_grafo);
        raiz = nodo_hoja;
        contador_accesos_bplus += 1;
        return;
    }

    contador_accesos_bplus += 1;
    
    NodoBPlusBase* ruta_padres[64]; // Corregido: Guardar camino para propagar splits hacia arriba
    int profundidad = 0;
    NodoBPlusBase* nodo_actual = raiz;
    
    // Descender desde raíz hasta hoja, guardando ruta de padres
    while (!nodo_actual->es_hoja()) {
        ruta_padres[profundidad] = nodo_actual; // Guardar padre para propagación posterior
        profundidad++;
        
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        // Encontrar puntero correcto comparando con claves
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
        contador_accesos_bplus += 1;
    }

    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);

    // Caso 2: Hoja con espacio disponible - insertar directamente
    if (nodo_hoja->insertar_clave(clave)) {
        int* claves = nodo_hoja->obtener_claves();
        int cantidad_claves = nodo_hoja->obtener_num_claves();
        int posicion_insercion = 0;
        // Buscar posición donde se insertó la clave
        while (posicion_insercion < cantidad_claves && claves[posicion_insercion] != clave) {
            posicion_insercion++;
        }
        nodo_hoja->establecer_dato(posicion_insercion, nodo_grafo);
        contador_accesos_bplus += 1;
        return;
    }

    // Caso 3: Hoja llena - dividir nodo (split)
    NodoBHoja* nodo_hoja_nueva = new NodoBHoja(orden);

    int cantidad_claves = nodo_hoja->obtener_num_claves();
    int* claves_temporales = new int[cantidad_claves + 1];
    NodoGrafo** datos_temporales = new NodoGrafo*[cantidad_claves + 1];
    int* claves = nodo_hoja->obtener_claves();
    // Copiar claves y datos existentes a arrays temporales
    for (int i = 0; i < cantidad_claves; ++i) {
        claves_temporales[i] = claves[i];
        datos_temporales[i] = nodo_hoja->obtener_dato(i);
    }
    // Encontrar posición para nueva clave
    int posicion_insercion = 0;
    while (posicion_insercion < cantidad_claves && claves_temporales[posicion_insercion] < clave) {
        posicion_insercion++;
    }
    // Desplazar elementos para insertar nueva clave en posición correcta
    for (int i = cantidad_claves; i > posicion_insercion; --i) {
        claves_temporales[i] = claves_temporales[i - 1];
        datos_temporales[i] = datos_temporales[i - 1];
    }
    claves_temporales[posicion_insercion] = clave;
    datos_temporales[posicion_insercion] = nodo_grafo;

    int mitad = (cantidad_claves + 1) / 2; // Calcular punto de división

    // Limpiar nodo hoja original
    for (int i = 0; i < nodo_hoja->obtener_orden(); ++i) {
        nodo_hoja->establecer_dato(i, 0);
    }
    while (nodo_hoja->obtener_num_claves() > 0) {
        nodo_hoja->decrementar_num_claves();
    }

    // Distribuir primera mitad en nodo original
    for (int i = 0; i < mitad; ++i) {
        nodo_hoja->insertar_clave(claves_temporales[i]);
        nodo_hoja->establecer_dato(i, datos_temporales[i]);
    }
    // Distribuir segunda mitad en nodo nuevo
    for (int i = mitad; i < cantidad_claves + 1; ++i) {
        nodo_hoja_nueva->insertar_clave(claves_temporales[i]);
        nodo_hoja_nueva->establecer_dato(i - mitad, datos_temporales[i]);
    }

    // Actualizar enlaces de lista secuencial de hojas
    nodo_hoja_nueva->establecer_siguiente(nodo_hoja->obtener_siguiente());
    nodo_hoja->establecer_siguiente(nodo_hoja_nueva);

    int clave_promocion = claves_temporales[mitad]; // Clave a promover al padre
    NodoBPlusBase* hijo_derecho = nodo_hoja_nueva; // Corregido: Preparar para propagación de split

    delete[] claves_temporales;
    delete[] datos_temporales;

    // Si la hoja dividida era la raíz, crear nueva raíz interna
    if (nodo_hoja == raiz) {
        NodoBInterno* nueva_raiz = new NodoBInterno(orden);
        nueva_raiz->insertar_clave(clave_promocion);
        nueva_raiz->establecer_puntero(0, nodo_hoja);
        nueva_raiz->establecer_puntero(1, nodo_hoja_nueva);
        raiz = nueva_raiz;
        contador_accesos_bplus += 2;
        return;
    }

    // Propagar clave promocionada hacia arriba, dividiendo nodos internos si es necesario
    while (profundidad > 0) { // Corregido: Propagar splits de nodos internos hacia arriba - faltaba completamente
        profundidad--;
        NodoBInterno* padre = static_cast<NodoBInterno*>(ruta_padres[profundidad]);
        
        // Intentar insertar clave promocionada en padre
        if (padre->insertar_clave(clave_promocion)) {
            int* claves_padre = padre->obtener_claves();
            int num_claves_padre = padre->obtener_num_claves();
            int pos_insertar = 0;
            // Encontrar posición donde se insertó la clave
            while (pos_insertar < num_claves_padre && claves_padre[pos_insertar] != clave_promocion) {
                pos_insertar++;
            }
            // Desplazar punteros para hacer espacio al nuevo hijo derecho
            for (int i = num_claves_padre; i > pos_insertar + 1; --i) {
                padre->establecer_puntero(i, padre->obtener_puntero(i - 1));
            }
            padre->establecer_puntero(pos_insertar + 1, hijo_derecho);
            contador_accesos_bplus += 1;
            return; // Inserción exitosa, terminar
        }

        // Padre lleno - dividir nodo interno
        NodoBInterno* nodo_interno_nuevo = new NodoBInterno(orden);
        int num_claves_padre = padre->obtener_num_claves();
        int* claves_temp_interno = new int[num_claves_padre + 1];
        NodoBPlusBase** punteros_temp = new NodoBPlusBase*[num_claves_padre + 2];
        
        // Copiar claves existentes del padre
        int* claves_padre = padre->obtener_claves();
        for (int i = 0; i < num_claves_padre; ++i) {
            claves_temp_interno[i] = claves_padre[i];
        }
        // Copiar punteros existentes del padre
        for (int i = 0; i <= num_claves_padre; ++i) {
            punteros_temp[i] = padre->obtener_puntero(i);
        }
        
        // Encontrar posición para insertar nueva clave
        int pos_insertar = 0;
        while (pos_insertar < num_claves_padre && claves_temp_interno[pos_insertar] < clave_promocion) {
            pos_insertar++;
        }
        
        // Insertar clave promocionada en arrays temporales
        for (int i = num_claves_padre; i > pos_insertar; --i) {
            claves_temp_interno[i] = claves_temp_interno[i - 1];
        }
        claves_temp_interno[pos_insertar] = clave_promocion;
        
        // Insertar nuevo puntero derecho en arrays temporales
        for (int i = num_claves_padre + 1; i > pos_insertar + 1; --i) {
            punteros_temp[i] = punteros_temp[i - 1];
        }
        punteros_temp[pos_insertar + 1] = hijo_derecho;
        
        int mitad_interno = (num_claves_padre + 1) / 2; // Punto de división
        int clave_promocion_nueva = claves_temp_interno[mitad_interno]; // Clave del medio sube
        
        // Limpiar padre para reconstruir con primera mitad
        while (padre->obtener_num_claves() > 0) {
            padre->decrementar_num_claves();
        }
        
        // Colocar primera mitad de claves en padre (antes de mitad)
        for (int i = 0; i < mitad_interno; ++i) {
            padre->insertar_clave(claves_temp_interno[i]);
        }
        // Colocar punteros correspondientes en padre
        for (int i = 0; i <= mitad_interno; ++i) {
            padre->establecer_puntero(i, punteros_temp[i]);
        }
        
        // Colocar segunda mitad de claves en nuevo nodo interno (después de mitad)
        for (int i = mitad_interno + 1; i < num_claves_padre + 1; ++i) {
            nodo_interno_nuevo->insertar_clave(claves_temp_interno[i]);
        }
        // Colocar punteros correspondientes en nuevo nodo interno
        for (int i = mitad_interno + 1; i <= num_claves_padre + 1; ++i) {
            nodo_interno_nuevo->establecer_puntero(i - mitad_interno - 1, punteros_temp[i]);
        }
        
        delete[] claves_temp_interno;
        delete[] punteros_temp;
        
        // Si padre dividido era raíz, crear nueva raíz
        if (padre == raiz) {
            NodoBInterno* nueva_raiz = new NodoBInterno(orden);
            nueva_raiz->insertar_clave(clave_promocion_nueva);
            nueva_raiz->establecer_puntero(0, padre);
            nueva_raiz->establecer_puntero(1, nodo_interno_nuevo);
            raiz = nueva_raiz;
            contador_accesos_bplus += 2;
            return;
        }
        
        // Continuar propagación hacia arriba con nueva clave y nuevo nodo
        clave_promocion = clave_promocion_nueva;
        hijo_derecho = nodo_interno_nuevo;
        contador_accesos_bplus += 1;
    }
}

NodoGrafo* ArbolB::buscar(int clave) {
    // Árbol vacío - no encontrado
    if (!raiz) {
        return 0;
    }

    contador_accesos_bplus += 1; // Simular acceso a disco en raíz
    NodoBPlusBase* nodo_actual = raiz;

    // Descender desde raíz hasta hoja siguiendo punteros apropiados
    while (!nodo_actual->es_hoja()) {
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        // Encontrar puntero correcto comparando clave buscada con claves del nodo
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
        contador_accesos_bplus += 1; // Simular acceso a disco en cada nivel
    }

    // Buscar clave en el nodo hoja
    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);
    int* claves = nodo_hoja->obtener_claves();
    int cantidad_claves = nodo_hoja->obtener_num_claves();
    for (int i = 0; i < cantidad_claves; ++i) {
        if (claves[i] == clave) {
            return nodo_hoja->obtener_dato(i); // Retornar dato asociado
        }
    }
    return 0; // No encontrado
}

bool ArbolB::eliminar(int clave) {
    NodoBPlusBase* nodo_actual = raiz;
    // Árbol vacío - no se puede eliminar
    if (!nodo_actual) {
        return false;
    }

    // Descender desde raíz hasta hoja que contiene la clave
    while (!nodo_actual->es_hoja()) {
        NodoBInterno* nodo_interno = static_cast<NodoBInterno*>(nodo_actual);
        int indice_puntero = 0;
        int* claves = nodo_actual->obtener_claves();
        int cantidad_claves = nodo_actual->obtener_num_claves();
        // Encontrar puntero correcto comparando con claves
        while (indice_puntero < cantidad_claves && claves[indice_puntero] <= clave) {
            indice_puntero++;
        }
        nodo_actual = nodo_interno->obtener_puntero(indice_puntero);
    }

    NodoBHoja* nodo_hoja = static_cast<NodoBHoja*>(nodo_actual);
    int* claves = nodo_hoja->obtener_claves();
    int cantidad_claves = nodo_hoja->obtener_num_claves();

    // Buscar posición de la clave a eliminar
    int posicion_eliminar = -1;
    for (int i = 0; i < cantidad_claves; ++i) {
        if (claves[i] == clave) {
            posicion_eliminar = i;
            break;
        }
    }
    // Clave no encontrada
    if (posicion_eliminar == -1) {
        return false;
    }

    // Desplazar elementos hacia la izquierda para eliminar la clave
    for (int i = posicion_eliminar; i < cantidad_claves - 1; ++i) {
        claves[i] = claves[i + 1];
        nodo_hoja->establecer_dato(i, nodo_hoja->obtener_dato(i + 1));
    }

    // Limpiar última posición y decrementar contador
    nodo_hoja->establecer_dato(cantidad_claves - 1, 0);
    nodo_hoja->decrementar_num_claves();

    contador_accesos_bplus += 1; // Simular acceso a disco
    return true;
}

int ArbolB::obtener_accesos() const {
    return contador_accesos_bplus;
}
