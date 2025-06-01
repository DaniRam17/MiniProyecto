// Archivo: src/ListVisualizer.cpp#include "../include/ListVisualizer.h"
#include <SFML/Graphics.hpp>
#include <sstream>
using namespace std;
using namespace sf;

void manejarScrollBotones(RenderWindow &ventana, RectangleShape &botonIzq, RectangleShape &botonDer, int &offsetX) {
    Event e;
    while (ventana.pollEvent(e)) {
        if (e.type == Event::Closed)
            ventana.close();
        if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
            Vector2f mousePos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
            if (botonIzq.getGlobalBounds().contains(mousePos)) {
                offsetX = max(0, offsetX - 220);
            }
            if (botonDer.getGlobalBounds().contains(mousePos)) {
                offsetX += 220;
            }
        }
    }
}

void mostrarListaAccesos(Font &fuente, const vector<pair<int, string>> &accesos) {
    RenderWindow ventana(VideoMode(1200, 300), "Lista de Accesos (Visualizacion)", Style::Titlebar | Style::Close);
    ventana.setFramerateLimit(60);

    RectangleShape botonIzq(Vector2f(40, 40));
    botonIzq.setPosition(10, 240);
    botonIzq.setFillColor(Color(50, 50, 50));
    RectangleShape botonDer(Vector2f(40, 40));
    botonDer.setPosition(1150, 240);
    botonDer.setFillColor(Color(50, 50, 50));

    Text txtIzq("<", fuente, 22);
    txtIzq.setPosition(20, 242);
    txtIzq.setFillColor(Color::White);
    Text txtDer(">", fuente, 22);
    txtDer.setPosition(1160, 242);
    txtDer.setFillColor(Color::White);

    Text titulo("Desde Primer a Ultimo acceso", fuente, 18);
    titulo.setFillColor(Color::White);
    titulo.setStyle(Text::Italic | Text::Bold);
    titulo.setPosition(420, 20);
    Text leyendaContador("", fuente, 14);
    leyendaContador.setFillColor(Color(200, 200, 200));
    leyendaContador.setPosition(460, 50);

    int offsetX = 0;

    while (ventana.isOpen()) {
        manejarScrollBotones(ventana, botonIzq, botonDer, offsetX);

        ventana.clear(Color(20, 20, 20));
        ventana.draw(titulo);

        float x = 30 - offsetX;
        float y = 100;

        for (size_t i = 0; i < accesos.size(); ++i) {
            RectangleShape nodo(Vector2f(160, 40));
            nodo.setPosition(x, y);
            nodo.setFillColor(Color(80, 170, 250));
            nodo.setOutlineThickness(2);
            nodo.setOutlineColor(Color::White);

            Text txt(accesos[i].second, fuente, 13);
            txt.setFillColor(Color::White);
            txt.setPosition(x + 8, y + 10);

            ventana.draw(nodo);
            ventana.draw(txt);

            if (i < accesos.size() - 1) {
                Vertex arrow[] = {
                    Vertex(Vector2f(x + 160, y + 20), Color::White),
                    Vertex(Vector2f(x + 180, y + 20), Color::White)};
                ventana.draw(arrow, 2, Lines);
            }

            x += 200;
        }

        // Mostrar leyenda cantidad visible
        int nodosVisibles = 1200 / 200;
        stringstream ss;
        ss << "Mostrando " << min((int)accesos.size(), nodosVisibles) << " de " << accesos.size() << " nodos";
        leyendaContador.setString(ss.str());
        ventana.draw(leyendaContador);

        ventana.draw(botonIzq);
        ventana.draw(txtIzq);
        ventana.draw(botonDer);
        ventana.draw(txtDer);

        ventana.display();
    }
}

void mostrarListaUsuarios(Font &fuente, const vector<string> &usuarios) {
    RenderWindow ventana(VideoMode(1200, 300), "Lista de Usuarios (Visualizacion)", Style::Titlebar | Style::Close);
    ventana.setFramerateLimit(60);

    RectangleShape botonIzq(Vector2f(40, 40));
    botonIzq.setPosition(10, 240);
    botonIzq.setFillColor(Color(50, 50, 50));
    RectangleShape botonDer(Vector2f(40, 40));
    botonDer.setPosition(1150, 240);
    botonDer.setFillColor(Color(50, 50, 50));

    Text txtIzq("<", fuente, 22);
    txtIzq.setPosition(20, 242);
    txtIzq.setFillColor(Color::White);
    Text txtDer(">", fuente, 22);
    txtDer.setPosition(1160, 242);
    txtDer.setFillColor(Color::White);

    Text titulo("Inicio a Fin de lista", fuente, 18);
    titulo.setFillColor(Color::White);
    titulo.setStyle(Text::Italic | Text::Bold);
    titulo.setPosition(460, 20);

    Text leyendaContador("", fuente, 14);
    leyendaContador.setFillColor(Color(200, 200, 200));
    leyendaContador.setPosition(460, 50);

    int offsetX = 0;

    while (ventana.isOpen()) {
        manejarScrollBotones(ventana, botonIzq, botonDer, offsetX);

        ventana.clear(Color(10, 10, 10));
        ventana.draw(titulo);

        float x = 30 - offsetX;
        float y = 100;

        for (size_t i = 0; i < usuarios.size(); ++i) {
            RectangleShape nodo(Vector2f(160, 40));
            nodo.setPosition(x, y);
            nodo.setFillColor(Color(90, 200, 120));
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
                    Vertex(Vector2f(x + 180, y + 20), Color::White)};
                ventana.draw(arrow, 2, Lines);
            }

            x += 200;
        }

        // Mostrar leyenda cantidad visible
        int nodosVisibles = 1200 / 200;
        stringstream ss;
        ss << "Mostrando " << min((int)usuarios.size(), nodosVisibles) << " de " << usuarios.size() << " nodos";
        leyendaContador.setString(ss.str());
        ventana.draw(leyendaContador);
        ventana.draw(botonIzq);
        ventana.draw(txtIzq);
        ventana.draw(botonDer);
        ventana.draw(txtDer);

        ventana.display();
    }
}
