/*
** EPITECH PROJECT, 2019
** Background.cpp
** File description:
** 
*/

#include "Background.hpp"
//a delete
#include <iostream>

Background::Background() {
    _textureFrame.loadFromFile("graphicUtils/frame.png");
    _textureMax = 9;
    for (int i = 0; i < _textureMax; i++) {
        _textureArray[i].loadFromFile("graphic/background/" + std::to_string(i) + ".png");
        _textureArray[i].setSmooth(true);
    }
    _choice = 0;
}

Background::~Background() {

}

void Background::buttonPressed(int i) {
   this->_choice = i;
}

void Background::setGui(sf::RenderWindow &win) {
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
            h->add(tgui::Picture::create("graphic/background/" + std::to_string(i) + ".png"));
            //button
            auto button = tgui::Button::create();
            button->setRenderer(theme.getRenderer("Button"));
            button->setPosition(75, 70);
            button->setText("choose");
            button->setSize(10, 30);
            button->connect("pressed", &Background::buttonPressed, this, i);
            h->add(button);
            grid->addWidget(h, i, 0);
    }

    scrollPanel->add(grid);
    _gui.add(scrollPanel);
}

void Background::event(sf::Event &event) {
    _gui.handleEvent(event);
}

void Background::displayGui(sf::RenderWindow &window) {
    _gui.draw();
}

void Background::displayBackground(sf::RenderWindow &window) {
    sf::Sprite sprBackground(_textureArray[_choice]);
    sprBackground.scale(
        static_cast<float>(static_cast<float>(1350) / static_cast<float>(_textureArray[_choice].getSize().x)), 
        static_cast<float>(static_cast<float>(810) / static_cast<float>(_textureArray[_choice].getSize().y))
    );
//    sprBackground.setColor(sf::Color(255, 255, 255, 100));
    sprBackground.setPosition(40, (1034 - 810) / 2);
    window.draw(sprBackground);
    displayGui(window);
}

void Background::display(sf::RenderWindow &window) {
    sf::Sprite sprFrame(_textureFrame);
    sprFrame.setPosition(40 - 5, (1034 - 810) / 2 - 5);
    window.draw(sprFrame);

    displayBackground(window);
}