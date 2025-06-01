
#ifndef ACCESO_H
#define ACCESO_H

#include <string>


struct Acceso {
    std::string fechaHora;
    Acceso* siguiente;
    Acceso* anterior;

    Acceso(); 
};

class ListaAccesos {
private:
    Acceso* cabeza;
    static const int MAX_ACCESOS = 13;

public:
    ListaAccesos();
    ~ListaAccesos();

    void registrarAcceso();
    void eliminarAccesos(int n);
    void eliminarUltimoAcceso();
    void mostrarAccesos() const;
    int contarAccesos() const;
    std::string getUltimoAcceso() const;
    std::string buscarPorPosicion(int pos) const;
    
    Acceso* getCabeza() const;  // ✅ Nuevo
};

#endif
