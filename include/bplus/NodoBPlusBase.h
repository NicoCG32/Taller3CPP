#pragma once

class NodoBPlusBase {
protected:
    int* claves;
    int orden;
    int num_claves;
    bool hoja;

public:
    NodoBPlusBase(int _orden, bool _hoja);
    virtual ~NodoBPlusBase();
    int obtener_orden() const;
    int obtener_num_claves() const;
    bool es_hoja() const;
    int* obtener_claves() const;
    bool insertar_clave(int clave);
    void decrementar_num_claves();
};
