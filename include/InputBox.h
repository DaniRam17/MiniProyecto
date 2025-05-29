#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class InputBox {
private:
    sf::RectangleShape caja;
    sf::Text texto;
    std::string contenido;
    std::string placeholder;  
    bool activa;
    float minWidth;  // Minimum width of the box
    float originalWidth; // Original width to revert when empty
    float padding;   // Padding between text and box edges

public:
    InputBox(float x, float y, float ancho, float alto, sf::Font& fuente, const std::string& placeholder = "");

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& ventana);
    std::string getTexto() const;
    void setTexto(const std::string& nuevo);
    void setActiva(bool activa);
    void update();
    void adjustWidth(); // New method to adjust box width
    void setPosition(float x, float y); // To update position after width changes

};

#endif