#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Map.hpp"
#include "Hero.hpp"
#include "Item.hpp"
#include "Villagers.hpp"
#include "PerkCard.hpp"
#include "MonsterCard.hpp"

enum class Turn {
    HERO, MONSTER
};

enum class Player {
    PLAYER_1, PLAYER_2
};

struct Players
{
    Turn turn = Turn::HERO;
    Player player;
    std::string namePlayer;
    Heroes hero1;
    Heroes hero2;
    Players(Map& map) : hero1{0, NameHeroes::ARCHAEOLOGIST, map, NameLocation::CAMP}, hero2{0, NameHeroes::MAYOR, map, NameLocation::CAVE} {
    } 
};

class Games {
private:
    Map mapGames;

    Villager villagerGames{this->mapGames};
    Item itemGames{this->mapGames};

    Players player1{mapGames};
    Players player2{mapGames};

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
    
    void setButtonAndTextMenu(sf::RectangleShape&, sf::RectangleShape&, sf::RectangleShape&, sf::Text&, sf::Text&, sf::Text&);
    void setImageInDesktop(const sf::Texture&, sf::Sprite&);
    void menu(bool = true);
    
    void setButtonAndTextStartGame(sf::RectangleShape&, sf::RectangleShape&, sf::RectangleShape&, sf::Text&, sf::Text&, sf::Text&, sf::Text&, sf::Text&);
    std::vector<std::string> startPlay(const std::string&);
    //////////////////////////////
    void startGame();
    void addLocations();

    void drawPrekCard(const PerkCardType&);


};

