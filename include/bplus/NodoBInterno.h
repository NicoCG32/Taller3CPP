#pragma once
#include "bplus/NodoBPlusBase.h"

class NodoBInterno : public NodoBPlusBase {
private:
    NodoBPlusBase** punteros;
public:
    int buscar_siguiente();
};
