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

void opcion_crear_subdirectorio(Sistema& sistema) {
    cout << "ID del directorio padre: ";
    int id_padre;
    if (!(cin >> id_padre)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }
    if (sistema.buscar_nodo_grafo(id_padre) == 0) {
        cout << "Padre no encontrado" << endl;
        return;
    }
    sistema.crear_nodo(id_padre);
    NodoGrafo* p = sistema.buscar_nodo_grafo(id_padre);
    if (p != 0) {
        NodoDirectorio* d = (NodoDirectorio*)p;
        cout << "Subdirectorios ahora: " << d->cantidad_hijos() << endl;
    }
}

void opcion_insertar_archivo(Sistema& sistema) {

    cout << "ID del directorio padre: ";
    int id_padre;
    if (!(cin >> id_padre)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }

    NodoGrafo* p = sistema.buscar_nodo_grafo(id_padre);
    if (p == 0) {
        cout << "Padre no encontrado" << endl;
        return;
    }

    cout << "ID del archivo: ";
    int id_archivo;
    if (!(cin >> id_archivo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }

    cout << "Tamano del archivo: ";
    int tamano;
    if (!(cin >> tamano)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }

    cout << "Tipo del archivo (numero): ";
    int tipo;
    if (!(cin >> tipo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }

    NodoArchivo* arch = new NodoArchivo(tamano, tipo);
    arch->establecer_id(id_archivo);
    sistema.insertar_nodo_grafo(id_archivo, arch);

    ((NodoDirectorio*)p)->agregar_hijo(id_archivo);
    cout << "Archivo insertado" << endl;
}

void opcion_buscar_nodo(Sistema& sistema) {
    cout << "ID a buscar: ";
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }
    
    NodoGrafo* n = sistema.buscar_nodo_grafo(id);
    if (n == 0) {
        cout << "No encontrado" << endl;
    } else {
        bool es_dir = n->es_directorio();
        cout << (es_dir ? "Directorio" : "Archivo") << " encontrado" << endl;
    }
}

void opcion_eliminar_archivo(Sistema& sistema) {

    cout << "ID del directorio padre: ";
    int id_padre;
    if (!(cin >> id_padre)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }

    if (sistema.buscar_nodo_grafo(id_padre) == 0) {
        cout << "Padre no encontrado" << endl;
        return;
    }

    cout << "ID del archivo a eliminar: ";
    int id_archivo;
    if (!(cin >> id_archivo)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida" << endl;
        return;
    }
    
    sistema.eliminar_archivo(id_archivo, id_padre);
    cout << "Eliminar hecho" << endl;
}

void opcion_listar_contenido(Sistema& sistema) {
    cout << "[Pendiente] Listar contenido de directorio" << endl;
}

void opcion_obtener_rutas(Sistema& sistema) {
    cout << "[Pendiente] Obtener rutas completas de archivo" << endl;
}

void opcion_calcular_espacio(Sistema& sistema) {
    cout << "[Pendiente] Calcular espacio ocupado del directorio" << endl;
}

int main() {
    Sistema sistema;
    cout << "Sistema de archivos inicializado" << endl;

    NodoDirectorio* raiz = new NodoDirectorio();
    raiz->establecer_id(100);
    sistema.insertar_nodo_grafo(raiz->obtener_id(), raiz);

    while (true) {
        cout << endl;
        cout << "Menu" << endl;
        cout << "1) Crear subdirectorio" << endl;
        cout << "2) Insertar archivo" << endl;
        cout << "3) Buscar nodo por ID" << endl;
        cout << "4) Eliminar archivo" << endl;
        cout << "5) Listar contenido (pendiente)" << endl;
        cout << "6) Obtener rutas (pendiente)" << endl;
        cout << "7) Calcular espacio (pendiente)" << endl;
        cout << "8) Salir" << endl;
        cout << "Opcion: ";

        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida" << endl;
            continue;
        }

        if (opcion == 1) {
            opcion_crear_subdirectorio(sistema);
        } else if (opcion == 2) {
            opcion_insertar_archivo(sistema);
        } else if (opcion == 3) {
            opcion_buscar_nodo(sistema);
        } else if (opcion == 4) {
            opcion_eliminar_archivo(sistema);
        } else if (opcion == 5) {
            opcion_listar_contenido(sistema);
        } else if (opcion == 6) {
            opcion_obtener_rutas(sistema);
        } else if (opcion == 7) {
            opcion_calcular_espacio(sistema);
        } else if (opcion == 8) {
            break;
        } else {
            cout << "Opcion invalida" << endl;
        }
    }

    return 0;
}
