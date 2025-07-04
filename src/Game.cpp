#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

Game::Game()
    : gameMap(Map::getInstance()),
      mayor(gameMap),
      archaeologist(gameMap),
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
        mayor.getcoffinDestroyed()[loc] = false;
    }

    perkDeck.initializeDeck();
    monsterDeck.initializeDeck();
    std::shuffle(Item::allItems.begin(), Item::allItems.end(), std::default_random_engine(std::random_device{}()));

    itemBag = Item::allItems;
    std::shuffle(itemBag.begin(), itemBag.end(), std::default_random_engine(std::random_device{}()));


    mayor.addPerkCard(perkDeck.drawCard());
    archaeologist.addPerkCard(perkDeck.drawCard());

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
        monsterPhaseTrue = true;
        currentHero = isMayorTurn ? static_cast<Heroes*>(&mayor) : static_cast<Heroes*>(&archaeologist);

        heroTurn(*currentHero);
        villagerManager.getLocationVillager();
        if(monsterPhaseTrue)
        {
            monsterPhase();
        }
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
    if(hero.getName() == "Mayor")
    {

        hero.setNumberActionTaken(0);

    }
    else
    {

        hero.setNumberActionTaken(0);

    }
    while (hero.canTakeAction()) {
        std::cout << "\n" << hero.getName() << " Turn. Actions left: " << (hero.getMaxAction() - hero.getNumberActionTaken()) << "\n";
        if(hero.getName() == "Mayor")
        {
            std::cout << "1. Move\n2. Guide Villager\n3. Pick Up Item\n4. Defeat Monster\n5. Show Inventory\n6. Advance\n7. Use Perk Card\n8. End Turn\n";
            gameMap.print();
            gameMap.printPlayers();
            hero.showCoffinStatus();
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1: 
                    hero.move(); 
                    break;
                case 2: 
                    hero.guide();       
                    break;
                case 3: 
                    hero.handlePickUp(gameMap);        
                    break;
                case 4: 
                    {
                    std::cout << "which monster you want to defeat ? (Dracula / InvisibleMan)";
                    std::string monstername;
                    std::cin >> monstername;
                    if(monstername == "Dracula")
                        handleDefeatDracula(&dracula , hero);   
                    else if(monstername == "InvisibleMan")
                        handleDefeatDracula(&invisibleMan , hero);  
                    hero.defeat(); 
                        break;
                    }
                case 5: 
                    hero.showInventory(); 
                    break;
                case 6: 
                    hero.handleAdvanceCoffin(hero.getLocationHero());
                    handleInvisibleManAttack();
                    break;
                case 7: {
                    const auto& perkCards = hero.getPerkCards();
                    if (perkCards.empty()) {
                        std::cout << "You don't have any Perk Cards!\n";
                        break;
                    }

                    std::cout << "Your Perk Cards:\n";
                    for (size_t i = 0; i < perkCards.size(); ++i) {
                        std::cout << i + 1 << ". " << perkCards[i] << " - " << perkCards[i].getDescription() << "\n";
                    }

                    std::cout << "Choose a card to use (0 to cancel): ";
                    int choice;
                    std::cin >> choice;

                    if (choice <= 0 || static_cast<size_t>(choice) > perkCards.size()) {
                        std::cout << "Cancelled using Perk Card.\n";
                        break;
                    }

                    PerkCard selected = perkCards[choice - 1];
                    hero.removePerkCard(choice - 1);  // remove the card after using it

                    switch (selected.getType()) {
                        case PerkCardType::VisitFromDetective:
                            PerkDeck::visitFormTheDetective();
                            break;

                        case PerkCardType::BreakOfDawn:
                            monsterPhaseTrue = false;
                            std::cout << "Monster phase will be skipped.\n";
                            placeRandomItemAt(hero.getLocationHero() , 2);
                            std::cout << "You received 2 random items at your location.\n";
                            break;

                        case PerkCardType::Overstock:
                            placeRandomItemAt(mayor.getLocationHero() , 1);
                            placeRandomItemAt(archaeologist.getLocationHero() , 1);
                            std::cout << "Each hero received 1 item at their locations.\n";
                            break;

                        case PerkCardType::LateIntoTheNight:
                            hero.increaseActionMax();
                            std::cout << "You received 2 extra actions this turn!\n";
                            break;

                        case PerkCardType::Repel:
                            PerkDeck::Repel(dracula, invisibleMan);
                            break;

                        case PerkCardType::Hurry:
                            PerkDeck::Hurry(mayor, archaeologist);
                            break;

                        default:
                            std::cout << "Unknown Perk Card.\n";
                            break;
                    }

                    break;
                }

                
                case 8: 
                    return;

                default: std::cout << "Invalid choice\n";
            }
        }
        else
        {
            std::cout << "1. Move\n2. Guide Villager\n3. Pick Up Item\n4. Defeat Monster\n5. Show Inventory\n6. Advance\n7. Use Perk Card\n8. Use SpecialAbillity\n9. End Turn\n";
            gameMap.print();
            gameMap.printPlayers();
            int choice;
            std::cin >> choice;
            switch (choice) {
                case 1: 
                    hero.move(); 
                    break;
                case 2: 
                    hero.guide();       
                    break;
                case 3: 
                    hero.handlePickUp(gameMap);        
                    break;
                case 4: 
                    {
                    std::cout << "which monster you want to defeat ? (Dracula / InvisibleMan)";
                    std::string monstername;
                    std::cin >> monstername;
                    if(monstername == "Dracula")
                        handleDefeatDracula(&dracula , hero);   
                    else if(monstername == "InvisibleMan")
                        handleDefeatDracula(&invisibleMan , hero);  
                    hero.defeat(); 
                        break;
                    }
                case 5: 
                    hero.showInventory(); 
                    break;
                case 6: 
                    hero.handleAdvanceCoffin(hero.getLocationHero());
                    handleInvisibleManAttack();
                    break;
                case 7: {
                    const auto& perkCards = hero.getPerkCards();
                    if (perkCards.empty()) {
                        std::cout << "You don't have any Perk Cards!\n";
                        break;
                    }

                    std::cout << "Your Perk Cards:\n";
                    for (size_t i = 0; i < perkCards.size(); ++i) {
                        std::cout << i + 1 << ". " << perkCards[i] << " - " << perkCards[i].getDescription() << "\n";
                    }

                    std::cout << "Choose a card to use (0 to cancel): ";
                    int choice;
                    std::cin >> choice;

                    if (choice <= 0 || static_cast<size_t>(choice) > perkCards.size()) {
                        std::cout << "Cancelled using Perk Card.\n";
                        break;
                    }

                    PerkCard selected = perkCards[choice - 1];
                    hero.removePerkCard(choice - 1);  // remove the card after using it

                    switch (selected.getType()) {
                        case PerkCardType::VisitFromDetective:
                            PerkDeck::visitFormTheDetective();
                            break;

                        case PerkCardType::BreakOfDawn:
                            monsterPhaseTrue = false;
                            std::cout << "Monster phase will be skipped.\n";
                            placeRandomItemAt(hero.getLocationHero() , 2);
                            std::cout << "You received 2 random items at your location.\n";
                            break;

                        case PerkCardType::Overstock:
                            placeRandomItemAt(mayor.getLocationHero() , 1);
                            placeRandomItemAt(archaeologist.getLocationHero() , 1);
                            std::cout << "Each hero received 1 item at their locations.\n";
                            break;

                        case PerkCardType::LateIntoTheNight:
                            hero.increaseActionMax();
                            std::cout << "You received 2 extra actions this turn!\n";
                            break;

                        case PerkCardType::Repel:
                            PerkDeck::Repel(dracula, invisibleMan);
                            break;

                        case PerkCardType::Hurry:
                            PerkDeck::Hurry(mayor, archaeologist);
                            break;

                        default:
                            std::cout << "Unknown Perk Card.\n";
                            break;
                    }

                    break;
                }

                case 8:

                    archaeologist.specialAction(gameMap);
                    archaeologist.incrementAction();
                    break;
                
                case 9: 
                    return;

                default: std::cout << "Invalid choice\n";
            }
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

}

void Game::resolveMonsterEvent(const MonsterCard& card) {

    MonsterCardType cardType = card.getType();

    switch(cardType)
    {

        case FormOfTheBat :

            if(!dracula.isDead())
                {gameMap.setPlayerPosition("Dracula", currentHero->getLocationHero());}
            placeRandomItem(2);
            if(!invisibleMan.isDead())
                {invisibleMan.move(heroes , villagers);}
            return;

        case Sunrise :
            if(!invisibleMan.isDead())
                {gameMap.setPlayerPosition("Dracula", "crypt");}
            
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}

            if(!invisibleMan.isDead())
                {invisibleMan.move(heroes , villagers);}
            return;

        case Thief: {
            std::string targetLocation = findLocationWithMostItems();
            if (!targetLocation.empty()) {
                if(!invisibleMan.isDead())
                    {gameMap.setPlayerPosition("InvisibleMan", targetLocation);}

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
            villagerManager.initializeVillagers(NameVillagers::WilnureAndChick);
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
            return;
 
        case FortuneTeller :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Maleva);
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
            return;
 
        case FormerEmployer :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Dr_crunly);
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
            if(!invisibleMan.isDead())
                {invisibleMan.move(heroes , villagers);}

            return;
 
        case HurriedAssistant :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Fritz);
            if(!dracula.isDead())
                {dracula.move(heroes , villagers);}
            return;
 
        case TheInnocent :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Maria);
            if(!invisibleMan.isDead())
                {invisibleMan.move(heroes , villagers);}
            if(!dracula.isDead())
                {dracula.move(heroes , villagers);}
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
            return;

        case EgyptianExpert :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Prof_pearson);
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
            if(!dracula.isDead())
                {dracula.move(heroes , villagers);}
            return;
 
        case TheIchthyologist :

            placeRandomItem(3);
            villagerManager.initializeVillagers(NameVillagers::Dr_read);
            if(!frenziedMonster->isDead())
                {frenziedMonster->move(heroes , villagers);}
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
            Heroes& activeHero = isMayorTurn ? static_cast<Heroes&>(mayor) : static_cast<Heroes&>(archaeologist);
            if (symbol == '!' && !monster->isDead())
            {
            std::cout << "the dice reveald [ ! ]\n";
            monster->usePower(activeHero, heroes, villagers);
            }

            else if (symbol == '*') 
            {
                std::cout << "the dice reveald [ * ]\n";
                if (monster->getNameM() == "Dracula" && !monster->isDead())
                    handleDraculaAttack();
                else if (monster->getNameM() == "Invisible Man" && !monster->isDead())
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


void Game::handleDefeatDracula(Monster* monster, Heroes& hero) {
    if (monster->getNameM() == "Dracula") {
        for (auto& entry : hero.getcoffinDestroyed()) {
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
        if(!invisibleMan.isDead())
        {

            frenziedMonster = &invisibleMan;

        }
        monster->Defeated();
        gameMap.removePlayer(monster->getNameM());
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
        gameMap.removePlayer(monster->getNameM());
        std::cout << "Invisible Man has been defeated!\n";
    }
    hero.defeat();
}

void Game::handleAdvanceInvisibleMan(Heroes& hero) {
    hero.Advance(*this);
  }

void Game::usePerkCard(Heroes& hero, const PerkCard& card) {
    switch (card.getType()) {
        case PerkCardType::VisitFromDetective: {
            perkDeck.visitFormTheDetective();
            pekrcardName = "VisitFromDetective";
            break;
        }
        case PerkCardType::BreakOfDawn: {
            perkDeck.breakOfDawn(hero, *this);
            pekrcardName = "BreakOfDawn";
            break;
        }
        case PerkCardType::Overstock: {
            perkDeck.overstock(*this, mayor, archaeologist);
            pekrcardName = "Overstock";
            break;
        }
        case PerkCardType::LateIntoTheNight: {
            perkDeck.lateIntoTheNight(hero);  // متدی در Hero بساز برای دادن اکشن اضافه
            pekrcardName = "LateIntoTheNight";
            break;
        }
        case PerkCardType::Repel: {
            perkDeck.Repel(dracula, invisibleMan);
            pekrcardName = "Repel";
            break;
        }
        case PerkCardType::Hurry: {
            perkDeck.Hurry(mayor, archaeologist);
            pekrcardName = "Hurry";
            break;
        }
    }
}

void Game::setMonsterPhaseTrue(bool value) {
    monsterPhaseTrue = value;
}

void Game::setInvisibleAdvanceDone(bool value) {
    invisibleAdvanceDone = value;
}



void Game::run() {

    initializeGame();
    startGameLoop();

}