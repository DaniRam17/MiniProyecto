// Archivo: src/Usuario.cpp
// -------------------------------------------------------------
// IMPLEMENTACIÓN: Métodos de la clase Usuario
// Integra lista enlazada de accesos para historial
// -------------------------------------------------------------

#include "../include/Usuario.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Usuario::Usuario() : id(0), nombre(""), correo("") {}

// Constructor con datos (registra primer acceso)
Usuario::Usuario(int i, string n, string c) : id(i), nombre(n), correo(c) {
    registrarAcceso(); // ✅ Registro automático al crear el usuario
}

// Destructor (automáticamente limpia la lista de accesos)
Usuario::~Usuario() {
    // No requiere liberar explícitamente accesos
}

// ✅ Agrega un nuevo acceso con fecha/hora actual
void Usuario::registrarAcceso() {
    accesos.registrarAcceso();
}

// ✅ Muestra todos los accesos del usuario
void Usuario::mostrarAccesos() const {
    accesos.mostrarAccesos();
}

// ✅ Elimina los primeros 'n' accesos desde cabeza
void Usuario::eliminarAccesos(int n) {
    accesos.eliminarAccesos(n);
}

// ✅ Busca acceso por posición en la lista (1 basado)
string Usuario::buscarAcceso(int pos) const {
    return accesos.buscarPorPosicion(pos);
}
