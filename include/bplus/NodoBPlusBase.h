#pragma once

/**
 * Nodo base compartido por nodos internos y hojas del B+ tree.
 * @pre Orden mayor que cero.
 * @post Gestiona claves y metadatos comunes.
 * @author Pablo Guzmán
 */
class NodoBPlusBase {
protected:
    int* claves;
    int orden;
    int num_claves;
    bool hoja;

public:
    /**
     * Construye un nodo base.
     * @pre _orden > 0.
     * @post Inicializa arreglo de claves y tipo de nodo.
     * @param _orden Capacidad máxima de claves.
     * @param _hoja Indica si es hoja.
     * @throws No lanza.
     */
    NodoBPlusBase(int _orden, bool _hoja);

    /**
     * Libera memoria de claves.
     * @pre Ninguna.
     * @post Memoria interna liberada.
     * @throws No lanza.
     */
    virtual ~NodoBPlusBase();

    /**
     * Obtiene el orden del nodo.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Valor de orden configurado.
     * @throws No lanza.
     */
    int obtener_orden() const;

    /**
     * Cantidad de claves usadas.
     * @pre Ninguna.
     * @post No modifica el nodo.
     * @return Número de claves actuales.
     * @throws No lanza.
     */
    int obtener_num_claves() const;

    /**
     * Indica si el nodo es hoja.
     * @pre Ninguna.
     * @post No modifica el nodo.
     * @return true si es hoja.
     * @throws No lanza.
     */
    bool es_hoja() const;

    /**
     * Devuelve el arreglo de claves.
     * @pre Ninguna.
     * @post No modifica el nodo.
     * @return Puntero a claves almacenadas.
     * @throws No lanza.
     */
    int* obtener_claves() const;

    /**
     * Inserta una clave manteniendo orden.
     * @pre Existe espacio para la clave.
     * @post La clave se agrega en el arreglo desplazando si es necesario.
     * @param clave Valor a insertar.
     * @return true si se insertó, false si no había espacio.
     * @throws No lanza.
     */
    bool insertar_clave(int clave);

    /**
     * Disminuye el contador de claves.
     * @pre num_claves > 0.
     * @post num_claves se reduce en uno.
     * @throws No lanza.
     */
    void decrementar_num_claves();
};
