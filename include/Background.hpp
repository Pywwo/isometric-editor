/*
** EPITECH PROJECT, 2019
** Background.hpp
** File description:
** 
*/

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Enum.hpp"
#include <TGUI/TGUI.hpp>

class Background
{
public:
    Background();
    ~Background();
    void display(sf::RenderWindow &window);
    void setGui(sf::RenderWindow &window);
    void displayGui(sf::RenderWindow &window);
    void event(sf::Event &event);
    void buttonPressed(int i);
    void displayBackground(sf::RenderWindow &window);
private:
    //frame
    sf::Texture _textureFrame;
    std::array<sf::Texture, 9> _textureArray;
    int _textureMax;
    //choice
    unsigned int _choice;
    //gui
    tgui::Gui _gui;
};

#endif