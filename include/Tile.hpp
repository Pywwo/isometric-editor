/*
** EPITECH PROJECT, 2019
** Background.hpp
** File description:
** 
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enum.hpp"
#include <TGUI/TGUI.hpp>
#include <array>

class Tile
{
public:
    Tile();
    ~Tile();
    void display(sf::RenderWindow &window);
    void setGui(sf::RenderWindow &window);
    void displayGui(sf::RenderWindow &window);
    void event(sf::Event &event);
    void buttonPressed(int i);
    void posToIsoPoint(int x, int y);
    void buttonGrid();
    void displayTile(sf::RenderWindow &window, bool displayGrid);
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
    //map tile
    std::array<std::array<int, 34>, 34> _map;
    //offsets
    float _offsetX;
    float _offsetY;
};

#endif