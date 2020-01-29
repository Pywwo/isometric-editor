/*
** EPITECH PROJECT, 2019
** editor
** File description:
** gonne have the window, and all the classes mandatory / also gestion onglet
*/

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Tile.hpp"
#include "Background.hpp"
#include "Layer.hpp"
#include "Objects.hpp"

class Editor
{
public:
    Editor();
    ~Editor();
    void setSaveFileName(const std::string fileName);
    void run();
    void displayOngletChoice();
    void displayByChoice();
    void editorEvent(sf::Event &event);
    void editorEventMouse(int x, int y);
private:
    sf::RenderWindow _window;
    std::string _saveName;
    //map
    // choice onglet
    Onglet _onglet;
    sf::Texture _textureOnglet;

    // mes classes
    Background _background;
    Tile _tile;
    Layer _layer;
    Objects _objects;
};

#endif