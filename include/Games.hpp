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
    std::shared_ptr<Heroes> hero1;
    std::shared_ptr<Heroes> hero2;
    Monster monster;
    Players(Map& map) : hero1(std::make_shared<Archaeologist>(map)),
        hero2(std::make_shared<Mayor>(map)),
        monster(NameMonster::INVISIBLE_MAN, 3, map)
        {}

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
    void setButtonAndImageAction(sf::RectangleShape&,sf::Texture&, sf::Sprite&, const std::string&, const int, const int);
    void run(Players&);
    void Games::setImageMVHI(sf::Texture&, sf::Sprite&, const std::string&, const int);

    template<typename T>
    void setButtonClickedLocation(std::vector<std::pair<T, sf::RectangleShape>>&, const std::vector<T>&, std::vector<sf::Sprite>&, std::vector<sf::Texture>&, const int, const int = 0);


    void drawPrekCard(const PerkCardType&);
    std::string drawMonsterCard(const MonsterCardType&);
    std::string drawCard(const std::string&, const int);

    std::string getNameImage(const NameItem&);
    std::string getNameImage(const NameVillagers&);
    std::string getNameImage(const NameHeroes&);
    std::string getNameImage(const NameMonster&);
    std::string getNameImage(const bool);


};

