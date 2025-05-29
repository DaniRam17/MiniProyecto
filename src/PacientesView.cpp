// Archivo: src/PacientesView.cpp
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace sf;
using namespace std;

// Estructura de paciente según el archivo binario
struct Paciente {
    char nombre[30];
    int edad;
    int codigoPaciente;
    char vacuna[30];
    char fabricante[30];
    int codigoRegistro;
    char fecha[11];
};

// Muestra gráficamente la lista de pacientes registrados en pacientes.dat
void mostrarVistaPacientes(Font& fuente) {
    RenderWindow ventana(VideoMode(800, 600), "Listado de Pacientes", Style::Close);

    vector<string> lineas;
    ifstream archivo("data/pacientes.dat", ios::binary);
    if (!archivo) {
        lineas.push_back("Error: No se pudo abrir pacientes.dat");
    } else {
        Paciente p;
        while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Paciente))) {
            if (p.codigoPaciente != 9999) {
                stringstream ss;
                ss << "Nombre: " << p.nombre
                   << " | Edad: " << p.edad
                   << " | Codigo: " << p.codigoPaciente
                   << " | Vacuna: " << p.vacuna
                   << " | Fabricante: " << p.fabricante
                   << " | Fecha: " << p.fecha;
                lineas.push_back(ss.str());
            }
        }
        archivo.close();
    }

    Text titulo("Listado de Pacientes Registrados", fuente, 22);
    titulo.setFillColor(Color(20, 20, 80));
    titulo.setPosition(180, 15);

    Text texto("", fuente, 16);
    texto.setFillColor(Color::Black);

    RectangleShape fondo;
    fondo.setSize(Vector2f(760, 500));
    fondo.setPosition(20, 60);
    fondo.setFillColor(Color(250, 250, 250));
    fondo.setOutlineColor(Color(200, 200, 200));
    fondo.setOutlineThickness(1);

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed)
                ventana.close();
        }

        ventana.clear(Color(235, 235, 235));
        ventana.draw(titulo);
        ventana.draw(fondo);

        float y = 70;
        for (size_t i = 0; i < lineas.size(); ++i) {
            texto.setString(lineas[i]);
            texto.setPosition(30, y);
            y += 25;
            if (y > 550) break;
            ventana.draw(texto);
        }

        ventana.display();
    }
}
