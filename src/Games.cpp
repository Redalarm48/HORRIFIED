#include "../include/Games.hpp"
#include <iostream>
#include <cmath>


Games::Games() {
    this->arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    this->handCursor.loadFromSystem(sf::Cursor::Hand);
    this->windowSize = this->window.getSize();
    setFont();
    // this->itemGames{(this->mapGames)};
    // Heroes hero(4, NameHeroes::ARCHAEOLOGIST, this->mapGames);
}

void Games::setFont() {
    if(!font.loadFromFile("../font/Creepster-Regular.ttf")) {
        throw std::invalid_argument("not found font");
    }
}

bool Games::isMouseOver(const sf::RectangleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

bool Games::isMouseOver(const sf::CircleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}



void Games::centerTextInButton(sf::Text& text, const sf::RectangleShape& button) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    text.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);
}

