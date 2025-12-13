#include "Sistema.h"
#include <cstdio>
#include <cstring>

static void construir_rutas_recursivo(Sistema* sistema,
									   int id_actual,
									   int* pila_ids,
									   int profundidad,
									   char** rutas,
									   int* contador_rutas,
									   int max_rutas) {
	NodoGrafo* nodo = sistema->buscar_nodo_grafo(id_actual);
	if (nodo == 0) {
		return;
	}

	pila_ids[profundidad] = id_actual;

	int cantidad_padres = nodo->cantidad_padres();
	int* padres = nodo->lista_padres();

	if (cantidad_padres == 0) {
		if (*contador_rutas >= max_rutas) {
			return;
		}
		char buffer[256];
		int pos = 0;
		for (int i = profundidad; i >= 0; --i) {
			int escrito = std::snprintf(buffer + pos, 256 - pos, "/%d", pila_ids[i]);
			if (escrito < 0) {
				break;
			}
			pos += escrito;
			if (pos >= 255) {
				break;
			}
		}
		buffer[255] = '\0';

		char* ruta = new char[256];
		std::strncpy(ruta, buffer, 256);
		ruta[255] = '\0';

		rutas[*contador_rutas] = ruta;
		*contador_rutas = *contador_rutas + 1;
		return;
	}

	for (int i = 0; i < cantidad_padres; ++i) {
		construir_rutas_recursivo(sistema,
								   padres[i],
								   pila_ids,
								   profundidad + 1,
								   rutas,
								   contador_rutas,
								   max_rutas);
	}
}

static int sumar_espacio_recursivo(Sistema* sistema, int id_dir) {
	NodoGrafo* nodo = sistema->buscar_nodo_grafo(id_dir);
	if (nodo == 0) {
		return 0;
	}
	if (!nodo->es_directorio()) {
		NodoArchivo* archivo = (NodoArchivo*)nodo;
		int tam = archivo->obtener_tamano();
		return tam;
	}

	NodoDirectorio* dir = (NodoDirectorio*)nodo;
	int total = 0;
	int cantidad = dir->cantidad_hijos();
	int* hijos = dir->lista_hijos();
	for (int i = 0; i < cantidad; ++i) {
		total += sumar_espacio_recursivo(sistema, hijos[i]);
	}
	return total;
}

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
	NodoGrafo* nodo_archivo = indice_bplus.buscar(id_archivo);
	if (nodo_archivo == 0) {
		return;
	}
	if (nodo_archivo->es_directorio()) {
		return;
	}

	NodoGrafo* nodo_padre = indice_bplus.buscar(id_directorio_padre);
	if (nodo_padre == 0) {
		return;
	}

	NodoDirectorio* directorio_padre = (NodoDirectorio*)nodo_padre;
	directorio_padre->quitar_hijo(id_archivo);

	nodo_archivo->quitar_padre(id_directorio_padre);
	int restantes = nodo_archivo->cantidad_padres();
	if (restantes <= 0) {
		indice_bplus.eliminar(id_archivo);
	}
}

int* Sistema::listar_contenido(int id_directorio) {
	NodoGrafo* nodo = indice_bplus.buscar(id_directorio);
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
		int id_hijo = origen[i];
		copia[i] = id_hijo;
		buscar_nodo_grafo(id_hijo);
	}
	return copia;
}

char** Sistema::obtener_rutas_completas(int d) {
	NodoGrafo* nodo = indice_bplus.buscar(d);
	if (nodo == 0) {
		return 0;
	}

	const int max_rutas = 32;
	char** rutas = new char*[max_rutas + 1];
	for (int i = 0; i < max_rutas + 1; ++i) {
		rutas[i] = 0;
	}
	int pila_ids[64];
	int contador = 0;
	construir_rutas_recursivo(this, d, pila_ids, 0, rutas, &contador, max_rutas);
	rutas[contador] = 0;
	return rutas;
}

int Sistema::calcular_espacio_ocupado(int d) {
	NodoGrafo* nodo = indice_bplus.buscar(d);
	if (nodo == 0) {
		return 0;
	}
	if (!nodo->es_directorio()) {
		NodoArchivo* archivo = (NodoArchivo*)nodo;
		int tam = archivo->obtener_tamano();
		return tam;
	}
	int total = sumar_espacio_recursivo(this, d);
	return total;
}
