#  MiniProyecto: Sistema de Gestión de Accesos con Lista Enlazada y Tabla Hash

##  Descripción

Este sistema permite gestionar los accesos de usuarios a una plataforma mediante una **estructura combinada de lista enlazada y tabla hash**. Desarrollado en **C++** con **interfaz gráfica en SFML**, el programa permite registrar, buscar y eliminar usuarios, así como llevar un control visual e intuitivo de los accesos en tiempo real.

---

##  Tecnologías utilizadas

- C++17
- [SFML 2.6.1](https://www.sfml-dev.org/)
- MinGW + Visual Studio Code
- Archivos binarios y de texto para persistencia:
  - `usuarios.dat` (usuarios registrados)
  - `accesos_eliminados.log` (registro de accesos eliminados)
  - `historial_accesos.txt` (registro histórico completo de accesos)

---

##  Funcionalidades principales

- Guardar usuarios (ID, nombre, correo) con su último acceso.
- Validar existencia de usuarios mediante una **función hash personalizada**.
- Implementación de lista doblemente enlazada (TDA) para almacenar accesos por usuario.
- Registro y eliminación de accesos de forma individual o en lote.
- Eliminación de usuarios por **ID** o por **posición en la lista**.
- Visualización gráfica de accesos y usuarios usando nodos enlazados con **scroll dinámico** y botones intuitivos `<` `>`.
- Interfaz gráfica dividida por secciones: ingreso de datos, acciones disponibles y mensajes del sistema.
- Guardado automático de accesos en archivo histórico (`historial_accesos.txt`).

---

##  Estructura del proyecto



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

---

##  Compilación

###  Requisitos:

- Tener instalado **MinGW** o cualquier compilador compatible con `g++` y soporte para C++17.
- Tener descargada y correctamente configurada la librería [SFML 2.6.1](https://www.sfml-dev.org/download.php).
- Asegúrate de que las rutas de los archivos `.h` y `.lib` estén correctamente incluidas.

###  Archivos esenciales que deben estar presentes:

| Tipo              | Archivos clave                                                        |
|-------------------|------------------------------------------------------------------------|
| Ejecutable        | `main.cpp`                                                             |
| Interfaz gráfica  | `GestionAccesosView.cpp/h`, `InputBox.cpp/h`, `Menu.cpp/h`            |
| Lógica            | `Usuario.cpp/h`, `Acceso.cpp/h`, `HashTable.cpp/h`                    |
| Persistencia      | `Archivo.cpp/h`                                                       |
| Visualización     | `ListVisualizer.cpp/h`, `UsuarioListView.cpp/h`                       |
| Recursos          | `assets/OpenSans.ttf`                                                 |
| Datos             | `data/usuarios.dat`, `data/accesos_eliminados.log`                   |

> Si algún archivo está ausente o con nombre incorrecto, la compilación fallará.

---

###  Comando de compilación:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -IC:/Librerias/SFML-2.6.1/include -LC:/Librerias/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -o bin/MiniProyecto.exe

---

##  Configuración de entorno y rutas de compilación

El funcionamiento correcto del proyecto depende de que la librería **SFML 2.6.1** esté instalada correctamente y enlazada con Visual Studio Code.

###  Archivos clave para compilar correctamente en VSCode:

1. `.vscode/tasks.json` → Define el comando de compilación con las rutas de `SFML`.
2. `.vscode/launch.json` → Permite ejecutar el ejecutable desde el botón de play ▶️.
3. `.vscode/c_cpp_properties.json` → Contiene las rutas para que el IntelliSense de VSCode funcione correctamente.

### ⚠️ ¡IMPORTANTE!

Si cambias la ubicación del proyecto (por ejemplo, `C:\MiniProyecto\` o `D:\Proyectos\Accesos`), **debes actualizar las rutas** en los siguientes campos:

```jsonc
// Dentro de tasks.json
"-IC:/Librerias/SFML-2.6.1/include",
"-LC:/Librerias/SFML-2.6.1/lib"

// Dentro de c_cpp_properties.json
"includePath": [
  "C:/Librerias/SFML-2.6.1/include",
  "${workspaceFolder}/include"
],
"libPath": [
  "C:/Librerias/SFML-2.6.1/lib"
]



Créditos y referencias
SFML Documentation: https://www.sfml-dev.org/documentation/2.6.1/

C++ Reference: https://cplusplus.com/doc/tutorial/

GeeksForGeeks Data Structures: https://geeksforgeeks.org/data-structures/

Douglas- 32151059
Josue -32151059