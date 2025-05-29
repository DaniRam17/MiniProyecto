// Archivo: src/HashTable.cpp
// -------------------------------------------------------------
// ESTRUCTURA DE DATOS: Tabla Hash
// Propósito: búsqueda eficiente de usuarios por ID
// Usa una función hash personalizada y controla colisiones
// -------------------------------------------------------------
// Archivo: src/HashTable.cpp
// -------------------------------------------------------------
// IMPLEMENTACIÓN: Tabla Hash para gestión de usuarios
// -------------------------------------------------------------

#include "../include/HashTable.h"
#include "../include/Archivo.h"
#include "../include/Usuario.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < TAMANIO_TABLA; ++i) {
        tabla[i] = nullptr;
    }
    historialInsercion.clear(); // ✅ Se inicializa la lista de inserción
}

// ✅ Inserta un usuario si no hay colisión y mantiene orden de inserción
bool HashTable::insertarUsuario(Usuario* usuario) {
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(usuario->getId(), intento);
        if (tabla[pos] == nullptr) {
            tabla[pos] = usuario;
            historialInsercion.push_back(usuario); // ✅ Mantener orden
            Archivo::guardarUsuario(*usuario, "data/usuarios.dat");
            return true;
        } else if (tabla[pos]->getId() == usuario->getId()) {
            return false; // ID duplicado
        }
        intento++;
    }
    return false;
}

// ✅ Devuelve un puntero al usuario si existe
Usuario* HashTable::buscarUsuario(int id) {
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(id, intento);
        if (tabla[pos] == nullptr) return nullptr;
        if (tabla[pos]->getId() == id) return tabla[pos];
        intento++;
    }
    return nullptr;
}

// ✅ NUEVA: Buscar usuario por posición de inserción (1-indexado)
Usuario* HashTable::buscarUsuarioPorPosicion(int posicion) {
    if (posicion < 1 || posicion > (int)historialInsercion.size()) {
        return nullptr; // Posición inválida
    }
    
    auto it = historialInsercion.begin();
    advance(it, posicion - 1); // Convertir de 1-indexado a 0-indexado
    return *it;
}

// ✅ Elimina usuario por ID y lo remueve del historial también
bool HashTable::eliminarUsuarioPorId(int id) {
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(id, intento);
        if (tabla[pos] == nullptr) return false;
        if (tabla[pos]->getId() == id) {
            // ✅ Remover del historial
            historialInsercion.remove(tabla[pos]);
            delete tabla[pos];
            tabla[pos] = nullptr;
            return true;
        }
        intento++;
    }
    return false;
}

// ✅ CORREGIDA: Elimina usuario por posición de inserción (1-indexado)
bool HashTable::eliminarUsuarioPorPosicion(int posicion) {
    if (posicion < 1 || posicion > (int)historialInsercion.size()) {
        return false; // Posición inválida
    }
    
    // Obtener el usuario en esa posición
    auto it = historialInsercion.begin();
    advance(it, posicion - 1); // Convertir de 1-indexado a 0-indexado
    Usuario* usuarioAEliminar = *it;
    
    // Buscar y eliminar de la tabla hash
    int id = usuarioAEliminar->getId();
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(id, intento);
        if (tabla[pos] == usuarioAEliminar) {
            tabla[pos] = nullptr;
            break;
        }
        intento++;
    }
    
    // Eliminar del historial
    historialInsercion.erase(it);
    delete usuarioAEliminar;
    return true;
}

// ✅ Muestra todos los usuarios cargados en consola
void HashTable::mostrarUsuarios() {
    cout << "\nUsuarios registrados en la tabla hash:\n";
    for (Usuario* u : historialInsercion) {
        cout << "ID=" << u->getId()
             << ", Nombre=" << u->getNombre()
             << ", Correo=" << u->getCorreo() << endl;
    }
}

// ✅ Visualiza accesos del usuario como pares {posición, fecha}
vector<pair<int, string>> HashTable::obtenerAccesosVisuales(int id) {
    vector<pair<int, string>> resultado;
    Usuario* usuario = buscarUsuario(id);
    if (usuario) {
        Acceso* actual = usuario->getListaAccesos();
        int index = 1;
        while (actual) {
            resultado.push_back({index++, actual->fechaHora});
            actual = actual->siguiente;
        }
    }
    return resultado;
}

// ✅ Devuelve los nombres en orden de inserción
vector<string> HashTable::obtenerUsuariosComoLista() const {
    vector<string> lista;
    for (Usuario* u : historialInsercion) {
        lista.push_back(u->getNombre());
    }
    return lista;
}

// ✅ Limpia todos los usuarios
void HashTable::limpiarTabla() {
    for (int i = 0; i < TAMANIO_TABLA; ++i) {
        if (tabla[i] != nullptr) {
            delete tabla[i];
            tabla[i] = nullptr;
        }
    }
    historialInsercion.clear();
}