#pragma once

class NodoGrafo {
private:
    int id;
    int* padres;
    int num_padres;

public:
    NodoGrafo() : id(-1), padres(0), num_padres(0) {}
    explicit NodoGrafo(int _id) : id(_id), padres(0), num_padres(0) {}
    virtual ~NodoGrafo() {}

    virtual bool es_directorio() = 0;

    int obtener_id() const { return id; }
    void establecer_id(int nuevo_id) { id = nuevo_id; }

    int* lista_padres() { return padres; }
    int cantidad_padres() const { return num_padres; }
    void agregar_padre(int id_padre) {
        int* nuevo = new int[num_padres + 1];
        for (int i = 0; i < num_padres; ++i) nuevo[i] = padres[i];
        nuevo[num_padres] = id_padre;
        delete[] padres;
        padres = nuevo;
        num_padres += 1;
    }
    void quitar_padre(int id_padre) {
        if (num_padres == 0 || !padres) return;
        int nuevo_count = 0;
        for (int i = 0; i < num_padres; ++i) if (padres[i] != id_padre) nuevo_count++;
        int* nuevo = nuevo_count ? new int[nuevo_count] : 0;
        int j = 0;
        for (int i = 0; i < num_padres; ++i) if (padres[i] != id_padre) { nuevo[j++] = padres[i]; }
        delete[] padres;
        padres = nuevo;
        num_padres = nuevo_count;
    }
};
