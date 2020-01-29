/*
** EPITECH PROJECT, 2019
** layer
** File description:
** 
*/

#include "Layer.hpp"

Layer::Layer() {
    _textureFrame.loadFromFile("graphicUtils/frame.png");
    _textureMax = 3;
    for (int i = 0; i < _textureMax; i++) {
        _textureArray[i].loadFromFile("graphic/layer/" + std::to_string(i) + ".png");
        _textureArray[i].setSmooth(true);
    }
    _choice = 0;
}

Layer::~Layer() {

}


void Layer::buttonPressed(int i) {
   this->_choice = i;
}

void Layer::setGui(sf::RenderWindow &win) {
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
            h->add(tgui::Picture::create("graphic/layer/" + std::to_string(i) + ".png"));
            //button
            auto button = tgui::Button::create();
            button->setRenderer(theme.getRenderer("Button"));
            button->setPosition(75, 70);
            button->setText("choose");
            button->setSize(10, 30);
            button->connect("pressed", &Layer::buttonPressed, this, i);
            h->add(button);
            grid->addWidget(h, i, 0);
    }

    scrollPanel->add(grid);
    _gui.add(scrollPanel);
}

bool sort(const std::pair<sf::Vector2f, int> &lhs, const std::pair<sf::Vector2f, int> &rhs) { return lhs.first.y < rhs.first.y; }

void Layer::event(sf::Event &event) {
    _gui.handleEvent(event);
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.x > 20 and 
event.mouseButton.x < 1350 + 100 and 
event.mouseButton.y > ((1034 - 810) / 2 - 5) - 50 and 
event.mouseButton.y < ((1034 - 810) / 2 - 5) + 810 + 50) {
            std::pair<sf::Vector2f, int> New;
            New.first.x = event.mouseButton.x - _textureArray[_choice].getSize().x / 2;
            New.first.y = event.mouseButton.y - _textureArray[_choice].getSize().y / 2;
            New.second = _choice;
            _list.push_back(New);
            std::sort(_list.begin(), _list.end(), sort);
        }
    }
}

void Layer::displayGui(sf::RenderWindow &window) {
    _gui.draw();
}

void Layer::displayLayer(sf::RenderWindow &window) {
    for (auto it : _list) {
        sf::Sprite spr(_textureArray[it.second]);
        spr.setPosition(it.first);
        window.draw(spr);
    }
}

void Layer::display(sf::RenderWindow &window) {

    displayLayer(window);
    sf::Sprite choiceSpr(_textureArray[_choice]);
    sf::Vector2f posChoice = (static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    posChoice.x -= _textureArray[_choice].getSize().x / 2;
    posChoice.y -= _textureArray[_choice].getSize().y / 2;
    choiceSpr.setPosition(posChoice);
    window.draw(choiceSpr);

    sf::Sprite sprFrame(_textureFrame);
    sprFrame.setPosition(40 - 5, (1034 - 810) / 2 - 5);
    window.draw(sprFrame);
    displayGui(window);
}