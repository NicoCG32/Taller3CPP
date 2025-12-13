#pragma once

#include "Sistema.h"

/**
 * Aplicación interactiva del sistema de archivos.
 * @pre Ninguna.
 * @post Proporciona interfaz de usuario para manipular archivos y directorios.
 * @author Pablo Guzmán
 */

/**
 * Solicita al usuario crear un subdirectorio dentro de un padre.
 * @pre Ninguna.
 * @post Si el padre existe, se crea un nuevo directorio.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_crear_subdirectorio(Sistema& sistema);

/**
 * Solicita al usuario insertar un archivo en un directorio.
 * @pre Ninguna.
 * @post Si el padre existe, se crea un nuevo archivo.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_insertar_archivo(Sistema& sistema);

/**
 * Busca un nodo por identificador e informa su tipo.
 * @pre Ninguna.
 * @post Se busca y reporta si existe y es archivo o directorio.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_buscar_nodo(Sistema& sistema);

/**
 * Solicita eliminar un archivo de su directorio padre.
 * @pre Ninguna.
 * @post Si ambos existen, se elimina el archivo.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_eliminar_archivo(Sistema& sistema);

/**
 * Lista todos los hijos de un directorio.
 * @pre Ninguna.
 * @post Se muestran los ids de todos los archivos y subdirectorios.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_listar_contenido(Sistema& sistema);

/**
 * Obtiene todas las rutas desde raíz a un archivo (DFS iterativo).
 * @pre Ninguna.
 * @post Se muestran todas las rutas completas separadas por '/'.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_obtener_rutas(Sistema& sistema);

/**
 * Calcula y muestra el espacio total ocupado en un directorio (BFS).
 * @pre Ninguna.
 * @post Se suma recursivamente todo el contenido del directorio.
 * @param sistema Referencia al sistema de archivos.
 * @throws No lanza.
 */
void opcion_calcular_espacio(Sistema& sistema);

/**
 * Punto de entrada de la aplicación.
 * @pre Ninguna.
 * @post Se ejecuta el menú interactivo del sistema de archivos.
 * @return 0 al salir normalmente.
 * @throws No lanza.
 */
int main();
