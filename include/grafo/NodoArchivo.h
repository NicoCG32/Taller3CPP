#pragma once
#include "grafo/NodoGrafo.h"

class NodoArchivo : public NodoGrafo {
private:
    int tamano;
    int tipo; // 0: Imagen; 1: Documento; 2: ejecutable; 3: Video; 4: Comprimido

public:
    NodoArchivo() : tamano(0), tipo(0) {}
    explicit NodoArchivo(int size, int type) : tamano(size), tipo(type) {}
    bool es_directorio() { return false; }
    int obtener_tamano() const { return tamano; }
    int obtener_tipo() const { return tipo; }
    void establecer_tamano(int t) { tamano = t; }
    void establecer_tipo(int tp) { tipo = tp; }
};
