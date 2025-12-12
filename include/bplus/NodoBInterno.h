#pragma once
#include "bplus/NodoBPlusBase.h"

class NodoBInterno : public NodoBPlusBase {
private:
    NodoBPlusBase** punteros;
public:
    NodoBInterno(int _orden);
    ~NodoBInterno();
    int buscar_siguiente();
    void establecer_puntero(int idx, NodoBPlusBase* nodo);
    NodoBPlusBase* obtener_puntero(int idx) const;
};
