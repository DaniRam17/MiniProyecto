// Archivo: src/Usuario.cpp
// -------------------------------------------------------------
// IMPLEMENTACIÓN: Métodos de la clase Usuario
// Integra lista enlazada de accesos para historial
// -------------------------------------------------------------

#include "../include/Usuario.h"
#include <iostream>
using namespace std;


Usuario::Usuario() : id(0), nombre(""), correo("") {}


Usuario::Usuario(int i, string n, string c) : id(i), nombre(n), correo(c) {
    registrarAcceso(); 
}


Usuario::~Usuario() {
   
}


void Usuario::registrarAcceso() {
    accesos.registrarAcceso();
}


void Usuario::mostrarAccesos() const {
    accesos.mostrarAccesos();
}


void Usuario::eliminarAccesos(int n) {
    accesos.eliminarAccesos(n);
}


string Usuario::buscarAcceso(int pos) const {
    return accesos.buscarPorPosicion(pos);
}
