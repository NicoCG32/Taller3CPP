#pragma once

#include "grafo/NodoGrafo.h"
#include "grafo/NodoDirectorio.h"
#include "grafo/NodoArchivo.h"
#include "bplus/ArbolB.h"
#include "auxiliar/Stack.h"
#include "auxiliar/Queue.h"

class Sistema {
public:
	void insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo);
	NodoGrafo* buscar_nodo_grafo(int clave);
	void crear_nodo(int id_padre);
	void eliminar_archivo(int id_archivo, int id_directorio_padre);
	int* listar_contenido(int id_directorio);
	char** obtener_rutas_completas(int id_archivo);
	int calcular_espacio_ocupado(int id_directorio);
};
