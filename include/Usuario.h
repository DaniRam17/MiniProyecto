// Archivo: include/Usuario.h
// -------------------------------------------------------------
// ESTRUCTURA DE DATOS: Clase Usuario con lista de accesos
// Integra información personal y una lista enlazada de accesos
// Cada usuario gestiona su propio historial con ListaAccesos
// -------------------------------------------------------------
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Acceso.h"
using namespace std;

// ✅ Clase Usuario que incluye lista doblemente enlazada de accesos
class Usuario {
private:
    int id;
    string nombre;
    string correo;
    ListaAccesos accesos; // ✅ Lista para guardar los accesos de este usuario

public:
    Usuario();
    Usuario(int, string, string);
    ~Usuario();

    // ✅ Operaciones sobre accesos
    void registrarAcceso();
    void mostrarAccesos() const;
    void eliminarAccesos(int n);
    string buscarAcceso(int pos) const;

    // ✅ Getters principales
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCorreo() const { return correo; }

    // ✅ Acceso a la cabeza de la lista de accesos
    Acceso* getListaAccesos() const { return accesos.getCabeza(); }

    // ✅ Obtener último acceso (usado en Archivo.cpp para guardar)
    string getUltimoAcceso() const { return accesos.getUltimoAcceso(); }
};

#endif
