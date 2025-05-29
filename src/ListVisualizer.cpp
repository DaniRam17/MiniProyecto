// Archivo: src/ListVisualizer.cpp
#include "../include/ListVisualizer.h"
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;
using namespace sf;

// ✅ Dibuja una lista enlazada visual de accesos
void mostrarListaAccesos(Font& fuente, const vector<pair<int, string>>& accesos) {
    RenderWindow ventana(VideoMode(1200, 200), "Lista de Accesos (Visualizacion)", Style::Titlebar | Style::Close);
    ventana.setFramerateLimit(60);

    while (ventana.isOpen()) {
        Event e;
        while (ventana.pollEvent(e)) {
            if (e.type == Event::Closed)
                ventana.close();
        }

        ventana.clear(Color(30, 30, 30));

        float x = 30;
        float y = 80;
        for (size_t i = 0; i < accesos.size(); ++i) {
            // Dibujar nodo
            RectangleShape nodo(Vector2f(180, 40));
            nodo.setPosition(x, y);
            nodo.setFillColor(Color(50, 150, 250));
            nodo.setOutlineThickness(2);
            nodo.setOutlineColor(Color::White);

            // Texto dentro del nodo
            Text txt(accesos[i].second, fuente, 13);
            txt.setFillColor(Color::White);
            txt.setPosition(x + 8, y + 10);

            ventana.draw(nodo);
            ventana.draw(txt);

            // Flecha al siguiente nodo
            if (i < accesos.size() - 1) {
                Vertex arrow[] = {
                    Vertex(Vector2f(x + 180, y + 20), Color::White),
                    Vertex(Vector2f(x + 200, y + 20), Color::White)
                };
                ventana.draw(arrow, 2, Lines);
            }

            x += 220;
        }

        ventana.display();
    }
}

// ✅ Dibuja una lista visual de usuarios en orden de inserción
void mostrarListaUsuarios(Font& fuente, const vector<string>& usuarios) {
    RenderWindow ventana(VideoMode(1200, 200), "Lista de Usuarios (Visualizacion)", Style::Titlebar | Style::Close);
    ventana.setFramerateLimit(60);

    while (ventana.isOpen()) {
        Event e;
        while (ventana.pollEvent(e)) {
            if (e.type == Event::Closed)
                ventana.close();
        }

        ventana.clear(Color(25, 25, 25));

        float x = 30;
        float y = 80;

        for (size_t i = 0; i < usuarios.size(); ++i) {
            RectangleShape nodo(Vector2f(160, 40));
            nodo.setPosition(x, y);
            nodo.setFillColor(Color(90, 180, 100));
            nodo.setOutlineThickness(2);
            nodo.setOutlineColor(Color::White);

            Text txt(usuarios[i], fuente, 14);
            txt.setFillColor(Color::White);
            txt.setPosition(x + 8, y + 10);

            ventana.draw(nodo);
            ventana.draw(txt);

            if (i < usuarios.size() - 1) {
                Vertex arrow[] = {
                    Vertex(Vector2f(x + 160, y + 20), Color::White),
                    Vertex(Vector2f(x + 180, y + 20), Color::White)
                };
                ventana.draw(arrow, 2, Lines);
            }

            x += 200;
        }

        ventana.display();
    }
}
