// Archivo: src/main.cpp
// -------------------------------------------------------------
// PUNTO DE ENTRADA PRINCIPAL DEL SISTEMA
// Carga usuarios desde archivo, lanza menú e interfaz gráfica
// -------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../include/HashTable.h"
#include "../include/GestionAccesosView.h"
#include "../include/PacientesView.h"
#include "../include/Menu.h"
#include "../include/Archivo.h"

using namespace std;

// ✅ Carga fuente con ruta flexible
sf::Font cargarFuente() {
    sf::Font fuente;
    vector<string> rutas = {
        "assets/OpenSans.ttf",
        "assets/SourceCodePro-Bold.ttf",
        "C:/MiniProyecto/assets/SourceCodePro-Bold.ttf"
    };

    for (const auto& ruta : rutas) {
        if (filesystem::exists(ruta) && fuente.loadFromFile(ruta)) {
            cout << "Fuente cargada: " << ruta << endl;
            return fuente;
        }
    }

    cerr << "⚠️ Advertencia: No se pudo cargar una fuente personalizada.\n";
    return fuente;
}

int main() {
    sf::Font fuente = cargarFuente();

    if (!fuente.getInfo().family.empty()) {
        HashTable tabla;

        // ✅ Cargar usuarios desde archivo respetando orden de inserción
        Archivo::cargarUsuarios(tabla, "data/usuarios.dat");

        while (true) {
            int opcion = mostrarMenu(); // menú principal
            if (opcion == 1) {
                mostrarVistaGestionAccesos(fuente, tabla);
            } else if (opcion == 2) {
                mostrarVistaPacientes(fuente);
            } else {
                break;
            }
        }
    } else {
        cerr << "No se pudo cargar fuente válida. El sistema no puede continuar.\n";
    }

    return 0;
}
