/*
** EPITECH PROJECT, 2019
** Objects.cpp
** File description:
** for epitech
*/


#include "Objects.hpp"
//a delete
#include <iostream>

Objects::Objects() {
    _textureFrame.loadFromFile("graphicUtils/frame.png");
    _textureMax = 9;
    for (int i = 0; i < _textureMax; i++) {
       _textureArray[i].loadFromFile("graphic/Objects/" + std::to_string(i) + ".png");
    }
    _choice = 0;
    _grid.loadFromFile("graphicUtils/grid3.png");
    for (auto &it : _map)
        it.fill(0);
    _offsetX = 40 + 7.5 * 90;
    _offsetY = (1034 - 810) / 2 - 22.5 * 16;
    _displayGrid = true;
}

Objects::~Objects() {

}

void Objects::buttonPressed(int i) {
   this->_choice = i;
}

void Objects::buttonGrid() {
    if (_displayGrid == true) {
        _displayGrid = false;
        return;
    }
    _displayGrid = true;
}

void Objects::setGui(sf::RenderWindow &win) {
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
            h->add(tgui::Picture::create("graphic/Objects/" + std::to_string(i) + ".png"));
            //button
            auto button = tgui::Button::create();
            button->setRenderer(theme.getRenderer("Button"));
            button->setPosition(75, 70);
            button->setText("choose");
            button->setSize(10, 30);
            button->connect("pressed", &Objects::buttonPressed, this, i);
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
    button->connect("pressed", &Objects::buttonGrid, this);
    _gui.add(button);
}

void Objects::posToIsoPoint(int x, int y) {
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

void Objects::event(sf::Event &event) {
    _gui.handleEvent(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        posToIsoPoint(event.mouseButton.x, event.mouseButton.y);
    }
}

void Objects::displayGui(sf::RenderWindow &window) {
    _gui.draw();
}

void Objects::displayObjects(sf::RenderWindow &window, bool displayGrid) {
    sf::Vector2f vec;

    //display iso map
    for (int i = 0; i < 34; i++) {
        for (int j = 0; j < 34; j++) {
            vec.x = ((j - i) * 45) - 45 + _offsetX;
            vec.y = ((j + i) * 22.5) + _offsetY;
            if (vec.x > -50 and vec.x < 1350 and vec.y > 81 and vec.y < 913) {
                sf::Sprite sprObjects(_textureArray[_map[i][j]]);
                sprObjects.setPosition(vec.x - ((_textureArray[_map[i][j]].getSize().x - 90) / 2), (vec.y - _textureArray[_map[i][j]].getSize().y) + 45);
                window.draw(sprObjects);
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

    sf::Sprite choiceSpr(_textureArray[_choice]);
    sf::Vector2f posChoice = (static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    posChoice.x -= _textureArray[_choice].getSize().x / 2;
    posChoice.y -= _textureArray[_choice].getSize().y;
    choiceSpr.setPosition(posChoice);
    window.draw(choiceSpr);
}

void Objects::display(sf::RenderWindow &window) {

    displayObjects(window, _displayGrid);
    displayGui(window);
}