#include "..\include\Game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Game::Game()
    : gameMap(Map::getInstance()),
      mayor(3, "Mayor", gameMap),
      archaeologist(3, "Archaeologist", gameMap),
      dracula(gameMap),
      invisibleMan(gameMap),
      frenziedMonster(nullptr),
      terrorLevel(0),
      isMayorTurn(true),
      itemIndex(0),
      currentHero(&mayor),
      villagerManager(gameMap) {
    for (int i = 0; i < 60; ++i) {
    Item::allItems.push_back(new Item(static_cast<itemType>(i % 3), &gameMap, "item_" + std::to_string(i)));
}

}

Map& Game:: gM()
{
    return gameMap;
}

void Game::initializeGame() {
    perkDeck.initializeDeck();
    monsterDeck.initializeDeck();
    std::shuffle(Item::allItems.begin(), Item::allItems.end(), std::default_random_engine(std::random_device{}()));

    for (int i = 0; i < 12; ++i) {
        auto& item = getNextItem();
        std::string location = getRandomLocation();
        gameMap.setPlayerPosition(item.getName(), location);
    }

    frenziedMonster = &dracula;
    determineFirstPlayer();
}

void Game::determineFirstPlayer() {
    int mayorTime, archaeologistTime;
    std::cout << "Player controlling Mayor, when was your last meal? (hh:mm) ";
    std::cin >> mayorTime;
    std::cout << "Player controlling Archaeologist, when was your last meal? (hh:mm) ";
    std::cin >> archaeologistTime;

    isMayorTurn = (mayorTime > archaeologistTime);
}

Item& Game::getNextItem() {
    if (itemIndex >= Item::allItems.size()) itemIndex = 0;
    return *(Item::allItems[itemIndex++]);
}

std::string Game::getRandomLocation() const {
    static std::vector<std::string> locations = {
        "cave", "museum", "hospital", "camp", "crypt", "church", "precinct", "abbey",
        "laboratory", "inn", "mansion", "graveyard", "barn", "shop", "institute",
        "dungeon", "docks", "theatre", "tower"
    };
    return locations[rand() % locations.size()];
}

void Game::startGameLoop() {
    while (!checkWinCondition() && !checkLoseCondition()) {
        currentHero = isMayorTurn ? &mayor : &archaeologist;
        heroTurn(*currentHero);
        villagerManager.getLocationVillager();
        monsterPhase();
        isMayorTurn = !isMayorTurn;
    }

    if (checkWinCondition())
    { 

    std::cout << "Heroes win!\n";
    
    }
    else
    {

    std::cout << "Monsters win!\n";
    
    }
    
}

void Game::heroTurn(Heroes& hero) {
    hero.resetActions();
    while (hero.canTakeAction()) {
        std::cout << "\n" << hero.getName() << " Turn. Actions left: " << (3 - hero.getNumberActionTaken()) << "\n";
        std::cout << "1. Move\n2. Guide Villager\n3. Pick Up Item\n4. Defeat Monster\n5.Show Inventory\n6. End Turn\n";
        gameMap.print();
        gameMap.printPlayers();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: hero.move(); break;
            case 2: hero.guide(); break;
            case 3: handlePickUp(hero); break;
            case 4: hero.defeat(); break;
            case 5 : hero.showInventory(); break;
            case 6: return;

            default: std::cout << "Invalid choice\n";
        }
    }
}

void Game::monsterPhase() {

    heroes = {&mayor , &archaeologist};
    villagers = villagerManager.getActiveVillagers();

    if (monsterDeck.isEmpty()) 
    {
        return;
    }
    MonsterCard card = monsterDeck.drawCard();
    std::cout << "\nMonster Card Drawn: " << card.getDescription() << "\n";

    resolveMonsterEvent(card);
    rollDice(card);
    dracula.move(heroes , villagers);
    invisibleMan.move(heroes , villagers);

}

void Game::resolveMonsterEvent(const MonsterCard& card) {
    // To be implemented based on full MonsterCard effect logic
    MonsterCardType cardType = card.getType();

    switch(cardType)
    {

        case FormOfTheBat :

            gameMap.setPlayerPosition("Dracula", currentHero->getLocationHero());
            return;

        case Sunrise :

            gameMap.setPlayerPosition("Dracula", "crypt");
            return;

        case Thief :

            
            return;
 
        case TheDelivery :

            villagerManager.addVillager("Wilbur & Chick","docks", "percinct");
            return;
 
        case FortuneTeller :

            villagerManager.addVillager("Maleva","camp", "shop");
            return;
 
        case FormerEmployer :
            villagerManager.addVillager("Dr.crunly","laboratory", "percinct");

            return;
 
        case HurriedAssistant :

            villagerManager.addVillager("Fritz","tower", "institute");
            return;
 
        case TheInnocent :

            villagerManager.addVillager("Maria","barn", "camp");
            return;

        case EgyptianExpert :

            villagerManager.addVillager("Prof.pearson","cave", "museum");
            return;
 
        case TheIchthyologist :

            villagerManager.addVillager("Dr.read","institute", "camp");
            return;
         
    }
}

void Game::rollDice(const MonsterCard& card) {
    int diceCount = card.getDiceCount();
    std::vector<char> results;

    std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(0, 5);

    for (int i = 0; i < diceCount; ++i) {
        int roll = dist(rng);
        if (roll == 0) results.push_back('!');
        else if (roll == 1) results.push_back('*');
    }

    for (Monster* monster : card.getStrikeOrder()) {
        for (char symbol : results) {
            if (symbol == '!') monster->usePower(isMayorTurn ? mayor : archaeologist , heroes , villagers);
            else if (symbol == '*') {
                if (monster->getNameM() == "Dracula")
                    handleDraculaAttack();
                else if (monster->getNameM() == "Invisible Man")
                    handleInvisibleManAttack();
            }
        }
    }
}

bool Game::checkWinCondition() const {
    return dracula.isDead() && invisibleMan.isDead();
}

bool Game::checkLoseCondition() const {
    return terrorLevel >= 5 || monsterDeck.isEmpty();
}

void Game::increaseTerrorLevel() {
    if (++terrorLevel >= 5) {
        std::cout << "Terror has reached its peak!\n";
    }
}

void Game::handleDraculaAttack() {
    std::string currentLoc = gameMap.getPlayerPosition("Dracula");

    // بررسی قهرمان‌ها
    std::vector<Heroes*> heroesHere;
    if (gameMap.getPlayerPosition(mayor.getName()) == currentLoc)
        heroesHere.push_back(&mayor);
    if (gameMap.getPlayerPosition(archaeologist.getName()) == currentLoc)
        heroesHere.push_back(&archaeologist);

    for (Heroes* hero : heroesHere) {
        const auto& inventory = hero->getInventory();
        if (!inventory.empty()) {
            std::cout << "Dracula is attacking " << hero->getName() << "!\n";
            std::cout << hero->getName() << " has the following items:\n";
            for (size_t i = 0; i < inventory.size(); ++i) {
                std::cout << i + 1 << ". " << inventory[i]->getName() << "\n";
            }

            std::cout << "Do you want to discard an item to block the attack? (y/n): ";
            char answer;
            std::cin >> answer;

            if (answer == 'y' || answer == 'Y') {
                std::cout << "Enter the number of the item to discard: ";
                int itemChoice;
                std::cin >> itemChoice;

                if (itemChoice >= 1 && itemChoice <= (int)inventory.size()) {
                    Item* item = inventory[itemChoice - 1];
                    hero->removeFromInventory(item);
                    std::cout << hero->getName() << " used " << item->getName() << " to block the attack!\n";
                    return;  // حمله دفع شد
                } else {
                    std::cout << "Invalid choice. Attack proceeds.\n";
                }
            }
        }

        // اگر نخواست یا آیتم نداشت
        gameMap.setPlayerPosition(hero->getName(), "hospital");
        std::cout << "Dracula attacked " << hero->getName() << " and sent them to hospital!\n";
        increaseTerrorLevel();
        return;
    }

    // بررسی روستایی‌ها
    for (const auto& v : villagerManager.getActiveVillagers()) {
        const std::string& name = v.first;
        const std::string& location = v.second;

        if (location == currentLoc) {
            std::string nameCopy = name;
            villagerManager.removeVillager(nameCopy);
            std::cout << "Dracula killed villager " << name << "!\n";
            increaseTerrorLevel();
            return;
        }
    }

    std::cout << "Dracula attacked, but found no one.\n";
}

void Game::handleInvisibleManAttack() {
    std::string currentLoc = gameMap.getPlayerPosition("InvisibleMan");

    // بررسی روستایی‌ها
    for (const auto& v : villagerManager.getActiveVillagers()) {
        const std::string& name = v.first;
        const std::string& location = v.second;

        if (location == currentLoc) {
            std::string nameCopy = name;
            villagerManager.removeVillager(nameCopy);
            std::cout << "Dracula killed villager " << name << "!\n";
            increaseTerrorLevel();
            return;
        }
    }


    std::cout << "Dracula attacked, but found no one.\n";
}

void Game::handlePickUp(Heroes& hero) {
    while (true) {
        auto itemsHere = gameMap.getItemsAt(hero.getLocationHero());

        if (itemsHere.empty()) {
            std::cout << "There are no more items at this location.\n";
            return;
        }

        std::cout << "Items at this location:\n";
        for (size_t i = 0; i < itemsHere.size(); ++i) {
            std::cout << i + 1 << ". " << itemsHere[i]->getName() << "\n";
        }

        std::cout << "Enter item number to pick up (or 0 to stop): ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Finished picking up items.\n";
            break;
        }

        if (choice >= 1 && choice <= (int)itemsHere.size()) {
            Item* selected = itemsHere[choice - 1];
            hero.pickUp(selected);
            gameMap.removePlayer(selected->getName());  // حذف از map
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}




void Game::run() {

    initializeGame();
    std::cout << "\n=== DEBUG: Items in camp ===\n";
for (Item* item : gameMap.getItemsAt("camp")) {
    std::cout << "- " << item->getName() << "\n";
}

    startGameLoop();

}

