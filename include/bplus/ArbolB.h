#pragma once

#include "grafo/NodoGrafo.h"
#include "bplus/NodoBPlusBase.h"
#include "bplus/NodoBInterno.h"
#include "bplus/NodoBHoja.h"

/**
 * Árbol B+ que indexa nodos del grafo por clave numérica.
 * @pre Ninguna.
 * @post Mantiene inserciones, búsquedas y eliminaciones balanceadas.
 * @author Pablo Guzmán
 */
class ArbolB {
private:
    NodoBPlusBase* raiz = 0;
    int orden = 4;

public:
    /**
     * Inserta un nodo asociado a una clave.
     * @pre nodo distinto de nulo.
     * @post La clave queda almacenada en una hoja, dividiendo nodos si es necesario.
     * @param clave Identificador único a indexar.
     * @param nodo Nodo del grafo que se asocia a la clave.
     * @throws No lanza.
     */
    void insertar(int clave, NodoGrafo* nodo);

    /**
     * Busca un nodo por su clave.
     * @pre Ninguna.
     * @post No modifica la estructura.
     * @param clave Identificador buscado.
     * @return Nodo asociado o 0 si no existe.
     * @throws No lanza.
     */
    NodoGrafo* buscar(int clave);

    /**
     * Elimina una clave y su nodo asociado.
     * @pre La clave puede existir o no.
     * @post Si se encuentra, se remueve de la hoja.
     * @param clave Identificador a eliminar.
     * @return true si se eliminó, false si no estaba.
     * @throws No lanza.
     */
    bool eliminar(int clave);

    /**
     * Obtiene el contador de accesos simulados.
     * @pre Ninguna.
     * @post No modifica el árbol.
     * @return Número de accesos acumulados.
     * @throws No lanza.
     */
    int obtener_accesos() const;
};
