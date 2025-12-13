#pragma once
#include "grafo/NodoGrafo.h"

/**
 * Nodo especializado del grafo que representa un archivo.
 * @pre Ninguna.
 * @post Mantiene tamaño y tipo de archivo.
 * @author Pablo Guzmán
 */
class NodoArchivo : public NodoGrafo {
private:
    int tamano;
    int tipo; // 0: Imagen; 1: Documento; 2: ejecutable; 3: Video; 4: Comprimido

public:
    /**
     * Construye un archivo con tamaño y tipo por defecto.
     * @pre Ninguna.
     * @post Inicializa tamano=0, tipo=0.
     * @throws No lanza.
     */
    NodoArchivo() : tamano(0), tipo(0) {}

    /**
     * Construye un archivo con tamaño y tipo especificado.
     * @pre Ninguna.
     * @post Inicializa con los valores dados.
     * @param size Tamaño en bytes.
     * @param type Tipo de archivo (0-4).
     * @throws No lanza.
     */
    explicit NodoArchivo(int size, int type) : tamano(size), tipo(type) {}

    /**
     * Indica que este nodo es un archivo.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return false.
     * @throws No lanza.
     */
    bool es_directorio() { return false; }

    /**
     * Obtiene el tamaño del archivo.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Tamaño en bytes.
     * @throws No lanza.
     */
    int obtener_tamano() const { return tamano; }

    /**
     * Obtiene el tipo de archivo.
     * @pre Ninguna.
     * @post No modifica el estado.
     * @return Tipo numérico (0-4).
     * @throws No lanza.
     */
    int obtener_tipo() const { return tipo; }

    /**
     * Establece el tamaño del archivo.
     * @pre Ninguna.
     * @post Actualiza el tamaño.
     * @param t Nuevo tamaño en bytes.
     * @throws No lanza.
     */
    void establecer_tamano(int t) { tamano = t; }

    /**
     * Establece el tipo de archivo.
     * @pre Ninguna.
     * @post Actualiza el tipo.
     * @param tp Nuevo tipo (0-4).
     * @throws No lanza.
     */
    void establecer_tipo(int tp) { tipo = tp; }
};
