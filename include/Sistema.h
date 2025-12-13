#pragma once

#include "grafo/Grafo.h"
#include "grafo/NodoGrafo.h"
#include "grafo/NodoDirectorio.h"
#include "grafo/NodoArchivo.h"
#include "bplus/ArbolB.h"
#include "auxiliar/Stack.h"
#include "auxiliar/Queue.h"

/**
 * Estado de nodo durante búsqueda en profundidad (DFS).
 * @pre Ninguna.
 * @post Almacena información de profundidad y camino recorrido.
 * @author Pablo Guzmán
 */
struct EstadoDFS {
    int id;              /**< Identificador del nodo en la búsqueda. */
    int profundidad;     /**< Nivel de profundidad actual en el árbol. */
    int camino[64];      /**< Array de IDs del camino desde raíz hasta nodo actual. */
};

/**
 * Orquestador del sistema de archivos.
 * @pre Ninguna.
 * @post Maneja todas las operaciones sobre archivos y directorios.
 * @author Pablo Guzmán
 */
class Sistema {
private:
    ArbolB indice_bplus;

public:
    /**
     * Inserta un nodo en el índice B+.
     * @pre nodo_grafo distinto de nulo.
     * @post La clave queda indexada en el árbol.
     * @param clave Identificador único.
     * @param nodo_grafo Nodo a almacenar.
     * @throws No lanza.
     */
    void insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo);

    /**
     * Busca un nodo por identificador.
     * @pre Ninguna.
     * @post No modifica el sistema.
     * @param clave Identificador buscado.
     * @return Nodo encontrado o 0.
     * @throws No lanza.
     */
    NodoGrafo* buscar_nodo_grafo(int clave);

    /**
     * Crea un nuevo subdirectorio dentro de un padre.
     * @pre id_padre existe y es un directorio.
     * @post Se crea un nuevo directorio hijo con ID único global.
     * @param id_padre Identificador del directorio padre.
     * @throws No lanza.
     */
    void crear_nodo(int id_padre);

    /**
     * Elimina un archivo de un directorio.
     * @pre id_archivo existe y es un archivo, id_directorio_padre es su padre.
     * @post El archivo se remueve; si pierde todos sus padres, se borra del índice.
     * @param id_archivo Identificador del archivo a eliminar.
     * @param id_directorio_padre Identificador del directorio padre.
     * @throws No lanza.
     */
    void eliminar_archivo(int id_archivo, int id_directorio_padre);

    /**
     * Lista los hijos de un directorio.
     * @pre id_directorio existe y es un directorio.
     * @post Retorna copia de la lista de hijos.
     * @param id_directorio Identificador del directorio.
     * @return Arreglo dinámico de ids o 0 si está vacío.
     * @throws No lanza.
     */
    int* listar_contenido(int id_directorio);

    /**
     * Obtiene todas las rutas desde raíz hasta un archivo (DFS iterativo).
     * @pre id_archivo existe y es un archivo.
     * @post Retorna arreglo de rutas separadas por '/'.
     * @param id_archivo Identificador del archivo.
     * @return Matriz de cadenas de rutas (terminada en 0) o 0 si sin rutas.
     * @throws No lanza.
     */
    char** obtener_rutas_completas(int id_archivo);

    /**
     * Calcula el espacio total ocupado por un directorio (BFS).
     * @pre id_directorio existe y es un directorio.
     * @post Suma recursivamente los tamaños de archivos.
     * @param id_directorio Identificador del directorio.
     * @return Tamaño total en bytes.
     * @throws No lanza.
     */
    int calcular_espacio_ocupado(int id_directorio);

};
