#include "Hero.hpp"
#include "Villagers.hpp"
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

    std::vector<std::string> neighborsHero;

    auto neighbors = current->getNeighbors();
    for(auto& loc : neighbors) {
        neighborsHero.push_back(loc->getName());
    }

    std::string nameVillager = Villager::guideVillager(neighborsHero);
    locationHero.setPlayerPosition(nameVillager, getLocationHero());


}
void Heroes::pickUp() {
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