// Archivo: src/Archivo.cpp
// -------------------------------------------------------------
// IMPLEMENTACIÓN: Lectura y escritura binaria de usuarios
// Permite guardar campos como ID, nombre, correo y fecha
// Se recuperan desde el archivo y se reconstruyen en memoria
// -------------------------------------------------------------

#include "../include/Archivo.h"
#include <cstring>
using namespace std;

// ✅ Guarda los datos del usuario en el archivo binario (serialización manual)
void Archivo::guardarUsuario(const Usuario& usuario, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary | ios::app);
    if (!archivo) {
        cerr << "Error al abrir archivo para guardar." << endl;
        return;
    }

    int id = usuario.getId();
    string nombre = usuario.getNombre();
    string correo = usuario.getCorreo();
    string fecha = usuario.getUltimoAcceso();

    size_t tamNombre = nombre.size();
    size_t tamCorreo = correo.size();
    size_t tamFecha = fecha.size();

    archivo.write(reinterpret_cast<char*>(&id), sizeof(id));
    archivo.write(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
    archivo.write(nombre.c_str(), tamNombre);
    archivo.write(reinterpret_cast<char*>(&tamCorreo), sizeof(tamCorreo));
    archivo.write(correo.c_str(), tamCorreo);
    archivo.write(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha));
    archivo.write(fecha.c_str(), tamFecha);

    archivo.close();
}

// ✅ Lee los datos del archivo binario y reconstruye objetos Usuario
// Respetando el orden de inserción en HashTable
void Archivo::cargarUsuarios(HashTable& tabla, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo para lectura." << endl;
        return;
    }

    // Limpiar tabla actual para evitar duplicados
    tabla.limpiarTabla();

    while (!archivo.eof()) {
        int id;
        size_t tamNombre, tamCorreo, tamFecha;
        string nombre, correo, fecha;

        archivo.read(reinterpret_cast<char*>(&id), sizeof(id));
        if (archivo.eof()) break;

        archivo.read(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
        nombre.resize(tamNombre);
        archivo.read(&nombre[0], tamNombre);

        archivo.read(reinterpret_cast<char*>(&tamCorreo), sizeof(tamCorreo));
        correo.resize(tamCorreo);
        archivo.read(&correo[0], tamCorreo);

        archivo.read(reinterpret_cast<char*>(&tamFecha), sizeof(tamFecha));
        fecha.resize(tamFecha);
        archivo.read(&fecha[0], tamFecha);

        Usuario* nuevo = new Usuario(id, nombre, correo);
        // Simular fecha recuperada como primer acceso
        // nota: no lo insertamos manualmente para evitar duplicado visual
        tabla.insertarUsuario(nuevo); // ✅ Insertarlo respetando orden
    }

    archivo.close();
}
