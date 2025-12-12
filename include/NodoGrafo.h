#pragma once

class NodoGrafo {
private:
    int id;

public:
    // Indica si el nodo corresponde a un directorio
    bool es_directorio();

    // Retorna un vector (puntero) con los ids de los padres
    int* lista_padres();
};
