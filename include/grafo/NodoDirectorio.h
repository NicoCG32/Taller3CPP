#pragma once
#include "grafo/NodoGrafo.h"

/**
 * Nodo especializado del grafo que representa un directorio.
 * @pre Ninguna.
 * @post Mantiene lista de identificadores de hijos.
 * @author Pablo Guzmán
 */
class NodoDirectorio : public NodoGrafo {
    
public:
    /**
     * Indica que este nodo es un directorio.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return true.
     * @throws No lanza.
     */
    bool es_directorio();

    /**
     * Devuelve la lista de hijos.
     * @pre Ninguna.
     * @post No modifica la lista.
     * @return Arreglo de ids de hijos o 0 si está vacío.
     * @throws No lanza.
     */
    int* lista_hijos();

    /**
     * Cantidad de hijos en el directorio.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Número de hijos.
     * @throws No lanza.
     */
    int cantidad_hijos() const;

    /**
     * Agrega un archivo/subdirectorio como hijo.
     * @pre Ninguna.
     * @post El id se añade al final de la lista de hijos.
     * @param id_hijo Identificador del hijo.
     * @throws No lanza.
     */
    void agregar_hijo(int id_hijo);
    
    /**
     * Quita un hijo específico del directorio.
     * @pre Ninguna.
     * @post La lista de hijos se actualiza sin el id indicado.
     * @param id_hijo Identificador a remover.
     * @throws No lanza.
     */
    void quitar_hijo(int id_hijo);

private:
    int* hijos = 0;
    int num_hijos = 0;
};
