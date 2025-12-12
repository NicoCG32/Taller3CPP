#include <iostream>
#include "Sistema.h"
#include "auxiliar/Stack.h"
#include "auxiliar/Queue.h"
#include "auxiliar/Nodo.h"
#include "bplus/ArbolB.h"
#include "grafo/NodoArchivo.h"
#include "grafo/NodoDirectorio.h"

int main() {
    Sistema sistema;
    std::cout << "Sistema de archivos inicializado" << std::endl;

    ArbolB arbol;

    NodoDirectorio* directorio_raiz = new NodoDirectorio();
    directorio_raiz->establecer_id(100);

    NodoArchivo* archivo1 = new NodoArchivo(1024, 1);
    archivo1->establecer_id(10);

    NodoArchivo* archivo2 = new NodoArchivo(2048, 1);
    archivo2->establecer_id(20);

    arbol.insertar(directorio_raiz->obtener_id(), directorio_raiz);
    arbol.insertar(archivo1->obtener_id(), archivo1);
    arbol.insertar(archivo2->obtener_id(), archivo2);

    std::cout << "Accesos B+: " << arbol.obtener_accesos() << std::endl;

    std::cout << "Buscar 10: " << (arbol.buscar(10) ? "ok" : "no") << std::endl;
    std::cout << "Buscar 20: " << (arbol.buscar(20) ? "ok" : "no") << std::endl;
    std::cout << "Buscar 99: " << (arbol.buscar(99) ? "ok" : "no") << std::endl;

    std::cout << "Eliminar 10: " << (arbol.eliminar(10) ? "ok" : "no") << std::endl;
    std::cout << "Re-buscar 10: " << (arbol.buscar(10) ? "ok" : "no") << std::endl;
    std::cout << "Accesos B+ totales: " << arbol.obtener_accesos() << std::endl;

    delete directorio_raiz;
    delete archivo1;
    delete archivo2;
    return 0;
}
