
#include "../include/Acceso.h"
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;


Acceso::Acceso() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << 1 + ltm->tm_mon << "-"
       << ltm->tm_mday << " "
       << ltm->tm_hour << ":"
       << ltm->tm_min << ":"
       << ltm->tm_sec;
    fechaHora = ss.str();
    siguiente = nullptr;
    anterior = nullptr;
}


ListaAccesos::ListaAccesos() {
    cabeza = nullptr;
}


ListaAccesos::~ListaAccesos() {
    Acceso* actual = cabeza;
    while (actual) {
        Acceso* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaAccesos::registrarAcceso() {
  
    if (contarAccesos() >= MAX_ACCESOS) {
        eliminarUltimoAcceso();
    }

    Acceso* nuevo = new Acceso();
    nuevo->siguiente = cabeza;
    nuevo->anterior = nullptr;

    if (cabeza) {
        cabeza->anterior = nuevo;
    }

    cabeza = nuevo;
}


void ListaAccesos::eliminarAccesos(int n) {
    for (int i = 0; i < n && cabeza; ++i) {
        Acceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        if (cabeza) cabeza->anterior = nullptr;
        delete temp;
    }
}


void ListaAccesos::eliminarUltimoAcceso() {
    if (!cabeza) return;

    Acceso* temp = cabeza;
    while (temp->siguiente) {
        temp = temp->siguiente;
    }

    if (temp->anterior) {
        temp->anterior->siguiente = nullptr;
    } else {
        cabeza = nullptr; // único nodo
    }

    delete temp;
}


int ListaAccesos::contarAccesos() const {
    int contador = 0;
    Acceso* actual = cabeza;
    while (actual) {
        ++contador;
        actual = actual->siguiente;
    }
    return contador;
}


void ListaAccesos::mostrarAccesos() const {
    Acceso* actual = cabeza;
    while (actual) {
        cout << actual->fechaHora << endl;
        actual = actual->siguiente;
    }
}


string ListaAccesos::getUltimoAcceso() const {
    return cabeza ? cabeza->fechaHora : "Sin registros";
}


string ListaAccesos::buscarPorPosicion(int pos) const {
    Acceso* actual = cabeza;
    int contador = 0;
    while (actual && contador < pos) {
        actual = actual->siguiente;
        contador++;
    }
    return actual ? actual->fechaHora : "No existe";
}

Acceso* ListaAccesos::getCabeza() const {
    return cabeza;
}
