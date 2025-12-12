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

    NodoDirectorio* directorio_raiz = new NodoDirectorio();
    directorio_raiz->establecer_id(100);
    NodoArchivo* archivo1 = new NodoArchivo(1024, 1);
    archivo1->establecer_id(10);
    NodoArchivo* archivo2 = new NodoArchivo(2048, 1);
    archivo2->establecer_id(20);

    sistema.insertar_nodo_grafo(directorio_raiz->obtener_id(), directorio_raiz);
    sistema.insertar_nodo_grafo(archivo1->obtener_id(), archivo1);
    sistema.insertar_nodo_grafo(archivo2->obtener_id(), archivo2);

    cout << "Buscar 10 via Sistema: " << (sistema.buscar_nodo_grafo(10) != nullptr ? "ok" : "no") << endl;
    cout << "Buscar 99 via Sistema: " << (sistema.buscar_nodo_grafo(99) != nullptr ? "ok" : "no") << endl;

    sistema.crear_nodo(100);
    NodoGrafo* padre = sistema.buscar_nodo_grafo(100);
    if (padre != 0) {
        NodoDirectorio* dir_padre = (NodoDirectorio*)padre;
        cout << "Hijos tras crear_nodo: " << dir_padre->cantidad_hijos() << endl;
        int* hijos = dir_padre->lista_hijos();
        int nuevo_id = hijos[dir_padre->cantidad_hijos() - 1];
        cout << "Buscar nuevo hijo via Sistema: " << (sistema.buscar_nodo_grafo(nuevo_id) != nullptr ? "ok" : "no") << endl;
    }

    delete directorio_raiz;
    delete archivo1;
    delete archivo2;

    return 0;
}
