#include "Sistema.h"

void Sistema::insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo) {
	if (nodo_grafo == 0) {
		return;
	}
	indice_bplus.insertar(clave, nodo_grafo);
}

NodoGrafo* Sistema::buscar_nodo_grafo(int clave) {
    NodoGrafo* nodo = indice_bplus.buscar(clave);
    if (nodo == 0) {
        return nullptr;
    }
	return nodo;
}

void Sistema::crear_nodo(int id_padre) {
	NodoGrafo* nodo_padre = indice_bplus.buscar(id_padre);
	if (nodo_padre == 0) {
		return;
	}

	NodoDirectorio* directorio_padre = (NodoDirectorio*)nodo_padre;
	int cantidad = directorio_padre->cantidad_hijos();
	int nuevo_id = id_padre + cantidad + 1;

	NodoDirectorio* nuevo_nodo = new NodoDirectorio();
	nuevo_nodo->establecer_id(nuevo_id);
	nuevo_nodo->agregar_padre(id_padre);

	directorio_padre->agregar_hijo(nuevo_id);
	indice_bplus.insertar(nuevo_id, nuevo_nodo);
}

void Sistema::eliminar_archivo(int id_archivo, int id_directorio_padre) {
	NodoGrafo* nodo_padre = indice_bplus.buscar(id_directorio_padre);
	if (nodo_padre == 0) {
		return;
	}
	NodoDirectorio* directorio_padre = (NodoDirectorio*)nodo_padre;
	directorio_padre->quitar_hijo(id_archivo);
	indice_bplus.eliminar(id_archivo);
}

int* Sistema::listar_contenido(int d) {
	NodoGrafo* nodo = indice_bplus.buscar(d);
	if (nodo == 0) {
		return 0;
	}
	NodoDirectorio* dir = (NodoDirectorio*)nodo;
	int cantidad = dir->cantidad_hijos();
	if (cantidad <= 0) {
		return 0;
	}
	int* origen = dir->lista_hijos();
	int* copia = new int[cantidad];
	for (int i = 0; i < cantidad; ++i) {
		copia[i] = origen[i];
	}
	return copia;
}

char** Sistema::obtener_rutas_completas(int d) { return 0; }

int Sistema::calcular_espacio_ocupado(int d) { return 0; }
