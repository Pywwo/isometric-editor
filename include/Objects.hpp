/*
** EPITECH PROJECT, 2019
** objects.hpp
** File description:
** for epitech
*/

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enum.hpp"
#include <TGUI/TGUI.hpp>
#include <array>

class Objects
{
public:
    Objects();
    ~Objects();
    void display(sf::RenderWindow &window);
    void setGui(sf::RenderWindow &window);
    void displayGui(sf::RenderWindow &window);
    void event(sf::Event &event);
    void buttonPressed(int i);
    void posToIsoPoint(int x, int y);
    void buttonGrid();
    void displayObjects(sf::RenderWindow &window, bool displayGrid);
private:
    //frame
    sf::Texture _textureFrame;
    std::array<sf::Texture, 10> _textureArray;
    int _textureMax;
    //choice
    unsigned int _choice;
    //gui
    tgui::Gui _gui;
    //grid
    sf::Texture _grid;
    bool _displayGrid;
    //map Objects
    std::array<std::array<int, 34>, 34> _map;
    //offsets
    float _offsetX;
    float _offsetY;
};

#endif