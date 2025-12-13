@echo off
echo Compilando Taller3CPP...
g++ -std=c++17 -I include src/App.cpp src/Sistema.cpp src/grafo/NodoGrafo.cpp src/grafo/NodoDirectorio.cpp src/grafo/NodoArchivo.cpp src/bplus/ArbolB.cpp src/bplus/NodoBInterno.cpp src/bplus/NodoBHoja.cpp src/bplus/NodoBPlusBase.cpp -o build/taller3.exe

if %errorlevel% neq 0 (
    echo.
    echo Error en la compilacion!
    pause
    exit /b %errorlevel%
)

echo Compilacion exitosa!
echo.
echo Ejecutando programa...
echo ==========================================
build\taller3.exe
