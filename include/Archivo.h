// Archivo: include/Archivo.h
// -------------------------------------------------------------
// GESTIÓN DE ARCHIVOS BINARIOS: Guardado y lectura de usuarios
// Permite persistencia de datos en 'usuarios.dat'
// Se usa para serializar y reconstruir objetos Usuario
// -------------------------------------------------------------

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <fstream>
#include <iostream>
#include "Usuario.h"
#include "HashTable.h"
using namespace std;

class Archivo {
public:
   
    static void guardarUsuario(const Usuario& usuario, const string& nombreArchivo);

  
    static void cargarUsuarios(HashTable& tabla, const string& nombreArchivo);
    static void guardarAccesos(const Usuario& usuario, const std::string& nombreArchivo);


};

#endif
