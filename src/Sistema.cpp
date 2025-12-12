#include "Sistema.h"

void Sistema::insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo) {
	if (nodo_grafo == 0) {
		return;
	}
	indice_bplus.insertar(clave, nodo_grafo);
}

NodoGrafo* Sistema::buscar_nodo_grafo(int clave) {
	return indice_bplus.buscar(clave);
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

	directorio_padre->agregar_hijo(nuevo_id);
	indice_bplus.insertar(nuevo_id, nuevo_nodo);
}

void Sistema::eliminar_archivo(int, int) {}

int* Sistema::listar_contenido(int) { return 0; }

char** Sistema::obtener_rutas_completas(int) { return 0; }

int Sistema::calcular_espacio_ocupado(int) { return 0; }
