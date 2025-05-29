// Archivo: src/Acceso.cpp
#include "../include/Acceso.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

// Constructor: inicializa lista vacía
ListaAccesos::ListaAccesos() : cabeza(nullptr), cola(nullptr), cantidad(0) {}

// Destructor: libera todos los nodos
ListaAccesos::~ListaAccesos() {
    while (cabeza) {
        Acceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    cola = nullptr;
}

// ✅ Registra un acceso al inicio de la lista (LIFO)
void ListaAccesos::registrarAcceso() {
    time_t ahora = time(0);
    string fechaHora = ctime(&ahora);
    fechaHora.pop_back(); // quitar salto de línea

    Acceso* nuevo = new Acceso(fechaHora);
    nuevo->siguiente = cabeza;
    nuevo->anterior = nullptr;

    if (cabeza != nullptr)
        cabeza->anterior = nuevo;
    else
        cola = nuevo; // si la lista estaba vacía

    cabeza = nuevo;
    cantidad++;
}

// ✅ Muestra todos los accesos desde cabeza hasta cola
void ListaAccesos::mostrarAccesos() const {
    Acceso* actual = cabeza;
    int i = 1;
    while (actual) {
        cout << "(" << i << ") " << actual->fechaHora << endl;
        actual = actual->siguiente;
        ++i;
    }
}

// ✅ Elimina los primeros n accesos desde cabeza y los guarda en log
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

// ✅ Devuelve la cantidad de accesos registrados
int ListaAccesos::contarAccesos() const {
    return cantidad;
}

// ✅ Devuelve el acceso más reciente (cabeza de la lista)
string ListaAccesos::getUltimoAcceso() const {
    return cabeza ? cabeza->fechaHora : "(Sin registros)";
}

// ✅ Busca un acceso por posición desde cabeza (1-based index)
string ListaAccesos::buscarPorPosicion(int pos) const {
    if (pos <= 0 || pos > cantidad) return "(Posición inválida)";
    Acceso* actual = cabeza;
    for (int i = 1; i < pos; ++i) {
        actual = actual->siguiente;
    }
    return actual->fechaHora;
}
