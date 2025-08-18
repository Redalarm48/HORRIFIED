#pragma once

#include "../include/Map.hpp"
#include <SFML/Graphics.hpp>
#include "../include/Hero.hpp"
#include "../include/Item.hpp"
#include "../include/Villagers.hpp"
#include "PerkCard.hpp"
#include "MonsterCard.hpp"
#include <string>

enum class Player {
    PLAYER_1, PLAYER_2
};

struct Players
{
    Player player;
    std::string namePlayer;
};

class Games {
private:
    Map mapGames;

    // MonsterDeck monsterCardInGames;
    // Heroes hero;
    Villager villagerGames{this->mapGames};
    Item itemGames{this->mapGames};

    Players player1;
    Players player2;

    std::vector<std::pair<NameLocation, sf::CircleShape>> locations;



    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window {this->desktop, "HORIFIED", sf::Style::Fullscreen};
    
    sf::Event event;
    
    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

    sf::Font font;
    
    sf::Vector2u windowSize;
public:
    Games();

    void setFont();
    bool isMouseOver(const sf::RectangleShape&, const sf::RenderWindow&);
    bool isMouseOver(const sf::CircleShape&, const sf::RenderWindow&);
    void centerTextInButton(sf::Text&, const sf::RectangleShape&);
    

    //////////////////////////////

};