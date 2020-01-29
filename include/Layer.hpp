/*
** EPITECH PROJECT, 2019
** layer.hpp
** File description:
** 
*/

#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enum.hpp"
#include <TGUI/TGUI.hpp>

//a delete
#include <iostream>

//ajouter ctrl + z

class Layer
{
public:
    Layer();
    ~Layer();
    void display(sf::RenderWindow &window);
    void setGui(sf::RenderWindow &window);
    void displayGui(sf::RenderWindow &window);
    void event(sf::Event &event);
    void buttonPressed(int i);
    void displayLayer(sf::RenderWindow &window);
private:
    //frame
    sf::Texture _textureFrame;
    std::array<sf::Texture, 9> _textureArray;
    int _textureMax;
    //choice
    unsigned int _choice;
    //gui
    tgui::Gui _gui;
    //list of layers
    std::vector<std::pair<sf::Vector2f, int>> _list; // premier pour pos, deuxième pour texture
};

#endif