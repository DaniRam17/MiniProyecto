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
#include <list> // ✅ Se agregó para manejar el orden de inserción
#include <SFML/Graphics.hpp>

#define TAMANIO_TABLA 100

class HashTable {
private:
    Usuario* tabla[TAMANIO_TABLA];
    std::list<Usuario*> historialInsercion; // ✅ Lista para mantener orden de inserción

    // Función hash con sondeo cuadrático
    int hashFunction(int id, int intento = 0) const {
        const unsigned int A = 2654435761;
        int hashBase = (id * A) % TAMANIO_TABLA;
        return (hashBase + intento * intento) % TAMANIO_TABLA;
    }

public:
    HashTable();

    // Operaciones principales
    bool insertarUsuario(Usuario* usuario);
    Usuario* buscarUsuario(int id);
    bool eliminarUsuarioPorId(int id);
    bool eliminarUsuarioPorPosicion(int pos);
    void mostrarUsuarios();

    // ✅ NUEVA: Buscar usuario por posición de inserción (1-indexado)
    Usuario* buscarUsuarioPorPosicion(int posicion);

    // Accesos por usuario (para dibujar lista enlazada)
    std::vector<std::pair<int, std::string>> obtenerAccesosVisuales(int id);

    // ✅ Visualización en orden de inserción
    std::vector<std::string> obtenerUsuariosComoLista() const;

    // ✅ Nueva función para limpiar historial (por ejemplo, al cargar desde archivo)
    void limpiarTabla();
};

#endif