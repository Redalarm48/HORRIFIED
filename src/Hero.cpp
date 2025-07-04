#include "Hero.hpp"
#include <unordered_set>
#include "Villagers.hpp"
#include "Game.hpp"
Heroes::Heroes(int maxAction, const std::string nameHero, Map& locationHero)  : nameHero(nameHero), statusHero(Status::Alive), locationHero(locationHero),
    numberActionTaken(0), maxActions(maxAction) {
        // perkCard.drawCard();
    }


Location* Heroes::getLocationHeroPtr () const {
    return this->locationHero.getPlayerPositionPtr(nameHero);    
}
std::string Heroes::getLocationHero() const {
    return this->locationHero.getPlayerPosition(nameHero);
}

bool Heroes::canTakeAction() const {
    return this->numberActionTaken < this->maxActions;
}

void Heroes::resetActions() {
    numberActionTaken = 0;
}


void Heroes::incrementAction() {
    ++numberActionTaken;
    
}

void Heroes::decreaseAction() {
    numberActionTaken-=2;
    if(numberActionTaken < 0)
        numberActionTaken = 0;
    
}

int Heroes::getNumberActionTaken() const {
    return numberActionTaken;
    
}



void Heroes::move(bool skipVillager) {

    if(!canTakeAction()) {
        std::cout << "No actions left.\n";
        return;
    }

    auto current = getLocationHeroPtr();

    if(!current) {
        std::cout << "Heo location unknwon";
        return;
    }

    std::vector<std::string> villagerMove;
    
    if(!skipVillager) {   
        villagerMove = Villager::moveLocation(getLocationHero());
    }
        
    auto neighbors = current->getNeighbors();

    for(size_t i = 0; i < neighbors.size(); ++i) {
        std::cout << i+1 << "." << neighbors[i]->getName() << "\n";
    }

    std::string newLocation;
    std::cout << "choose a location to move to (number): ";
    bool trueOrfalse = true;
    while (trueOrfalse)
    {
        std::cin >> newLocation;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            if(newLocation == neighbors[i]->getName()) {
                trueOrfalse = false;
                break;
            }
        }

        if(trueOrfalse) {
            std::cout << "Please enter the correct location name: ";

        }

        
    }
    

    locationHero.setPlayerPosition(nameHero, newLocation);

    std::cout << nameHero << " moved to " << newLocation << ".\n";

    if(!villagerMove.empty()) {
        for(auto& i : villagerMove) {
            Villager::updateVillager(i, newLocation);
            locationHero.setPlayerPosition(i, newLocation);
            std::cout << i << ", ";        
        }

        std::cout << "moved to " << newLocation << ".\n";
    }

    incrementAction();
}


void Heroes::guide() {  

    if(!canTakeAction()) {
        std::cout << "No actions left.\n";
        return;
    }

    auto current = getLocationHeroPtr();
    
    if(!current) {
        std::cout << "Hero location unknown.\n";
        return;
    }

    std::vector<std::string> neighborsHero;

    auto neighbors = current->getNeighbors();

    for(auto& loc : neighbors) {
        neighborsHero.push_back(loc->getName());
    }

    std::string nameVillager = Villager::guideVillager(neighborsHero);

    locationHero.setPlayerPosition(nameVillager, getLocationHero());

    incrementAction();

}

void Heroes::pickUp(Item* item) {
    inventory.push_back(item);

    incrementAction();
    
}

void Heroes::increaseActionMax()
{

    maxActions =+ 2;

}

int Heroes::getMaxAction()const
{

    return maxActions;

}


void Heroes::Advance(Game& game) {
    // بررسی کن که همه مکان‌ها حداقل یک آیتم ازشون جمع شده
    for (const auto& entry : this->getInvisibleItemCollected()) {
        if (!entry.second) {
            std::cout << "You must collect at least one item from all 5 required locations before advancing.\n";
            return;
        }
    }

    // حالا ۵ آیتم با مکان‌های متفاوت رو پیدا کن و حذفشون کن
    std::unordered_set<std::string> usedLocations;
    std::vector<Item*> itemsToRemove;

    for (Item* item : this->getInventory()) {
        std::string loc = item->getPickedUpFrom();
        if (this->getInvisibleItemCollected().count(loc) && !usedLocations.count(loc)) {
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
        this->removeFromInventory(item);
        game.returnItemToBag(item);
    }
    
    game.setInvisibleAdvanceDone(true);
    std::cout << "You successfully performed the advance action for Invisible Man.\n";


    incrementAction();
    
}
void Heroes::defeat() {
    

    incrementAction();
    
}
Archaeologist::Archaeologist(Map& map) : Heroes(4, "Archaeologist", map) {}

Mayor::Mayor(Map& map) : Heroes(5, "Mayor", map) {}

void Archaeologist::specialAction(Map& map) {

        std::string currentLoc = getLocationHero();
    std::vector<Item*> allItems;
    std::vector<std::string> itemSources; // برای اینکه بدونیم هر آیتم از کدوم خونه اومده

    // آیتم‌های خانه‌ی فعلی
    auto itemsHere = map.getItemsAt(currentLoc);
    for (auto& item : itemsHere) {
        allItems.push_back(item);
        itemSources.push_back(currentLoc);
    }

    // آیتم‌های خانه‌های همسایه
    auto neighbors = map.getNeighbors(currentLoc);
    for (const auto& neighbor : neighbors) {
        auto items = map.getItemsAt(neighbor);
        for (auto& item : items) {
            allItems.push_back(item);
            itemSources.push_back(neighbor);
        }
    }

    if (allItems.empty()) {
        std::cout << "There are no items at this location or neighboring locations.\n";
        return;
    }

    while (true) {
        std::cout << "Items available to pick up (from current and neighboring locations):\n";
        for (size_t i = 0; i < allItems.size(); ++i) {
            std::cout << i + 1 << ". " << allItems[i]->getName() 
                      << " (at " << itemSources[i] << ")\n";
        }

        std::cout << "Enter item number to pick up (or 0 to stop): ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Finished picking up items.\n";
            break;
        }

        if (choice >= 1 && choice <= (int)allItems.size()) {
            auto selected = allItems[choice - 1];
            std::string fromLocation = itemSources[choice - 1];

            pickUp(selected);
            selected->setPickedUpFrom(fromLocation);

            if (getInvisibleItemCollected().count(fromLocation)) {
                getInvisibleItemCollected()[fromLocation] = true;
            }

            map.removePlayer(selected->getName());
            // بعد از برداشتن، از لیست حذف کن تا دوباره نشون داده نشه
            allItems.erase(allItems.begin() + (choice - 1));
            itemSources.erase(itemSources.begin() + (choice - 1));
        } else {
            std::cout << "Invalid choice.\n";
        }

        if (allItems.empty()) {
            std::cout << "No more items to pick up.\n";
            break;
        }
    }

    incrementAction();

}

std::string Heroes::getName() const {
    return this->nameHero;
}

void Heroes::showInventory() const {
    std::cout << getName() << "'s Inventory:\n";
    for (const auto& item : inventory) {
        std::string color;
        switch (item->getType()) {
            case itemType::RED:
                color = "Red";
                break;
            case itemType::BLUE:
                color = "Blue";
                break;
            case itemType::YELLOW:
                color = "Yellow";
                break;
            default:
                color = "Unknown";
        }
        std::cout << "- " << item->getName() << " (" << color << ")\n";
    }
}

void Heroes::removeFromInventory(Item* item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}


std::vector<Item*> Heroes::getInventory(){
    return inventory;
}

std::vector<PerkCard> Heroes::getInGamePerkCards() {
    
    return perkCard.getInGamePerkCards();
}

void Heroes::setLocation(const std::string& nameHero, const std::string& locationHero) {
    this->locationHero.setPlayerPosition(nameHero, locationHero);
}

bool Heroes::removeItems(itemType type, int count) {
    int removed = 0;
    for (auto it = inventory.begin(); it != inventory.end() && removed < count; ) {
        if ((*it)->getType() == type) {
        removeFromInventory(*it);
        removed++;
        it = inventory.begin();
        }
        else 
        {
            ++it;       
        }
        
    }
    return removed == count;
    
}

bool Heroes::hasItems(itemType type, int count) const {
    int found = 0;
    for (Item* item : inventory) {
        if (item->getType() == type) {
            ++found;
            if (found >= count) return true;
        }
    }
    return false;
}
void Heroes::addPerkCard(const PerkCard& card) {
    perkCards.push_back(card);
}

void Heroes::usePerkCard(int index) {
    if (index >= 0 && index < (int)perkCards.size()) {
        perkCards.erase(perkCards.begin() + index);
    }
}

void Heroes::removePerkCard(int index) {
    if (index >= 0 && index < perkCards.size()) {
        perkCards.erase(perkCards.begin() + index);
    }
}

const std::vector<PerkCard>& Heroes::getPerkCards() const {
    return perkCards;
}

std::unordered_map<std::string, bool>& Heroes::getInvisibleItemCollected()
{

    return invisibleItemCollected;

}


std::unordered_map<std::string, bool>& Heroes::getcoffinDestroyed()
{

    return coffinDestroyed;

}


void Heroes::handlePickUp(Map& map) {
    while (true) {
        auto itemsHere = map.getItemsAt(getLocationHero());

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
            pickUp(selected);
            selected->setPickedUpFrom(getLocationHero());
            std::string from = selected->getPickedUpFrom();
            if (invisibleItemCollected.count(from)) {
                invisibleItemCollected[from] = true;
            }

            map.removePlayer(selected->getName());
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void Heroes::setNumberActionTaken(int num)
{

    numberActionTaken = num;

}

std::unordered_map<std::string, bool> Heroes::invisibleItemCollected{
    {"inn", false},
    {"barn", false},
    {"institute", false},
    {"laboratory", false},
    {"mansion", false}
};

std::unordered_map<std::string, bool> Heroes::coffinDestroyed{
        {"cave", false},
        {"crypt", false},
        {"dungeon", false},
        {"graveyard", false}
};

void Heroes::showCoffinStatus() 
{

    std::cout << "\nCoffins Status:\n";
    for (const auto& pair : coffinDestroyed) 
    {

        std::cout << " - " << pair.first << ": " << (pair.second ? "Destroyed" : " Not Destroyed") << "\n";
        
    }

}


void Heroes::handleAdvanceCoffin(const std::string& location) {
    defeat();

    if (getcoffinDestroyed()[location]) {
        std::cout << "This coffin is already destroyed.\n";
        return;
    }

    if (!hasItems(itemType::RED, 6)) {
        std::cout << "You need 6 red items to destroy a coffin.\n";
        return;
    }

    removeItems(itemType::RED, 6);
    getcoffinDestroyed()[location] = true;
    std::cout << "Coffin at " << location << " destroyed!\n";
}