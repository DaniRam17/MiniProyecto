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
    historialInsercion.clear(); 
}


bool HashTable::insertarUsuario(Usuario* usuario) {
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(usuario->getId(), intento);
        if (tabla[pos] == nullptr) {
            tabla[pos] = usuario;
            historialInsercion.push_back(usuario); 
            Archivo::guardarUsuario(*usuario, "data/usuarios.dat");
            return true;
        } else if (tabla[pos]->getId() == usuario->getId()) {
            return false; // ID duplicado
        }
        intento++;
    }
    return false;
}


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

Usuario* HashTable::buscarUsuarioPorPosicion(int posicion) {
    if (posicion < 1 || posicion > (int)historialInsercion.size()) {
        return nullptr; 
    }
    
    auto it = historialInsercion.begin();
    advance(it, posicion - 1); 
    return *it;
}


bool HashTable::eliminarUsuarioPorId(int id) {
    int intento = 0;
    while (intento < TAMANIO_TABLA) {
        int pos = hashFunction(id, intento);
        if (tabla[pos] == nullptr) return false;
        if (tabla[pos]->getId() == id) {
          
            historialInsercion.remove(tabla[pos]);
            delete tabla[pos];
            tabla[pos] = nullptr;
            return true;
        }
        intento++;
    }
    return false;
}


bool HashTable::eliminarUsuarioPorPosicion(int posicion) {
    if (posicion < 1 || posicion > (int)historialInsercion.size()) {
        return false; 
    }
    

    auto it = historialInsercion.begin();
    advance(it, posicion - 1); 
    Usuario* usuarioAEliminar = *it;
    
 
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
    
   
    historialInsercion.erase(it);
    delete usuarioAEliminar;
    return true;
}


void HashTable::mostrarUsuarios() {
    cout << "\nUsuarios registrados en la tabla hash:\n";
    for (Usuario* u : historialInsercion) {
        cout << "ID=" << u->getId()
             << ", Nombre=" << u->getNombre()
             << ", Correo=" << u->getCorreo() << endl;
    }
}


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


vector<string> HashTable::obtenerUsuariosComoLista() const {
    vector<string> lista;
    for (Usuario* u : historialInsercion) {
        lista.push_back(u->getNombre());
    }
    return lista;
}


void HashTable::limpiarTabla() {
    for (int i = 0; i < TAMANIO_TABLA; ++i) {
        if (tabla[i] != nullptr) {
            delete tabla[i];
            tabla[i] = nullptr;
        }
    }
    historialInsercion.clear();
}