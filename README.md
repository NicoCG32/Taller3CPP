# Taller 3: Grafos y Árboles B+

Asignatura: Estructura de Datos – 2° Semestre 2025

Profesor: Bastián Ruiz

Ayudante: Sebastián Pleticosic

Alumno: Pablo Guzmán Vargas – Paralelo C2

Nota: El taller es muy complicado y lo empecé bastante tarde, apunto a cumplir con lo mínimo honestamente.

## Compilación

Para compilar el proyecto, ejecuta:

```bash
g++ -std=c++17 -I include src/App.cpp src/Sistema.cpp src/grafo/NodoGrafo.cpp src/grafo/NodoDirectorio.cpp src/grafo/NodoArchivo.cpp src/bplus/ArbolB.cpp src/bplus/NodoBInterno.cpp src/bplus/NodoBHoja.cpp src/bplus/NodoBPlusBase.cpp -o build/taller3.exe
```

O si tienes configurada la tarea en VS Code:
```bash
Ctrl+Shift+B  # (ejecuta la tarea "Build Taller3CPP")
```

El ejecutable se generará en `build/taller3.exe`

## Generación de Documentación

Para generar la documentación en formato HTML con Doxygen:

```bash
cd docs
doxygen Doxyfile
```

La documentación se generará en `docs/html/`. Abre `docs/html/index.html` en tu navegador para visualizar la documentación completa de clases, métodos y funciones.