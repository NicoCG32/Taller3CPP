#include "bplus/NodoBHoja.h"

NodoBHoja::NodoBHoja(int _orden) : NodoBPlusBase(_orden, true), datos(0), siguiente_hoja(0) {
	if (_orden > 0) datos = new NodoGrafo*[_orden];
	for (int i = 0; i < _orden; ++i) datos[i] = 0;
}

NodoBHoja::~NodoBHoja() { delete[] datos; }

void NodoBHoja::establecer_dato(int idx, NodoGrafo* g) {
	if (idx >= 0 && idx < obtener_orden()) datos[idx] = g;
}

NodoGrafo* NodoBHoja::obtener_dato(int idx) const {
	if (idx >= 0 && idx < obtener_orden()) return datos[idx];
	return 0;
}

NodoBHoja* NodoBHoja::obtener_siguiente() const { return siguiente_hoja; }

void NodoBHoja::establecer_siguiente(NodoBHoja* s) { siguiente_hoja = s; }
