#ifndef USUARIOLISTVIEW_H
#define USUARIOLISTVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// ✅ Funciones para dibujar listas de usuarios y accesos
// Las versiones con parámetros permiten scroll visual

// Funciones con posición personalizada (usadas por la vista)
void dibujarUsuarios(sf::RenderWindow& ventana, sf::Font& fuente,
                     const std::vector<std::string>& usuarios,
                     float posYInicial, float alturaMaxima);

void dibujarAccesos(sf::RenderWindow& ventana, sf::Font& fuente,
                    const std::vector<std::pair<int, std::string>>& accesos,
                    float posYInicial, float alturaMaxima);

// ✅ Funciones de compatibilidad para mantener código anterior
void dibujarUsuarios(sf::RenderWindow& ventana, sf::Font& fuente,
                     const std::vector<std::string>& usuarios);

void dibujarAccesos(sf::RenderWindow& ventana, sf::Font& fuente,
                    const std::vector<std::pair<int, std::string>>& accesos);

#endif
