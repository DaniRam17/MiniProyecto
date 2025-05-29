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

// ✅ Visualiza la lista de accesos como una lista enlazada horizontal
void mostrarListaAccesos(sf::Font& fuente, const std::vector<std::pair<int, std::string>>& accesos);

// ✅ Visualiza la lista de usuarios en orden de inserción como nodos
void mostrarListaUsuarios(sf::Font& fuente, const std::vector<std::string>& usuarios);

#endif
