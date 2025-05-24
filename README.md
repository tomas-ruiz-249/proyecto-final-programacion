# Proyecto final Programación de Computadores 2024-2

Juego shooter inspirado en DOOM en c++.

![image](https://github.com/user-attachments/assets/142f8142-31a0-45b1-bb0c-bbcc9336ddfb)

## Descripción

El juego es shooter implementando usando programación orientada objetos y usando el algoritmo de raycasting para renderizar un mundo 3D basandose en un mundo cuadriculado en 2D. El proyecto también incluye un [editor de niveles](https://github.com/tomas-ruiz-249/editor-de-niveles) en el cual se pueden crear niveles y añadirlos facilmente al juego.
![image](https://github.com/user-attachments/assets/a7fb0964-b612-4d15-ac7f-1de2a3c3a10f)


## Guía de instalación

### Requerimientos

* Cmake
* Compilador de C++

### Instalando

* [Instalar CMake](https://cmake.org/download/)
* Instalar un compilador de C++
  #### Windows:
  * [MSVC](https://visualstudio.microsoft.com/downloads/)
  * [G++ (via MSYS2)](https://www.msys2.org/)
  #### Linux:
    Distribuciones basadas en Ubuntu:
    ```
    sudo apt-get update
    sudo apt-get install g++
    ```
    Distribuciones basadas en Arch:
    ```
    pacman -S mingw-w64-x86_64-gcc
    ```
* Clonar el repositorio
  Desde CMD (Windows) o Bash(Linux)
  ```
  git clone https://github.com/tomas-ruiz-249/proyecto-final-programacion.git
  cd proyecto-final-programacion
  ```
* Entrar al directorio build
  ```
  cd build
  ```
* Configurar CMake y compilar
  ```
  cmake ..
  cmake --build .
  ```

### Ejecutar el programa

* Desde build
```
cd ../
```
  Windows
  ```
  ProyectoFinalProgramacion.exe
  ```
  Linux
  ```
  ./ProyectoFinalProgramacion
  ```

## Autores

* [Tomás Andrés Ruíz Correa](https://github.com/tomas-ruiz-249)
* [Jaime Antonio Gamba Smith](https://github.com/Sindatos)
* [Juan Felipe Poveda Jimenez](https://github.com/FelipePoveda9)
* [Juan Jose Obando Ruíz](https://github.com/DonJuan213)



## Anexos
* [Editor de niveles](https://github.com/tomas-ruiz-249/editor-de-niveles)
* [Documentación del juego](https://tomas-ruiz-249.github.io/proyecto-final-programacion/)
