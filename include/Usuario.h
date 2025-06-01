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


class Usuario {
private:
    int id;
    string nombre;
    string correo;
    ListaAccesos accesos; 

public:
    Usuario();
    Usuario(int, string, string);
    ~Usuario();


    void registrarAcceso();
    void mostrarAccesos() const;
    void eliminarAccesos(int n);
    string buscarAcceso(int pos) const;


    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCorreo() const { return correo; }

    Acceso* getListaAccesos() const { return accesos.getCabeza(); }


    string getUltimoAcceso() const { return accesos.getUltimoAcceso(); }
};

#endif
