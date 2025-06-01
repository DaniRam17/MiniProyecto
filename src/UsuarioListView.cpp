// Archivo: src/UsuarioListView.cpp
#include "../include/UsuarioListView.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


void dibujarUsuarios(RenderWindow& ventana, Font& fuente, const vector<string>& usuarios, float posYInicial, float alturaMaxima) {
    float y = posYInicial;
    float x = 600;
    float limiteY = posYInicial + alturaMaxima - 40;

    for (size_t i = 0; i < usuarios.size(); ++i) {
        if (y > limiteY) {
            Text masElementos("... (+" + to_string(usuarios.size() - i) + " usuarios más)", fuente, 12);
            masElementos.setFillColor(Color(200, 200, 200));
            masElementos.setPosition(x, y);
            ventana.draw(masElementos);
            break;
        }

        RectangleShape nodo(Vector2f(180, 30));
        nodo.setPosition(x, y);
        nodo.setFillColor(Color(60, 120, 160));
        nodo.setOutlineThickness(1);
        nodo.setOutlineColor(Color(90, 170, 210));

        Text txt(usuarios[i], fuente, 14);
        txt.setFillColor(Color::White);
        txt.setPosition(x + 10, y + 5);

        ventana.draw(nodo);
        ventana.draw(txt);

        y += 45;
    }
}

void dibujarAccesos(RenderWindow& ventana, Font& fuente, const vector<pair<int, string>>& accesos, float posYInicial, float alturaMaxima) {
    float y = posYInicial;
    float x = 50;
    float limiteY = posYInicial + alturaMaxima - 50;

    for (size_t i = 0; i < accesos.size(); ++i) {
        if (y > limiteY) {
            Text masElementos("... (+" + to_string(accesos.size() - i) + " accesos más)", fuente, 12);
            masElementos.setFillColor(Color(150, 150, 150));
            masElementos.setPosition(x, y);
            ventana.draw(masElementos);
            break;
        }

        RectangleShape nodo(Vector2f(240, 40));
        nodo.setPosition(x, y);
        nodo.setFillColor(Color(100, 149, 237));
        nodo.setOutlineThickness(1);
        nodo.setOutlineColor(Color(120, 169, 255));

        string textoMostrar = accesos[i].second;
        if (textoMostrar.length() > 30) {
            textoMostrar = textoMostrar.substr(0, 27) + "...";
        }

        Text txt(textoMostrar, fuente, 14);
        txt.setFillColor(Color::White);
        txt.setPosition(x + 10, y + 10);

        ventana.draw(nodo);
        ventana.draw(txt);

        y += 55;
    }
}


void dibujarUsuarios(RenderWindow& ventana, Font& fuente, const vector<string>& usuarios) {
    dibujarUsuarios(ventana, fuente, usuarios, 450.0f, 200.0f);
}

void dibujarAccesos(RenderWindow& ventana, Font& fuente, const vector<pair<int, string>>& accesos) {
    dibujarAccesos(ventana, fuente, accesos, 450.0f, 200.0f);
}
