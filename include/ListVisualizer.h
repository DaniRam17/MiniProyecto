// Archivo: include/ListVisualizer.h
// -------------------------------------------------------------
// INTERFAZ DE VISUALIZACIÓN DEDICADA DE LISTAS ENLAZADAS
// Muestra accesos y usuarios como nodos conectados gráficamente
// -------------------------------------------------------------

#ifndef LISTVISUALIZER_H
#define LISTVISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


void mostrarListaAccesos(sf::Font& fuente, const std::vector<std::pair<int, std::string>>& accesos);


void mostrarListaUsuarios(sf::Font& fuente, const std::vector<std::string>& usuarios);

#endif
