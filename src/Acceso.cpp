// Archivo: src/Acceso.cpp
#include "../include/Acceso.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

ListaAccesos::ListaAccesos() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

ListaAccesos::~ListaAccesos() {
    while (cabeza) {
        Acceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    cola = nullptr;
}

void ListaAccesos::registrarAcceso() {
    time_t ahora = time(0);
    string fechaHora = ctime(&ahora);
    fechaHora.pop_back(); 

    Acceso* nuevo = new Acceso(fechaHora);
    nuevo->siguiente = cabeza;
    nuevo->anterior = nullptr;

    if (cabeza != nullptr)
        cabeza->anterior = nuevo;
    else
        cola = nuevo; 

    cabeza = nuevo;
    cantidad++;
}


void ListaAccesos::mostrarAccesos() const {
    Acceso* actual = cabeza;
    int i = 1;
    while (actual) {
        cout << "(" << i << ") " << actual->fechaHora << endl;
        actual = actual->siguiente;
        ++i;
    }
}


void ListaAccesos::eliminarAccesos(int n) {
    ofstream log("data/accesos_eliminados.log", ios::app);
    while (cabeza && n-- > 0) {
        log << cabeza->fechaHora << endl;
        Acceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        if (cabeza) cabeza->anterior = nullptr;
        else cola = nullptr;
        delete temp;
        cantidad--;
    }
    log.close();
}


int ListaAccesos::contarAccesos() const {
    return cantidad;
}


string ListaAccesos::getUltimoAcceso() const {
    return cabeza ? cabeza->fechaHora : "(Sin registros)";
}


string ListaAccesos::buscarPorPosicion(int pos) const {
    if (pos <= 0 || pos > cantidad) return "(Posición inválida)";
    Acceso* actual = cabeza;
    for (int i = 1; i < pos; ++i) {
        actual = actual->siguiente;
    }
    return actual->fechaHora;
}
