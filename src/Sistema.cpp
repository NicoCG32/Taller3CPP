#include "Sistema.h"
#include <cstring>

static int contador_id_global = 1000; // Corregido: Evita colisiones de IDs - antes usaba id_padre + cantidad que generaba duplicados

static void escribir_id(char* buffer, int* pos, int valor) {
	int temp[12];
	int len = 0;
	if (valor == 0) {
		if (*pos < 255) { buffer[*pos] = '0'; *pos += 1; }
		return;
	}
	while (valor > 0 && len < 12) { temp[len] = valor % 10; valor /= 10; len++; }
	for (int i = len - 1; i >= 0; --i) {
		if (*pos < 255) { buffer[*pos] = char('0' + temp[i]); *pos += 1; }
	}
}

static void construir_rutas_con_stack(Sistema* sistema, int id_inicio, char** rutas, int* contador_rutas, int max_rutas) {
	Stack<EstadoDFS*> pila;
	EstadoDFS* inicio = new EstadoDFS;
	inicio->id = id_inicio;
	inicio->profundidad = 0;
	inicio->camino[0] = id_inicio;
	Nodo<EstadoDFS*>* nodo_ini = new Nodo<EstadoDFS*>(inicio);
	pila.push(nodo_ini);

	while (!pila.empty()) {
		Nodo<EstadoDFS*>* nodo_pila = pila.pop();
		EstadoDFS* estado = nodo_pila->dato;
		delete nodo_pila;

		NodoGrafo* nodo = sistema->buscar_nodo_grafo(estado->id);
		if (nodo == 0) { delete estado; continue; }

		int cantidad_padres = nodo->cantidad_padres();
		int* padres = nodo->lista_padres();

		if (cantidad_padres == 0) {
			if (*contador_rutas < max_rutas) {
				char buffer[256];
				int pos = 0;
				for (int i = estado->profundidad; i >= 0 && pos < 255; --i) {
					if (pos < 255) { buffer[pos] = '/'; pos++; }
					escribir_id(buffer, &pos, estado->camino[i]);
				}
				if (pos >= 256) pos = 255;
				buffer[pos] = '\0';
				char* ruta = new char[256];
				int k = 0;
				while (buffer[k] != '\0' && k < 255) { ruta[k] = buffer[k]; k++; }
				ruta[k] = '\0';
				rutas[*contador_rutas] = ruta;
				(*contador_rutas)++;
			}
			delete estado;
			continue;
		}

		for (int i = 0; i < cantidad_padres; ++i) {
			EstadoDFS* nuevo = new EstadoDFS;
			nuevo->id = padres[i];
			nuevo->profundidad = estado->profundidad + 1;
			for (int j = 0; j <= estado->profundidad; ++j) {
				nuevo->camino[j] = estado->camino[j];
			}
			nuevo->camino[nuevo->profundidad] = padres[i];
			Nodo<EstadoDFS*>* nodo_nuevo = new Nodo<EstadoDFS*>(nuevo);
			pila.push(nodo_nuevo);
		}

		delete estado;
	}
}

static int sumar_espacio_bfs(Sistema* sistema, int id_dir) {
	Queue<int>* cola = new Queue<int>();
	Nodo<int>* inicio = new Nodo<int>(id_dir);
	cola->push(inicio);
	int total = 0;

	while (!cola->empty()) {
		Nodo<int>* actual = cola->pop();
		int id = actual->dato;
		delete actual;

		NodoGrafo* nodo = sistema->buscar_nodo_grafo(id);
		if (nodo == 0) { continue; }
		if (!nodo->es_directorio()) {
			NodoArchivo* archivo = (NodoArchivo*)nodo;
			total += archivo->obtener_tamano();
			continue;
		}

		NodoDirectorio* dir = (NodoDirectorio*)nodo;
		int cantidad = dir->cantidad_hijos();
		int* hijos = dir->lista_hijos();
		for (int i = 0; i < cantidad; ++i) {
			Nodo<int>* nuevo = new Nodo<int>(hijos[i]);
			cola->push(nuevo);
		}
	}

	delete cola;
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
	int nuevo_id = contador_id_global++; // Corregido: ID único global en vez de id_padre + cantidad

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
	if (origen == 0) { // Seguridad: verificar pointer nulo antes de copiar
		return 0;
	}
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
	int contador = 0;
	construir_rutas_con_stack(this, d, rutas, &contador, max_rutas);
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
	int total = sumar_espacio_bfs(this, d);
	return total;
}
