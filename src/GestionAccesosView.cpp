#include "../include/GestionAccesosView.h"
#include "../include/InputBox.h"
#include "../include/Usuario.h"
#include "../include/HashTable.h"
#include "../include/UsuarioListView.h"
#include "../include/Archivo.h"
#include "../include/ListVisualizer.h" 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace sf;
using namespace std;

void mostrarVistaGestionAccesos(Font& fuente, HashTable& tabla) {
    RenderWindow ventana(VideoMode(1100, 720), "Gestion de Accesos - HashTable", Style::Close);
    ventana.setFramerateLimit(60);

    int offsetAccesos = 0;
    int offsetUsuarios = 0;

    vector<pair<int, string>> accesosVisibles;
    vector<string> usuariosVisuales;

    Color fondo(18, 18, 20);
    Color colorPrimario(59, 130, 246), colorPrimarioHover(37, 99, 235);
    Color colorExito(34, 197, 94), colorExitoHover(22, 163, 74);
    Color colorError(239, 68, 68), colorErrorHover(220, 38, 38);
    Color colorSecundario(107, 114, 128), colorSecundarioHover(75, 85, 99);
    Color colorLimpiar(168, 85, 247), colorLimpiarHover(147, 51, 234); 

    int spacingY = 55;
    int posX = 40;
    int anchoInput = 280; 
    int botonCol1X = 400, botonCol2X = 680; 
    int botonWidth = 240, botonHeight = 45; 

    
    InputBox inputId(posX, spacingY * 1, anchoInput, 35, fuente, "ID");
    InputBox inputNombre(posX, spacingY * 2, anchoInput, 35, fuente, "Nombre");
    InputBox inputCorreo(posX, spacingY * 3, anchoInput, 35, fuente, "Correo");
    InputBox inputEliminarN(posX, spacingY * 4, anchoInput, 35, fuente, "Cantidad de accesos a Eliminar");
    InputBox inputBuscarPos(posX, spacingY * 5, anchoInput, 35, fuente, "Ingrese la posicion a buscar");
    InputBox inputEliminarId(posX, spacingY * 6, anchoInput, 35, fuente, "Ingrese el ID a Eliminar");
    InputBox inputEliminarPos(posX, spacingY * 7, anchoInput, 35, fuente, "Ingrese la posicion a Eliminar");

 
    int resultadoX = 50;
    int resultadoY = 480; 
    InputBox resultadoId(resultadoX, resultadoY, anchoInput, 35, fuente, "ID Encontrado");
    InputBox resultadoNombre(resultadoX + anchoInput + 20, resultadoY, anchoInput + 50, 35, fuente, "Nombre Encontrado");
    InputBox resultadoCorreo(resultadoX + anchoInput + anchoInput + 90, resultadoY, anchoInput + 50, 35, fuente, "Correo Encontrado");

    auto crearBoton = [&](float x, float y, Color color, Color colorHover, const string& texto) {
        RectangleShape boton(Vector2f(botonWidth, botonHeight));
        boton.setPosition(x, y);
        boton.setFillColor(color);

        RectangleShape sombra(Vector2f(botonWidth, botonHeight));
        sombra.setPosition(x + 2, y + 2);
        sombra.setFillColor(Color(0, 0, 0, 30));

        Text t(texto, fuente, 15);
        t.setFillColor(Color::White);
        t.setStyle(Text::Bold);
        FloatRect textBounds = t.getLocalBounds();
        t.setPosition(x + (botonWidth - textBounds.width) / 2, y + (botonHeight - textBounds.height) / 2 - 2);
        return make_tuple(boton, sombra, t);
    };

    auto [botonBuscar, sombraBuscar, txtBuscar] = crearBoton(botonCol1X, spacingY * 1, colorPrimario, colorPrimarioHover, "Buscar Usuario Por ID");
    auto [botonBuscarPosicion, sombraBuscarPosicion, txtBuscarPosicion] = crearBoton(botonCol2X, spacingY * 1, colorPrimario, colorPrimarioHover, "Buscar Usuario Por Posicion");
    auto [botonAcceso, sombraAcceso, txtAcceso] = crearBoton(botonCol2X, spacingY * 2, colorPrimario, colorPrimarioHover, "Registrar Acceso");
    auto [botonRegistrar, sombraRegistrar, txtRegistrar] = crearBoton(botonCol1X, spacingY * 2, colorExito, colorExitoHover, "Registrar Usuario");
    auto [botonEliminar, sombraEliminar, txtEliminar] = crearBoton(botonCol2X, spacingY * 3, colorError, colorErrorHover, "Eliminar Accesos");
    auto [botonEliminarUsr, sombraEliminarUsr, txtEliminarUsr] = crearBoton(botonCol1X, spacingY * 3, colorError, colorErrorHover, "Eliminar Usuario ID");
    auto [botonEliminarPos, sombraEliminarPos, txtEliminarPos] = crearBoton(botonCol2X, spacingY * 4, colorError, colorErrorHover, "Eliminar por Posicion");
    auto [botonVerUsuarios, sombraVerUsuarios, txtVerUsuarios] = crearBoton(botonCol1X, spacingY * 4, colorSecundario, colorSecundarioHover, "Ver Usuarios");
    auto [botonVerLista, sombraVerLista, txtVerLista] = crearBoton(botonCol2X, spacingY * 5, colorSecundario, colorSecundarioHover, "Ver Lista Accesos");
    auto [botonLimpiar, sombraLimpiar, txtLimpiar] = crearBoton(botonCol1X + 140, spacingY * 7, colorLimpiar, colorLimpiarHover, "Limpiar Todo");

   
    Text tituloResultados("RESULTADOS DE BUSQUEDA", fuente, 16);
    tituloResultados.setFillColor(Color(156, 163, 175));
    tituloResultados.setStyle(Text::Bold);
    tituloResultados.setPosition(40, resultadoY - 30);

    Text salida("", fuente, 16);
    salida.setFillColor(Color::White);
    salida.setStyle(Text::Bold);
    salida.setPosition(40, 670);

    RectangleShape fondoMensaje(Vector2f(1020, 35));
    fondoMensaje.setPosition(35, 665);
    fondoMensaje.setFillColor(Color(35, 39, 42, 180));
    fondoMensaje.setOutlineThickness(1);
    fondoMensaje.setOutlineColor(Color(65, 75, 85));


    auto limpiarTodo = [&]() {
        inputId.setTexto("");
        inputNombre.setTexto("");
        inputCorreo.setTexto("");
        inputEliminarN.setTexto("");
        inputBuscarPos.setTexto("");
        inputEliminarId.setTexto("");
        inputEliminarPos.setTexto("");
        
    
        resultadoId.setTexto("");
        resultadoNombre.setTexto("");
        resultadoCorreo.setTexto("");

        salida.setString("Campos limpiados.");
        salida.setFillColor(colorSecundario);
        
        accesosVisibles.clear();
    };

    while (ventana.isOpen()) {
        Event e;
        while (ventana.pollEvent(e)) {
            if (e.type == Event::Closed)
                ventana.close();

            inputId.handleEvent(e); inputId.adjustWidth();
            inputNombre.handleEvent(e); inputNombre.adjustWidth();
            inputCorreo.handleEvent(e); inputCorreo.adjustWidth();
            inputEliminarN.handleEvent(e); inputEliminarN.adjustWidth();
            inputBuscarPos.handleEvent(e); inputBuscarPos.adjustWidth();
            inputEliminarId.handleEvent(e); inputEliminarId.adjustWidth();
            inputEliminarPos.handleEvent(e); inputEliminarPos.adjustWidth();

            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                Vector2f mpos = ventana.mapPixelToCoords(Mouse::getPosition(ventana));
                auto clicEn = [&](RectangleShape& r) { return r.getGlobalBounds().contains(mpos); };

                if (clicEn(botonBuscar)) {
                    if (inputId.getTexto().empty()) {
                        salida.setString("Ingrese un ID valido.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputId.getTexto());
                    Usuario* u = tabla.buscarUsuario(id);
                    if (u) {
                        salida.setString("Usuario encontrado correctamente.");
                        salida.setFillColor(colorExito);
                        accesosVisibles = tabla.obtenerAccesosVisuales(id);
                        
                    
                        resultadoId.setTexto(to_string(u->getId()));
                        resultadoNombre.setTexto(u->getNombre());
                        resultadoCorreo.setTexto(u->getCorreo());
                    } else {
                        salida.setString("Usuario no existe en el sistema.");
                        salida.setFillColor(colorError);
                   
                        resultadoId.setTexto("");
                        resultadoNombre.setTexto("");
                        resultadoCorreo.setTexto("");
                    }
                }
                else if (clicEn(botonBuscarPosicion)) {
                if (inputBuscarPos.getTexto().empty()) {
                salida.setString("Ingrese una posicion valida.");
                salida.setFillColor(Color(255, 193, 7));
                continue;
                }
                int posicion = stoi(inputBuscarPos.getTexto());
                Usuario* u = tabla.buscarUsuarioPorPosicion(posicion);
                if (u) {
                salida.setString("Usuario encontrado en posicion " + to_string(posicion) + ".");
                salida.setFillColor(colorExito);
                accesosVisibles = tabla.obtenerAccesosVisuales(u->getId());
        
               
                resultadoId.setTexto(to_string(u->getId()));
                resultadoNombre.setTexto(u->getNombre());
                resultadoCorreo.setTexto(u->getCorreo());
                 } else {
                salida.setString("No existe usuario en la posicion " + to_string(posicion) + ".");
                salida.setFillColor(colorError);
               
                resultadoId.setTexto("");
                resultadoNombre.setTexto("");
                resultadoCorreo.setTexto("");
                accesosVisibles.clear();
                 }  
                }
                else if (clicEn(botonRegistrar)) {
                    if (inputId.getTexto().empty()) {
                        salida.setString("Ingrese un ID valido.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputId.getTexto());
                    string nombre = inputNombre.getTexto();
                    string correo = inputCorreo.getTexto();
                    if (nombre.empty() || correo.empty()) {
                        salida.setString("Complete todos los campos.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    Usuario* nuevo = new Usuario(id, nombre, correo);
                    if (tabla.insertarUsuario(nuevo)) {
                        Archivo::guardarUsuario(*nuevo, "data/usuarios.dat");
                        salida.setString("Usuario registrado exitosamente.");
                        salida.setFillColor(colorExito);
                        accesosVisibles = tabla.obtenerAccesosVisuales(id);
                        
                        
                        resultadoId.setTexto(to_string(nuevo->getId()));
                        resultadoNombre.setTexto(nuevo->getNombre());
                        resultadoCorreo.setTexto(nuevo->getCorreo());
                    } else {
                        salida.setString("ID duplicado o colision detectada.");
                        salida.setFillColor(colorError);
                        delete nuevo;
                    }
                }
                else if (clicEn(botonAcceso)) {
                    if (inputId.getTexto().empty()) {
                        salida.setString("Ingrese un ID para registrar acceso.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputId.getTexto());
                    Usuario* u = tabla.buscarUsuario(id);
                    if (u) {
                        u->registrarAcceso();
                        salida.setString("Acceso registrado.");
                        salida.setFillColor(colorExito);
                        accesosVisibles = tabla.obtenerAccesosVisuales(id);
                    } else {
                        salida.setString("Usuario no encontrado.");
                        salida.setFillColor(colorError);
                    }
                }
                else if (clicEn(botonEliminar)) {
                    if (inputEliminarN.getTexto().empty() || inputId.getTexto().empty()) {
                        salida.setString("Ingrese ID y cantidad.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputId.getTexto());
                    int n = stoi(inputEliminarN.getTexto());
                    Usuario* u = tabla.buscarUsuario(id);
                    if (u) {
                        u->eliminarAccesos(n);
                        salida.setString("Accesos eliminados.");
                        salida.setFillColor(colorExito);
                        accesosVisibles = tabla.obtenerAccesosVisuales(id);
                    } else {
                        salida.setString("Usuario no encontrado.");
                        salida.setFillColor(colorError);
                    }
                }
                else if (clicEn(botonEliminarUsr)) {
                    if (inputEliminarId.getTexto().empty()) {
                        salida.setString("Ingrese un ID a eliminar.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputEliminarId.getTexto());
                    if (tabla.eliminarUsuarioPorId(id)) {
                        salida.setString("Usuario eliminado.");
                        salida.setFillColor(colorExito);
                        accesosVisibles.clear();
                      
                        resultadoId.setTexto("");
                        resultadoNombre.setTexto("");
                        resultadoCorreo.setTexto("");
                    } else {
                        salida.setString("Usuario no encontrado.");
                        salida.setFillColor(colorError);
                    }
                }
                else if (clicEn(botonEliminarPos)) {
                    if (inputEliminarPos.getTexto().empty()) {
                        salida.setString("Ingrese posicion valida.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int pos = stoi(inputEliminarPos.getTexto());
                    if (tabla.eliminarUsuarioPorPosicion(pos)) {
                        salida.setString("Usuario eliminado por posicion.");
                        salida.setFillColor(colorExito);
                        accesosVisibles.clear();
                       
                        resultadoId.setTexto("");
                        resultadoNombre.setTexto("");
                        resultadoCorreo.setTexto("");
                    } else {
                        salida.setString("Posicion vacia o invalida.");
                        salida.setFillColor(colorError);
                    }
                }
                else if (clicEn(botonVerLista)) {
                    if (inputId.getTexto().empty()) {
                        salida.setString("Ingrese un ID para ver accesos.");
                        salida.setFillColor(Color(255, 193, 7));
                        continue;
                    }
                    int id = stoi(inputId.getTexto());
                    accesosVisibles = tabla.obtenerAccesosVisuales(id);
                    salida.setString("Mostrando lista de accesos...");
                    salida.setFillColor(colorExito);

                  
                    mostrarListaAccesos(fuente, accesosVisibles);
                }
                else if (clicEn(botonVerUsuarios)) {
                    usuariosVisuales = tabla.obtenerUsuariosComoLista();
                    salida.setString("Mostrando lista de usuarios...");
                    salida.setFillColor(colorExito);

                    mostrarListaUsuarios(fuente, usuariosVisuales);
                }
           
                else if (clicEn(botonLimpiar)) {
                    limpiarTodo();
                }
            }
        }

        ventana.clear(fondo);

        inputId.update(); inputId.draw(ventana);
        inputNombre.update(); inputNombre.draw(ventana);
        inputCorreo.update(); inputCorreo.draw(ventana);
        inputEliminarN.update(); inputEliminarN.draw(ventana);
        inputBuscarPos.update(); inputBuscarPos.draw(ventana);
        inputEliminarId.update(); inputEliminarId.draw(ventana);
        inputEliminarPos.update(); inputEliminarPos.draw(ventana);

  
        ventana.draw(tituloResultados);
        resultadoId.update(); resultadoId.draw(ventana);
        resultadoNombre.update(); resultadoNombre.draw(ventana);
        resultadoCorreo.update(); resultadoCorreo.draw(ventana);

       
        ventana.draw(sombraBuscarPosicion);
        ventana.draw(sombraBuscar); ventana.draw(sombraRegistrar);
        ventana.draw(sombraAcceso); ventana.draw(sombraEliminar);
        ventana.draw(sombraEliminarUsr); ventana.draw(sombraEliminarPos);
        ventana.draw(sombraVerLista); ventana.draw(sombraVerUsuarios);
        ventana.draw(sombraLimpiar);


        ventana.draw(botonBuscar);
         ventana.draw(txtBuscar);
         ventana.draw(botonBuscarPosicion);
         ventana.draw(txtBuscarPosicion);
        ventana.draw(botonAcceso); ventana.draw(txtAcceso);
         ventana.draw(botonRegistrar); ventana.draw(txtRegistrar);
        ventana.draw(botonEliminar); ventana.draw(txtEliminar);
        ventana.draw(botonEliminarUsr); ventana.draw(txtEliminarUsr);
        ventana.draw(botonEliminarPos); ventana.draw(txtEliminarPos);
         ventana.draw(botonVerUsuarios); ventana.draw(txtVerUsuarios);
        ventana.draw(botonVerLista); ventana.draw(txtVerLista);
        ventana.draw(botonLimpiar); ventana.draw(txtLimpiar); 
        ventana.draw(fondoMensaje);
        ventana.draw(salida);

        ventana.display();
    }
}