// Archivo: include/Acceso.h
// -------------------------------------------------------------
// ESTRUCTURA DE DATOS: Lista doblemente enlazada (tipo pila - LIFO)
// Propósito: almacenar la fecha y hora de los accesos del usuario
// Cada nodo representa un acceso registrado en el sistema.
// -------------------------------------------------------------

#ifndef ACCESO_H
#define ACCESO_H

#include <string>
using namespace std;


struct Acceso {
    string fechaHora;
    Acceso* siguiente;
    Acceso* anterior;

    Acceso(string fechaHora)
        : fechaHora(fechaHora), siguiente(nullptr), anterior(nullptr) {}
};


class ListaAccesos {
private:
    Acceso* cabeza;
    Acceso* cola;
    int cantidad;

public:
    ListaAccesos();
    ~ListaAccesos();

    void registrarAcceso();               // Inserta al inicio (LIFO)
    void eliminarAccesos(int n);          // Elimina n accesos desde cabeza
    void mostrarAccesos() const;          // Muestra de cabeza a cola
    int contarAccesos() const;            // Total de accesos
    string getUltimoAcceso() const;       // Acceso en cabeza
    string buscarPorPosicion(int pos) const; // Buscar por posición (desde cabeza)


    Acceso* getCabeza() const { return cabeza; }
};

#endif
