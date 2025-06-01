// Archivo: include/HashTable.h
// -------------------------------------------------------------
// ESTRUCTURA DE DATOS: Tabla Hash
// Propósito: búsqueda eficiente de usuarios por ID
// Usa una función hash personalizada y controla colisiones
// -------------------------------------------------------------
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Usuario.h"
#include <vector>
#include <string>
#include <list> 
#include <SFML/Graphics.hpp>

#define TAMANIO_TABLA 100

class HashTable {
private:
    Usuario* tabla[TAMANIO_TABLA];
    std::list<Usuario*> historialInsercion; 

    // Función hash con sondeo cuadrático
    int hashFunction(int id, int intento = 0) const {
        const unsigned int A = 2654435761;
        int hashBase = (id * A) % TAMANIO_TABLA;
        return (hashBase + intento * intento) % TAMANIO_TABLA;
    }

public:
    HashTable();


    bool insertarUsuario(Usuario* usuario);
    Usuario* buscarUsuario(int id);
    bool eliminarUsuarioPorId(int id);
    bool eliminarUsuarioPorPosicion(int pos);
    void mostrarUsuarios();

  
    Usuario* buscarUsuarioPorPosicion(int posicion);

    std::vector<std::pair<int, std::string>> obtenerAccesosVisuales(int id);


    std::vector<std::string> obtenerUsuariosComoLista() const;


    void limpiarTabla();
};

#endif