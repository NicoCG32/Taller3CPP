#pragma once

class NodoGrafo {
private:
    int id;
    int* padres;
    int num_padres;

public:
    NodoGrafo();
    explicit NodoGrafo(int _id);
    virtual ~NodoGrafo();

    virtual bool es_directorio() = 0;

    int obtener_id() const;
    void establecer_id(int nuevo_id);

    int* lista_padres();
    int cantidad_padres() const;
    
    void agregar_padre(int id_padre);

    void quitar_padre(int id_padre);
};
