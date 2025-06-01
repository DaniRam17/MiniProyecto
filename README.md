
#  MiniProyecto: Sistema de Gestión de Accesos con Lista Enlazada y Tabla Hash

## Descripción

Este sistema permite gestionar los accesos de usuarios a una plataforma mediante una **estructura combinada de lista enlazada y tabla hash**. Desarrollado en **C++** con **interfaz gráfica en SFML**, el programa permite registrar, buscar y eliminar usuarios, así como llevar un control visual de los accesos.

---

## Tecnologías utilizadas

- C++17
- [SFML 2.6.1](https://www.sfml-dev.org/)
- MinGW / Visual Studio Code
- Archivos binarios (`usuarios.dat`) y logs (`accesos_eliminados.log`)

---

##  Funcionalidades principales

- ✅ Guardar usuarios (ID, nombre, correo) con fecha/hora del último acceso.
- ✅ Validar existencia de usuario usando una **función hash personalizada**.
- ✅ Estructura de accesos tipo **lista doblemente enlazada (tipo pila)**.
- ✅ Registro y eliminación controlada de accesos por usuario.
- ✅ Eliminación de usuarios por ID o posición.
- ✅ Visualización gráfica de accesos y usuarios como nodos conectados.
- ✅ Interfaz gráfica dividida por secciones (entrada, acciones, mensajes).

---

## Estructura del proyecto

MiniProyecto/
├── assets/
│ └── OpenSans.ttf
├── bin/
│ └── MiniProyecto.exe
├── data/
│ ├── usuarios.dat
│ └── accesos_eliminados.log
├── include/
│ ├── Acceso.h
│ ├── Archivo.h
│ ├── HashTable.h
│ ├── InputBox.h
│ ├── Usuario.h
│ ├── GestionAccesosView.h
│ ├── Menu.h
│ └── UsuarioListView.h
├── src/
│ ├── main.cpp
│ ├── Acceso.cpp
│ ├── Archivo.cpp
│ ├── HashTable.cpp
│ ├── InputBox.cpp
│ ├── Usuario.cpp
│ ├── GestionAccesosView.cpp
│ ├── UsuarioListView.cpp
│ ├── ListVisualizer.cpp
│ ├── Menu.cpp
│ └── PacientesView.cpp
└── README.md


---

##  Compilación

### Requisitos:
- Tener instalado `g++` con soporte para C++17
- Tener SFML correctamente configurado

### Comando para compilar:
```bash
g++ -std=c++17 src/*.cpp -Iinclude -IC:/Librerias/SFML-2.6.1/include -LC:/Librerias/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -o bin/MiniProyecto.exe


Cómo usar
Ejecutar MiniProyecto.exe

Usar la interfaz gráfica para:

Registrar un usuario

Registrar accesos

Ver la lista de accesos o usuarios

Eliminar accesos o usuarios

Los datos se guardan automáticamente en archivos binarios para persistencia.

Créditos y referencias
SFML Documentation: https://www.sfml-dev.org/documentation/2.6.1/

C++ Reference: https://cplusplus.com/doc/tutorial/

GeeksForGeeks Data Structures: https://geeksforgeeks.org/data-structures/

Douglas- 32151059
Josue -32151059