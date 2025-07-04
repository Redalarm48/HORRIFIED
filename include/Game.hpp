#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include "Hero.hpp"
#include "Map.hpp"
#include "Monster.hpp"
#include "Dracula.hpp"
#include "InvisibleMan.hpp"
#include "Item.hpp"
#include "Villagers.hpp"
#include "PerkCard.hpp"
#include "MonsterCard.hpp"
#include <unordered_set>


class Game {
private:
    
    Map& gameMap;
    Mayor mayor;
    Archaeologist archaeologist;
    Heroes* currentHero;
    Dracula dracula;
    InvisibleMan invisibleMan;
    Monster* frenziedMonster;
    int terrorLevel;
    std::vector<Item*> itemBag;
    std::vector<Item*> activeItems;
    PerkDeck perkDeck;
    MonsterDeck monsterDeck{ &dracula, &invisibleMan, &dracula };
    std::vector<std::string> draculaCoffinLocations = { "cave", "crypt", "dungeon", "graveyard" };
    bool invisibleAdvanceDone = true;
    bool isMayorTurn;
    Villager villagerManager;
    int itemIndex;
    std::vector<Heroes*> heroes;
    std::vector<std::pair<std::string ,std::string>> villagers;
    std::string pekrcardName;
    bool monsterPhaseTrue = true;
    std::vector<Item*> allGameItems;


public:
    Game();
    Map& gM();
    void run();
    void initializeGame();
    void startGameLoop();
    void placeInitialItems();
    void heroTurn(Heroes& hero);
    void displayHeroMenu(Heroes& hero);
    void monsterPhase();
    void resolveMonsterCard(const MonsterCard& card);
    void rollDiceAndResolve(const std::vector<Monster*>& order, int diceCount);
    bool checkWinCondition() const;
    bool checkLoseCondition() const;
    void increaseTerrorLevel();

    void placeVillager(const std::string& name, const std::string& location, const std::string& safeZone);
    Item& getNextItem();
    std::string getRandomLocation() const;
    void determineFirstPlayer();
    void resolveMonsterEvent(const MonsterCard& card);
    void rollDice(const MonsterCard& card);
    void handleDraculaAttack();
    void handleInvisibleManAttack();
    void returnItemToBag(Item* item); 
    void placeRandomItem(int count); 
    void placeRandomItemAt(const std::string& location, int count);
    std::string findLocationWithMostItems() const;
    void handleDefeatDracula(Monster* monster, Heroes& hero);
    void handleAdvanceInvisibleMan(Heroes& hero);

    void setMonsterPhaseTrue(bool);
    void setInvisibleAdvanceDone(bool);
};

#endif // GAME_HPP
