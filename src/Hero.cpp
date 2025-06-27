#include "..\include\Hero.hpp"
#include "..\include\Villagers.hpp"
Heroes::Heroes(int maxAction, const std::string nameHero, Map& locationHero)  : nameHero(nameHero), statusHero(Status::Alive), locationHero(locationHero),
    numberActionTaken(0), maxActions(maxAction) {}


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



void Heroes::move() {
    if(!canTakeAction()) {
        std::cout << "No actions left.\n";
        return;
    }
    auto current = getLocationHeroPtr();
    if(!current) {
        std::cout << "Heo location unknwon";
        return;
    }
    // std::string n = "h";

    std::vector<std::string> villagerMove = Villager::moveLocation(getLocationHero());
    

    std::cout << "Current location: " << current->getName() << "\nNeighbors: \n";
    
    auto neighbors = current->getNeighbors();
    for(size_t i = 0; i < neighbors.size(); ++i) {
        std::cout << i+1 << "." << neighbors[i]->getName() << "\n";
    }

    std::cout << "choose a location to move to (number): ";
    std::string newLocationHero;
    std::cin >> newLocationHero;

    // Location* newLocation = neighbors[newLocationHero - 1];
    locationHero.setPlayerPosition(nameHero, newLocationHero);
    std::cout << nameHero << " moved to " << newLocationHero << ".\n";

    if(!villagerMove.empty()) {

        for(auto& i : villagerMove) {
            locationHero.setPlayerPosition(i, newLocationHero);
            std::cout << i << ", ";        
        }
        std::cout << "moved to " << newLocationHero << ".\n";
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

    std::cout << "Villagers at current location:\n";
    // villager.printVillagerAtLocation(current->getName());

    std::cout << "Enter billager name to guide";


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

// Archaeologist::Archaeologist() : Heroes();

// Mayor::Mayor() : Heroes();

// void Archaeologist::specialAction() {

// }

std::string Heroes::getName() const {
    return this->nameHero;
}

void Heroes::showInventory() const {
    std::cout << getName() << "'s Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << "- " << item->getName() << "\n";
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