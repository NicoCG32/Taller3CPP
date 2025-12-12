#include <iostream>
#include "Sistema.h"
#include "auxiliar/Stack.h"
#include "auxiliar/Queue.h"
#include "auxiliar/Nodo.h"
#include "bplus/ArbolB.h"
#include "grafo/NodoArchivo.h"
#include "grafo/NodoDirectorio.h"
#include "grafo/NodoGrafo.h"

using namespace std;

int main() {
    Sistema sistema;
    cout << "Sistema de archivos inicializado" << endl;

    NodoDirectorio* dir = new NodoDirectorio();
    dir->establecer_id(1);

    cout << "Es directorio: " << (dir->es_directorio() ? "si" : "no") << endl;

    cout << "Hijos iniciales: " << dir->cantidad_hijos() << endl;
    dir->agregar_hijo(10);
    dir->agregar_hijo(20);
    cout << "Hijos tras agregar: " << dir->cantidad_hijos() << endl;
    int* hijos = dir->lista_hijos();
    cout << "Listado hijos: " << hijos[0] << ", " << hijos[1] << endl;

    dir->quitar_hijo(10);
    cout << "Hijos tras quitar 10: " << dir->cantidad_hijos() << endl;
    if (dir->cantidad_hijos() > 0) cout << "Primer hijo: " << dir->lista_hijos()[0] << endl;

    delete dir;

    return 0;
}
