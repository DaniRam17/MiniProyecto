#include "../include/InputBox.h"
#include <iostream>

InputBox::InputBox(float x, float y, float ancho, float alto, sf::Font& fuente, const std::string& placeholderTexto)
    : placeholder(placeholderTexto), activa(false), contenido(""), minWidth(ancho), originalWidth(ancho), padding(10.0f)
{
    caja.setSize(sf::Vector2f(ancho, alto));
    caja.setPosition(x, y);
    caja.setFillColor(sf::Color(245, 245, 245));
    caja.setOutlineColor(sf::Color::Black);
    caja.setOutlineThickness(2);

    texto.setFont(fuente);
    texto.setCharacterSize(18);
    texto.setPosition(x + padding, y + (alto - 18) / 2); // Vertically centered

    // Initially show placeholder in gray
    texto.setFillColor(sf::Color(150, 150, 150));
    texto.setString(placeholder);
}

void InputBox::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::FloatRect bounds = caja.getGlobalBounds();
        activa = bounds.contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        update();
    } 
    else if (event.type == sf::Event::TextEntered && activa) {
        if (event.text.unicode == 8 && !contenido.empty()) {
            // Backspace: remove last character
            contenido.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
            // Only allow printable characters
            contenido += static_cast<char>(event.text.unicode);
        }
        update();
        adjustWidth(); // Adjust width after text changes
    }
}

void InputBox::draw(sf::RenderWindow& ventana) {
    ventana.draw(caja);
    ventana.draw(texto);
}

std::string InputBox::getTexto() const {
    return contenido;
}

void InputBox::setTexto(const std::string& nuevo) {
    contenido = nuevo;
    update();
    adjustWidth();
}

void InputBox::setActiva(bool estado) {
    activa = estado;
    update();
}

void InputBox::update() {
    // Change border color based on active state
    caja.setOutlineColor(activa ? sf::Color(30, 144, 255) : sf::Color::Black);

    if (contenido.empty() && !activa) {
        // Show placeholder in gray
        texto.setFillColor(sf::Color(150, 150, 150));
        texto.setString(placeholder);
    }
    else {
        // Show content in black
        texto.setFillColor(sf::Color::Black);
        texto.setString(contenido);
    }
}

void InputBox::adjustWidth() {
    // Calculate required width based on text
    float textWidth = texto.getLocalBounds().width + 2 * padding;
    float newWidth = std::max(minWidth, textWidth);
    
    // Only update if width changed significantly
    if (std::abs(caja.getSize().x - newWidth) > 1.0f) {
        caja.setSize(sf::Vector2f(newWidth, caja.getSize().y));
    }
}

void InputBox::setPosition(float x, float y) {
    caja.setPosition(x, y);
    texto.setPosition(x + padding, y + (caja.getSize().y - texto.getCharacterSize()) / 2);
}