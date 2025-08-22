#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Dracula.hpp"
#include "Map.hpp"
#include "Hero.hpp"
#include "Monster.hpp"
#include "InvisibleMan.hpp"
#include "Item.hpp"
#include "Villagers.hpp"
#include "PerkCard.hpp"
#include "MonsterCard.hpp"

class Dracula;

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
    Players( Map& map, PerkDeck& perk,
        std::shared_ptr<Heroes> h1,
            std::shared_ptr<Heroes> h2)
        : hero1(h1), hero2(h2) {}

};

class Games {
private:
    Map mapGames;
    PerkDeck perckCardGames{};
    
    std::shared_ptr<Monster> invisibleMan;
    std::shared_ptr<Monster> dracula;

    std::shared_ptr<Heroes> mayor;
    std::shared_ptr<Heroes> archaeologist;
    std::shared_ptr<Heroes> courier;
    std::shared_ptr<Heroes> scientist;


    MonsterDeck monsterCardInGames;
    Villager villagerGames{this->mapGames, this->perckCardGames};
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
    
    void setButtonAndTextMenu(sf::RectangleShape&, sf::RectangleShape&, sf::RectangleShape&, sf::Text&, sf::Text&, sf::Text&);
    void setImageInDesktop(const sf::Texture&, sf::Sprite&);
    void menu(bool = true);
    
    void setButtonAndTextStartGame(sf::RectangleShape&, sf::RectangleShape&, sf::RectangleShape&, sf::Text&, sf::Text&, sf::Text&, sf::Text&, sf::Text&);
    std::vector<std::string> startPlay(const std::string&);
    //////////////////////////////

    void startGame();
    void run(Players&);
    void addLocations();
    void clickedLocation(const NameLocation&, Players&, Heroes&, const NameAction& = NameAction::DEFAULT);
    void setImageMVHI(sf::Texture&, sf::Sprite&, const std::string&, const int);
    void setImageMonsterCard(sf::Texture&, sf::Sprite&, sf::RectangleShape&, const std::string&, int = 600);
    void setButtonAndImageAction(sf::RectangleShape&,sf::Texture&, sf::Sprite&, const std::string&, const int, const int);
    template<typename T>
    void setButtonClickedLocation(std::vector<std::pair<T, sf::RectangleShape>>&, const std::vector<T>&, std::vector<sf::Sprite>&, std::vector<sf::Texture>&, const int, const int = 0);
    std::string getNameImage(const NameItem&);
    std::string getNameImage(const NameVillagers&);
    std::string getNameImage(const NameHeroes&);
    std::string getNameImage(const NameMonster&);
    std::string getNameImage(const PerkCardType&);
    std::string getNameImage(const bool);

    void cout(const std::string&);
    void guideGames(const NameLocation&, const std::vector<std::pair<NameVillagers,sf::RectangleShape>>&, Players&);
    void guideGames(Players&);
    void moveGames(Players&);
    bool yesOrNo();
    void pickUpGames(const std::vector<NameItem>&, Heroes&);
    void advanceGames(Players&);
    void defeatGames(Players&);

    void drawPrekCard(const PerkCardType&);
    std::string drawMonsterCard(const MonsterCardType&);
    std::string drawCard(const std::string&, const int);
};