#include "Hero.hpp"
#include "Villagers.hpp"
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

}

void Heroes::pickUp(Item* item) {
    inventory.push_back(item);
    ++this->numberActionTaken;

}



void Heroes::Advance() {
    ++this->numberActionTaken;

}
void Heroes::defeat() {
    ++this->numberActionTaken;

}
// void Heroes::specialAction() {
//     ++this->numberActionTaken;

// }

Archaeologist::Archaeologist(Map& map) : Heroes(4, "Archaeologist", map) {}

// Mayor::Mayor() : Heroes();
Mayor::Mayor(Map& map) : Heroes(5, "Mayor", map) {}
// void Archaeologist::specialAction() {

// }

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

void Heroes::showPerkCards() const {
    std::cout << "Perk Cards:\n";
    for (size_t i = 0; i < perkCards.size(); ++i) {
        std::cout << i + 1 << ". " << static_cast<int>(perkCards[i].getType()) << " - " << perkCards[i].getDescription() << "\n";
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

        // if(numberActionTaken > 5)
        // {
        //     break;
        // }

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

 // 
// std::unordered_map<std::string, bool> Heroes::getInvisibleItemCollected() {

//     return invisibleItemCollected;

// }
//         }
//     }
//     return false;
// }

// std::unordered_map<std::string, bool> Heroes::getInvisibleItemCollected()
// {

//     return invisibleItemCollected;

// }
