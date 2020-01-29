/*
** EPITECH PROJECT, 2019
** editor.cpp
** File description:
** 
*/

#include "Editor.hpp"

Editor::Editor() : _window(sf::VideoMode(1920, 1034), "editor", sf::Style::Titlebar | sf::Style::Close) {
    _onglet = CHOICE_BACKROUND;
    _textureOnglet.loadFromFile("graphicUtils/choiceWindow.png");
    _background.setGui(_window);
    _tile.setGui(_window);
    _layer.setGui(_window);
    _objects.setGui(_window);
}

Editor::~Editor() {

}

void Editor::setSaveFileName(const std::string fileName) {
    _saveName = fileName;
}

void Editor::displayOngletChoice() {
    sf::Sprite onglet(_textureOnglet);

    onglet.setTextureRect(sf::IntRect(0, 0 + _onglet * 64, 1920, 64));
    _window.draw(onglet);
}

void Editor::displayByChoice() {
    if (_onglet == CHOICE_BACKROUND) {
        _background.display(_window);
    } else if (_onglet == CHOICE_TILE) {
        _background.displayBackground(_window);
        _tile.display(_window);
    } else if (_onglet == CHOICE_LAYER) {
        _background.displayBackground(_window);
        _tile.displayTile(_window, false);
        _layer.display(_window);
    } else if (_onglet == CHOICE_OBJECT) {
        _background.displayBackground(_window);
        _tile.displayTile(_window, false);
        _layer.displayLayer(_window);
        _objects.display(_window);
    }
}

void Editor::editorEventMouse(int x, int y) {
    if (x > 710 and x < 1210 and y > 5 and y < 31) {
        int tmpChoice = (x - 710) / 100;
        _onglet = static_cast<Onglet>(tmpChoice);
    }
}

void Editor::editorEvent(sf::Event &event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        editorEventMouse(event.mouseButton.x, event.mouseButton.y);
    }

}

void Editor::run() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            editorEvent(event);
            if (_onglet == CHOICE_BACKROUND)
                _background.event(event);
            else if (_onglet == CHOICE_TILE)
                _tile.event(event);
            else if (_onglet == CHOICE_LAYER)
                _layer.event(event);
            else if (_onglet == CHOICE_OBJECT)
                _objects.event(event);
        }
//        _window.clear(sf::Color::Black);
       _window.clear(sf::Color(163, 218, 244));
        displayOngletChoice();
        displayByChoice();
        _window.display();
    }
}