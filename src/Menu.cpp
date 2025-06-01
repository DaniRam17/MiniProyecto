// Archivo: src/Menu.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <cmath>
using namespace sf;
using namespace std;

sf::Font cargarFuenteMenu() {
    sf::Font fuente;
    vector<string> rutas = {
        "assets/SourceCodePro-Bold.ttf",
        "C:/MiniProyecto/assets/SourceCodePro-Bold.ttf",

    };

    for (const auto& ruta : rutas) {
        if (filesystem::exists(ruta) && fuente.loadFromFile(ruta)) {
            cout << "Fuente cargada para menu desde: " << ruta << endl;
            return fuente;
        }
    }

    cerr << "No se pudo cargar ninguna fuente para el menu.\n";
    return fuente;
}

struct BotonResponsive {
    RectangleShape caja;
    RectangleShape sombra;
    Text texto;
    bool hover = false;
    float animacion = 0.0f;
    Color colorBase;
    Color colorHover;
    Color colorTexto;

    BotonResponsive(float x, float y, float ancho, float alto, const string& label, Font& fuente, 
                   Color base = Color(52, 152, 219), Color hover_color = Color(41, 128, 185)) {
        colorBase = base;
        colorHover = hover_color;
        colorTexto = Color::Black;

    
        sombra.setSize(Vector2f(ancho, alto));
        sombra.setFillColor(Color(0, 0, 0, 50));
        sombra.setPosition(x + 3, y + 3);


        caja.setSize(Vector2f(ancho, alto));
        caja.setFillColor(colorBase);
        caja.setPosition(x, y);


        texto.setFont(fuente);
        texto.setString(label);
        texto.setCharacterSize(static_cast<unsigned int>(alto * 0.4f)); 
        texto.setFillColor(Color::Black);
        

        actualizarPosicionTexto();
    }

    void actualizarPosicionTexto() {
        FloatRect textBounds = texto.getLocalBounds();
        FloatRect cajaBounds = caja.getGlobalBounds();
        texto.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        texto.setPosition(cajaBounds.left + cajaBounds.width / 2, cajaBounds.top + cajaBounds.height / 2);
    }

    void actualizarTamaño(float x, float y, float ancho, float alto) {
        sombra.setSize(Vector2f(ancho, alto));
        sombra.setPosition(x + 3, y + 3);
        
        caja.setSize(Vector2f(ancho, alto));
        caja.setPosition(x, y);
        
    
        texto.setCharacterSize(static_cast<unsigned int>(alto * 0.4f));
        actualizarPosicionTexto();
    }

    void actualizar(Vector2f mouse, float deltaTime) {
        bool estaEnHover = caja.getGlobalBounds().contains(mouse);
        
        if (estaEnHover != hover) {
            hover = estaEnHover;
        }

    
        float objetivo = hover ? 1.0f : 0.0f;
        animacion += (objetivo - animacion) * deltaTime * 8.0f;

  
        Color colorActual;
        colorActual.r = static_cast<sf::Uint8>(colorBase.r + (colorHover.r - colorBase.r) * animacion);
        colorActual.g = static_cast<sf::Uint8>(colorBase.g + (colorHover.g - colorBase.g) * animacion);
        colorActual.b = static_cast<sf::Uint8>(colorBase.b + (colorHover.b - colorBase.b) * animacion);
        colorActual.a = 255;

        caja.setFillColor(colorActual);

    
        float elevacion = animacion * 2.0f;
        Vector2f posOriginal = caja.getPosition();
        sombra.setPosition(posOriginal.x + 3 + elevacion, posOriginal.y + 3 + elevacion);

        Color colorSombra = sombra.getFillColor();
        colorSombra.a = static_cast<sf::Uint8>(50 + animacion * 30);
        sombra.setFillColor(colorSombra);
    }

    bool estaPresionado(Vector2f mouse) {
        return caja.getGlobalBounds().contains(mouse);
    }

    void dibujar(RenderWindow& ventana) {
        ventana.draw(sombra);
        ventana.draw(caja);
        ventana.draw(texto);
    }
};

class MenuResponsive {
private:
    RenderWindow* ventana;
    Font fuente;
    vector<BotonResponsive> botones;
    Text titulo;
    Clock reloj;
    Vector2u tamañoVentana;
    

    VertexArray fondoGradiente;

public:
    MenuResponsive() {
        fuente = cargarFuenteMenu();
        configurarFondoGradiente();
    }

    void configurarFondoGradiente() {
        fondoGradiente.setPrimitiveType(Quads);
        fondoGradiente.resize(4);
        Color colorSuperior(20, 20, 20);   
        Color colorInferior(34, 34, 34);   
        
        fondoGradiente[0].color = colorSuperior;
        fondoGradiente[1].color = colorSuperior;
        fondoGradiente[2].color = colorInferior;
        fondoGradiente[3].color = colorInferior;
    }

    void actualizarLayout(Vector2u nuevoTamaño) {
        tamañoVentana = nuevoTamaño;
        
 
        fondoGradiente[0].position = Vector2f(0, 0);
        fondoGradiente[1].position = Vector2f(static_cast<float>(nuevoTamaño.x), 0);
        fondoGradiente[2].position = Vector2f(static_cast<float>(nuevoTamaño.x), static_cast<float>(nuevoTamaño.y));
        fondoGradiente[3].position = Vector2f(0, static_cast<float>(nuevoTamaño.y));


        titulo.setFont(fuente);
        titulo.setString("Sistema de Accesos");
        titulo.setCharacterSize(static_cast<unsigned int>(nuevoTamaño.y * 0.08f)); 
        titulo.setFillColor(Color::White);
        
        FloatRect tituloRect = titulo.getLocalBounds();
        titulo.setOrigin(tituloRect.left + tituloRect.width / 2, tituloRect.top + tituloRect.height / 2);
        titulo.setPosition(static_cast<float>(nuevoTamaño.x) / 2, static_cast<float>(nuevoTamaño.y) * 0.15f);


        botones.clear();

      
        float anchoBoton = static_cast<float>(nuevoTamaño.x) * 0.5f;  
        float altoBoton = static_cast<float>(nuevoTamaño.y) * 0.08f;   
        float espacioVertical = static_cast<float>(nuevoTamaño.y) * 0.12f; 
        
       
        anchoBoton = max(200.0f, min(anchoBoton, 400.0f));
        altoBoton = max(40.0f, min(altoBoton, 70.0f));

        float x = (static_cast<float>(nuevoTamaño.x) - anchoBoton) / 2;
        float yInicial = static_cast<float>(nuevoTamaño.y) * 0.35f;

        botones.emplace_back(x, yInicial, anchoBoton, altoBoton, "Gestionar Accesos", fuente,
                           Color::White, Color(230, 230, 230)); 
        
        botones.emplace_back(x, yInicial + espacioVertical, anchoBoton, altoBoton, "Ver Pacientes", fuente,
                          Color::White, Color(230, 230, 230)); 
        
        botones.emplace_back(x, yInicial + espacioVertical * 2, anchoBoton, altoBoton, "Salir", fuente,
                          Color::White, Color(230, 230, 230));
    }

    int ejecutar() {
        Vector2u tamañoInicial(800, 600); 
        ventana = new RenderWindow(VideoMode(tamañoInicial.x, tamañoInicial.y), 
                                 "Sistema de Accesos", Style::Default);
     
        ventana->setVerticalSyncEnabled(true);
        
        actualizarLayout(tamañoInicial);

        while (ventana->isOpen()) {
            float deltaTime = reloj.restart().asSeconds();
            Event evento;
            
            while (ventana->pollEvent(evento)) {
                if (evento.type == Event::Closed) {
                    ventana->close();
                }

                if (evento.type == Event::Resized) {
                   
                    ventana->setView(View(FloatRect(0, 0, 
                        static_cast<float>(evento.size.width), 
                        static_cast<float>(evento.size.height))));
                    actualizarLayout(Vector2u(evento.size.width, evento.size.height));
                }

                if (evento.type == Event::MouseButtonPressed && evento.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = ventana->mapPixelToCoords(Mouse::getPosition(*ventana));
                    
                    for (size_t i = 0; i < botones.size(); ++i) {
                        if (botones[i].estaPresionado(mousePos)) {
                            delete ventana;
                            return static_cast<int>(i + 1);
                        }
                    }
                }
            }

        
            Vector2f mousePos = ventana->mapPixelToCoords(Mouse::getPosition(*ventana));
            for (auto& boton : botones) {
                boton.actualizar(mousePos, deltaTime);
            }

          
            ventana->clear();
            ventana->draw(fondoGradiente);
            ventana->draw(titulo);
            
            for (auto& boton : botones) {
                boton.dibujar(*ventana);
            }
            
            ventana->display();
        }

        delete ventana;
        return 0;
    }
};

int mostrarMenu() {
    MenuResponsive menu;
    return menu.ejecutar();
}