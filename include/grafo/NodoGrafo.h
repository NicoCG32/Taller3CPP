#pragma once

/**
 * Nodo base del grafo que representa archivos o directorios.
 * @pre Ninguna.
 * @post Gestiona identificador y relaciones con padres.
 * @author Pablo Guzmán
 */
class NodoGrafo {
private:
    int id;
    int* padres;
    int num_padres;

public:
    /**
     * Construye un nodo sin id.
     * @pre Ninguna.
     * @post Inicializa id en 0 y sin padres.
     * @throws No lanza.
     */
    NodoGrafo();

    /**
     * Construye un nodo con id definido.
     * @pre Ninguna.
     * @post Inicializa id y lista de padres vacía.
     * @param _id Identificador del nodo.
     * @throws No lanza.
     */
    explicit NodoGrafo(int _id);

    /**
     * Libera la lista de padres.
     * @pre Ninguna.
     * @post Memoria de padres liberada.
     * @throws No lanza.
     */
    virtual ~NodoGrafo();

    /**
     * Indica si el nodo corresponde a un directorio.
     * @pre Implementado en derivadas.
     * @post No modifica el estado.
     * @return true si es directorio.
     * @throws No lanza.
     */
    virtual bool es_directorio() = 0;

    /**
     * Obtiene el identificador del nodo.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Identificador actual.
     * @throws No lanza.
     */
    int obtener_id() const;

    /**
     * Cambia el identificador del nodo.
     * @pre Ninguna.
     * @post Actualiza el id almacenado.
     * @param nuevo_id Valor a asignar.
     * @throws No lanza.
     */
    void establecer_id(int nuevo_id);

    /**
     * Devuelve la lista de padres.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Arreglo de ids de padres o 0 si no hay.
     * @throws No lanza.
     */
    int* lista_padres();

    /**
     * Cantidad de padres registrados.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Número de padres.
     * @throws No lanza.
     */
    int cantidad_padres() const;
    
    /**
     * Agrega un padre al nodo.
     * @pre Ninguna.
     * @post El id se agrega al final de la lista de padres.
     * @param id_padre Identificador del padre.
     * @throws No lanza.
     */
    void agregar_padre(int id_padre);

    /**
     * Quita un padre específico.
     * @pre Ninguna.
     * @post La lista de padres se actualiza sin el id indicado.
     * @param id_padre Identificador a remover.
     * @throws No lanza.
     */
    void quitar_padre(int id_padre);
};
