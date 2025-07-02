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
    for (const auto& loc : draculaCoffinLocations) 
    {
        coffinDestroyed[loc] = false;
    }

    perkDeck.initializeDeck();
    monsterDeck.initializeDeck();
    std::shuffle(Item::allItems.begin(), Item::allItems.end(), std::default_random_engine(std::random_device{}()));

    itemBag = Item::allItems;
    std::shuffle(itemBag.begin(), itemBag.end(), std::default_random_engine(std::random_device{}()));


    for (int i = 0; i < 12; ++i) {
        auto& item = getNextItem();
        std::string location = getRandomLocation();
        gameMap.setPlayerPosition(item.getName(), location);
    }

    frenziedMonster = &dracula;
    determineFirstPlayer();
}

void Game::determineFirstPlayer() {
    std::string mayorInput, archaeologistInput;

    std::cout << "Player controlling Mayor, when was your last meal? (hh:mm): ";
    std::cin >> mayorInput;

    std::cout << "Player controlling Archaeologist, when was your last meal? (hh:mm): ";
    std::cin >> archaeologistInput;

    // تبدیل به عدد دقیقه از 00:00 برای مقایسه
    auto parseTime = [](const std::string& timeStr) -> int {
        size_t colonPos = timeStr.find(':');
        if (colonPos == std::string::npos) return -1;

        int hours = std::stoi(timeStr.substr(0, colonPos));
        int minutes = std::stoi(timeStr.substr(colonPos + 1));

        return hours * 60 + minutes;
    };

    int mayorTime = parseTime(mayorInput);
    int archaeologistTime = parseTime(archaeologistInput);

    if (mayorTime == -1 || archaeologistTime == -1) {
        std::cout << "Invalid time format. Using default order (Mayor first).\n";
        isMayorTurn = true;
        return;
    }

    // هرکس دیرتر غذا خورده نوبت اول می‌گیرد
    isMayorTurn = (mayorTime > archaeologistTime);
}

Item& Game::getNextItem() {
    if (itemBag.empty()) {
        std::cout << "[Warning] Item bag is empty!\n";
        itemBag = Item::allItems;
        std::shuffle(itemBag.begin(), itemBag.end(), std::default_random_engine(std::random_device{}()));
    }

    Item* item = itemBag.back();
    itemBag.pop_back();  // از کیسه حذف میشه
    return *item;
}

void Game::returnItemToBag(Item* item) {
    itemBag.insert(itemBag.begin(), item);  // می‌تونی از اول یا آخر بذاری
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
        std::cout << "1. Move\n2. Guide Villager\n3. Pick Up Item\n4. Defeat Monster\n5. Show Inventory\n6. Advance\n7. End Turn\n";
        gameMap.print();
        gameMap.printPlayers();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: hero.move(); 
                    break;
            case 2: hero.guide(); 
                    break;
            case 3: handlePickUp(hero);
                    break;
            case 4: hero.defeat(); 
                    break;
            case 5: hero.showInventory(); 
                    break;
            case 6: handleAdvanceCoffin(hero.getLocationHero(), hero);
                    handleInvisibleManAttack();
                    break;
            case 7: return;

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

    MonsterCardType cardType = card.getType();

    switch(cardType)
    {

        case FormOfTheBat :

            gameMap.setPlayerPosition("Dracula", currentHero->getLocationHero());
            placeRandomItem(2);
            return;

        case Sunrise :

            gameMap.setPlayerPosition("Dracula", "crypt");
            return;

        case Thief: {
            std::string targetLocation = findLocationWithMostItems();
            if (!targetLocation.empty()) {
                gameMap.setPlayerPosition("InvisibleMan", targetLocation);

                // حذف همه آیتم‌های این مکان
                auto items = gameMap.getItemsAt(targetLocation);
                for (Item* item : items) {
                    gameMap.removePlayer(item->getName());
                    itemBag.push_back(item); // برگشت به کیسه آیتم‌ها
                }

                std::cout << "Invisible Man went to " << targetLocation << " and stole " << items.size() << " items!\n";
            } 
            else {
                std::cout << "No items on map for Invisible Man to steal.\n";
            }
            
            placeRandomItem(2);
            return;
        }
        
        case TheDelivery :

            placeRandomItem(3);
            villagerManager.addVillager("Wilbur & Chick","docks", "percinct");
            return;
 
        case FortuneTeller :

            placeRandomItem(3);
            villagerManager.addVillager("Maleva","camp", "shop");
            return;
 
        case FormerEmployer :

            placeRandomItem(3);
            villagerManager.addVillager("Dr.crunly","laboratory", "percinct");

            return;
 
        case HurriedAssistant :

            placeRandomItem(3);
            villagerManager.addVillager("Fritz","tower", "institute");
            return;
 
        case TheInnocent :

            placeRandomItem(3);
            villagerManager.addVillager("Maria","barn", "camp");
            return;

        case EgyptianExpert :

            placeRandomItem(3);
            villagerManager.addVillager("Prof.pearson","cave", "museum");
            return;
 
        case TheIchthyologist :

            placeRandomItem(3);
            villagerManager.addVillager("Dr.read","institute", "camp");
            return;
         
    }
}

void Game::placeRandomItem(int count) {
    for (int i = 0; i < count; ++i) {
        if (itemBag.empty()) {
            std::cout << "[Warning] Item bag is empty! Refilling...\n";
            itemBag = Item::allItems;
            std::shuffle(itemBag.begin(), itemBag.end(), std::default_random_engine(std::random_device{}()));
        }

        Item* item = itemBag.back();
        itemBag.pop_back();

        std::string location = getRandomLocation();
        gameMap.setPlayerPosition(item->getName(), location);

        std::cout << "[Info] Placed item " << item->getName() << " at " << location << "\n";
    }
}

void Game::placeRandomItemAt(const std::string& location, int count) {
    for (int i = 0; i < count; ++i) {
        if (itemBag.empty()) {
            itemBag = Item::allItems;
            std::shuffle(itemBag.begin(), itemBag.end(), std::default_random_engine(std::random_device{}()));
        }

        Item* item = itemBag.back();
        itemBag.pop_back();

        gameMap.setPlayerPosition(item->getName(), location);
        std::cout << "[Info] Placed item " << item->getName() << " at " << location << "\n";
    }
}

std::string Game::findLocationWithMostItems() const {
    const auto& allLocations = gameMap.getAllLocationNames();
    std::string maxLocation = "";
    size_t maxCount = 0;

    for (const std::string& loc : allLocations) {
        size_t count = gameMap.getItemsAt(loc).size();
        if (count > maxCount) {
            maxCount = count;
            maxLocation = loc;
        }
    }

    return maxLocation;
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
                    returnItemToBag(item);
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
            selected->setPickedUpFrom(hero.getLocationHero());
            std::string from = selected->getPickedUpFrom();
            if (invisibleItemCollected.count(from)) {
                invisibleItemCollected[from] = true;
            }

            gameMap.removePlayer(selected->getName());  // حذف از map
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void Game::handleAdvanceCoffin(const std::string& location, Heroes& hero) {
    hero.defeat();

    if (coffinDestroyed[location]) {
        std::cout << "This coffin is already destroyed.\n";
        return;
    }

    if (!hero.hasItems(itemType::RED, 6)) {
        std::cout << "You need 6 red items to destroy a coffin.\n";
        return;
    }

    hero.removeItems(itemType::RED, 6);
    coffinDestroyed[location] = true;
    std::cout << "Coffin at " << location << " destroyed!\n";
}

void Game::handleDefeatDracula(Monster* monster, Heroes& hero) {
    if (monster->getNameM() == "Dracula") {
        for (auto& entry : coffinDestroyed) {
            if (!entry.second) {
                std::cout << "You must destroy all Dracula's coffins first.\n";
                return;
            }
        }

        if (!hero.hasItems(itemType::YELLOW, 6)) {
            std::cout << "You need 6 yellow items to defeat Dracula.\n";
            return;
        }

        hero.removeItems(itemType::YELLOW, 6);
        monster->Defeated();
        std::cout << "Dracula has been defeated!\n";
    }
    if (monster->getNameM() == "Invisible Man") {
        if (!invisibleAdvanceDone) {
            std::cout << "You must perform the advance action before defeating Invisible Man.\n";
            return;
        }

        if (!hero.hasItems(itemType::RED, 9)) {
            std::cout << "You need 9 red items to defeat Invisible Man.\n";
            return;
        }

        hero.removeItems(itemType::RED, 9);
        monster->Defeated();
        std::cout << "Invisible Man has been defeated!\n";
    }

}

void Game::handleAdvanceInvisibleMan(Heroes& hero) {
    // بررسی کن که همه مکان‌ها حداقل یک آیتم ازشون جمع شده
    for (const auto& entry : invisibleItemCollected) {
        if (!entry.second) {
            std::cout << "You must collect at least one item from all 5 required locations before advancing.\n";
            return;
        }
    }

    // حالا ۵ آیتم با مکان‌های متفاوت رو پیدا کن و حذفشون کن
    std::unordered_set<std::string> usedLocations;
    std::vector<Item*> itemsToRemove;

    for (Item* item : hero.getInventory()) {
        std::string loc = item->getPickedUpFrom();
        if (invisibleItemCollected.count(loc) && !usedLocations.count(loc)) {
            usedLocations.insert(loc);
            itemsToRemove.push_back(item);
        }

        if (usedLocations.size() == 5) break;
    }

    if (usedLocations.size() < 5) {
        std::cout << "You do not have the correct 5 items from distinct locations.\n";
        return;
    }

    // حذف آیتم‌ها از اینونتوری
    for (Item* item : itemsToRemove) {
        hero.removeFromInventory(item);
        returnItemToBag(item);
    }

    invisibleAdvanceDone = true;
    std::cout << "You successfully performed the advance action for Invisible Man.\n";
}




void Game::run() {

    initializeGame();
    std::cout << "\n=== DEBUG: Items in camp ===\n";
for (Item* item : gameMap.getItemsAt("camp")) {
    std::cout << "- " << item->getName() << "\n";
}

    startGameLoop();

}

