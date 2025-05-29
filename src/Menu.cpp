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

        // Configurar sombra
        sombra.setSize(Vector2f(ancho, alto));
        sombra.setFillColor(Color(0, 0, 0, 50));
        sombra.setPosition(x + 3, y + 3);

        // Configurar caja principal
        caja.setSize(Vector2f(ancho, alto));
        caja.setFillColor(colorBase);
        caja.setPosition(x, y);

        // Configurar texto
        texto.setFont(fuente);
        texto.setString(label);
        texto.setCharacterSize(static_cast<unsigned int>(alto * 0.4f)); 
        texto.setFillColor(Color::Black);
        
        // Centrar texto
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
        
        // Ajustar tamaño de texto proporcionalmente
        texto.setCharacterSize(static_cast<unsigned int>(alto * 0.4f));
        actualizarPosicionTexto();
    }

    void actualizar(Vector2f mouse, float deltaTime) {
        bool estaEnHover = caja.getGlobalBounds().contains(mouse);
        
        if (estaEnHover != hover) {
            hover = estaEnHover;
        }

        // Animación suave
        float objetivo = hover ? 1.0f : 0.0f;
        animacion += (objetivo - animacion) * deltaTime * 8.0f;

        // Interpolar colores
        Color colorActual;
        colorActual.r = static_cast<sf::Uint8>(colorBase.r + (colorHover.r - colorBase.r) * animacion);
        colorActual.g = static_cast<sf::Uint8>(colorBase.g + (colorHover.g - colorBase.g) * animacion);
        colorActual.b = static_cast<sf::Uint8>(colorBase.b + (colorHover.b - colorBase.b) * animacion);
        colorActual.a = 255;

        caja.setFillColor(colorActual);

        // Efecto de elevación
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
    
    // Gradiente de fondo
    VertexArray fondoGradiente;

public:
    MenuResponsive() {
        fuente = cargarFuenteMenu();
        configurarFondoGradiente();
    }

    void configurarFondoGradiente() {
        fondoGradiente.setPrimitiveType(Quads);
        fondoGradiente.resize(4);
        Color colorSuperior(20, 20, 20);   // Casi negro (gris muy oscuro)
        Color colorInferior(34, 34, 34);   // Negro suave con un poco de contraste
        
        fondoGradiente[0].color = colorSuperior;
        fondoGradiente[1].color = colorSuperior;
        fondoGradiente[2].color = colorInferior;
        fondoGradiente[3].color = colorInferior;
    }

    void actualizarLayout(Vector2u nuevoTamaño) {
        tamañoVentana = nuevoTamaño;
        
        // Actualizar gradiente de fondo
        fondoGradiente[0].position = Vector2f(0, 0);
        fondoGradiente[1].position = Vector2f(static_cast<float>(nuevoTamaño.x), 0);
        fondoGradiente[2].position = Vector2f(static_cast<float>(nuevoTamaño.x), static_cast<float>(nuevoTamaño.y));
        fondoGradiente[3].position = Vector2f(0, static_cast<float>(nuevoTamaño.y));

        // Configurar título responsive
        titulo.setFont(fuente);
        titulo.setString("Sistema de Accesos");
        titulo.setCharacterSize(static_cast<unsigned int>(nuevoTamaño.y * 0.08f)); // 8% de la altura
        titulo.setFillColor(Color::White);
        
        FloatRect tituloRect = titulo.getLocalBounds();
        titulo.setOrigin(tituloRect.left + tituloRect.width / 2, tituloRect.top + tituloRect.height / 2);
        titulo.setPosition(static_cast<float>(nuevoTamaño.x) / 2, static_cast<float>(nuevoTamaño.y) * 0.15f);

        // Limpiar botones existentes
        botones.clear();

        // Calcular dimensiones responsive
        float anchoBoton = static_cast<float>(nuevoTamaño.x) * 0.5f;  // 50% del ancho
        float altoBoton = static_cast<float>(nuevoTamaño.y) * 0.08f;   // 8% de la altura
        float espacioVertical = static_cast<float>(nuevoTamaño.y) * 0.12f; // 12% para espaciado
        
        // Limitar tamaños mínimos y máximos
        anchoBoton = max(200.0f, min(anchoBoton, 400.0f));
        altoBoton = max(40.0f, min(altoBoton, 70.0f));

        float x = (static_cast<float>(nuevoTamaño.x) - anchoBoton) / 2;
        float yInicial = static_cast<float>(nuevoTamaño.y) * 0.35f;

        // Crear botones con colores diferentes
        botones.emplace_back(x, yInicial, anchoBoton, altoBoton, "Gestionar Accesos", fuente,
                           Color::White, Color(230, 230, 230)); // Verde
        
        botones.emplace_back(x, yInicial + espacioVertical, anchoBoton, altoBoton, "Ver Pacientes", fuente,
                          Color::White, Color(230, 230, 230)); // Azul
        
        botones.emplace_back(x, yInicial + espacioVertical * 2, anchoBoton, altoBoton, "Salir", fuente,
                          Color::White, Color(230, 230, 230)); // Rojo
    }

    int ejecutar() {
        Vector2u tamañoInicial(800, 600); // Tamaño inicial más grande
        ventana = new RenderWindow(VideoMode(tamañoInicial.x, tamañoInicial.y), 
                                 "Sistema de Accesos", Style::Default);
        
        // Configurar ícono de ventana (opcional)
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
                    // Actualizar vista cuando se redimensiona
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
                            return static_cast<int>(i + 1); // Retornar 1, 2, 3
                        }
                    }
                }
            }

            // Actualizar animaciones
            Vector2f mousePos = ventana->mapPixelToCoords(Mouse::getPosition(*ventana));
            for (auto& boton : botones) {
                boton.actualizar(mousePos, deltaTime);
            }

            // Dibujar todo
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