/*
** EPITECH PROJECT, 2019
** Background.cpp
** File description:
** 
*/

#include "Tile.hpp"
//a delete
#include <iostream>

Tile::Tile() {
    _textureFrame.loadFromFile("graphicUtils/frame.png");
    _textureMax = 10;
    for (int i = 0; i < _textureMax; i++) {
       _textureArray[i].loadFromFile("graphic/tile/" + std::to_string(i) + ".png");
    }
    _choice = 0;
    _grid.loadFromFile("graphicUtils/grid3.png");
    for (auto &it : _map)
        it.fill(0);
    _offsetX = 40 + 7.5 * 90;
    _offsetY = (1034 - 810) / 2 - 22.5 * 16;
    _displayGrid = true;
}

Tile::~Tile() {

}

void Tile::buttonPressed(int i) {
   this->_choice = i;
}

void Tile::buttonGrid() {
    if (_displayGrid == true) {
        _displayGrid = false;
        return;
    }
    _displayGrid = true;
}

void Tile::setGui(sf::RenderWindow &win) {
    _gui.setTarget(win);

    //theme
    tgui::Theme theme("guiGraphic/Black.txt");

    //scrollpanel
    auto scrollPanel = tgui::ScrollablePanel::create({ "25%", "75%" });
    scrollPanel->setPosition(1920 - (0.25 * 1920), 1034 * 0.125);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(214, 206, 205));
    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    auto grid = tgui::Grid::create();
    for (int i = 0; i < _textureMax; ++i)
    {
            auto h = tgui::HorizontalLayout::create({ tgui::bindWidth(scrollPanel), tgui::bindHeight(scrollPanel) / 8 });
        //    h->add(tgui::Label::create(std::to_string(i) + ".png"));
            h->add(tgui::Picture::create("graphic/tile/" + std::to_string(i) + ".png"));
            //button
            auto button = tgui::Button::create();
            button->setRenderer(theme.getRenderer("Button"));
            button->setPosition(75, 70);
            button->setText("choose");
            button->setSize(10, 30);
            button->connect("pressed", &Tile::buttonPressed, this, i);
            h->add(button);
            grid->addWidget(h, i, 0);
    }

    scrollPanel->add(grid);
    _gui.add(scrollPanel);
    //button grid
    auto button = tgui::Button::create();
    button->setRenderer(theme.getRenderer("Button"));
    button->setPosition(1500, 70);
    button->setText("grid");
    button->setSize(100, 50);
    button->connect("pressed", &Tile::buttonGrid, this);
    _gui.add(button);
}

void Tile::posToIsoPoint(int x, int y) {
    if (x > -50 and x < 1390 + 23 and y > 81 and y < 1000) {
        float posX = 0.0;
        float posY = 0.0;
        posX = ((x - _offsetX) / 45 + (y - _offsetY) / 22.5) / 2;
        posY = ((y - _offsetY) / 22.5 - ((x - _offsetX) / 45)) / 2;

        if (posX < 0.0 or posY < 0.0)
            return;
        if (posY >= static_cast<float>(_map.size()) or posX >= static_cast<float>(_map[0].size())) {
            return;
        }
        _map[posY][posX] = _choice;
    }
}

void Tile::event(sf::Event &event) {
    _gui.handleEvent(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        posToIsoPoint(event.mouseButton.x, event.mouseButton.y);
    }
}

void Tile::displayGui(sf::RenderWindow &window) {
    _gui.draw();
}

void Tile::displayTile(sf::RenderWindow &window, bool displayGrid) {
    sf::Vector2f vec;

    //display iso map
    for (int i = 0; i < 34; i++) {
        for (int j = 0; j < 34; j++) {
            vec.x = ((j - i) * 45) - 45 + _offsetX;
            vec.y = ((j + i) * 22.5) + _offsetY;
            if (vec.x > -50 and vec.x < 1350 and vec.y > 81 and vec.y < 913) {
                sf::Sprite sprTile(_textureArray[_map[i][j]]);
                sprTile.setPosition(vec.x - ((_textureArray[_map[i][j]].getSize().x - 90) / 2), vec.y);
                window.draw(sprTile);
            }
        }
    }
    //display iso grid
    if (displayGrid == true) {
        sf::Sprite sprGrid(_grid);
        for (int i = 0; i < 34; i++) {
            for (int j = 0; j < 34; j++) {
                vec.x = ((j - i) * 45) - 45 + _offsetX;
                vec.y = ((j + i) * 22.5) + _offsetY;
                if (vec.x > -50 and vec.x < 1350 and vec.y > 81 and vec.y < 913) {
                    sprGrid.setPosition(vec.x - ((_grid.getSize().x - 90) / 2), vec.y);
                    window.draw(sprGrid);
                }
            }
        }
    }
    //display frame
    sf::Sprite sprFrame(_textureFrame);
    sprFrame.setPosition(40 - 5, (1034 - 810) / 2 - 5);
    window.draw(sprFrame);
}

void Tile::display(sf::RenderWindow &window) {

    displayTile(window, _displayGrid);
    displayGui(window);
}