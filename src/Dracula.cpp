#include "Dracula.hpp"

Dracula::Dracula(Map& map) : Monster("Dracula" , 1 , map) {}

void Dracula::usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers)
        {
            
            getMap().setPlayerPosition(h.getName() , getLocationMonster());
            std::cout << "Dracula Hypnotized someone , Last Hero in charge moves to the Dracula.\n";
            //باید آخرین قهرمان آخرین بازیکنی که بازی کرده منتقل بشه

        }

void Dracula::move(const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) {
    std::string currentPos = getMap().getPlayerPosition("Dracula");
    std::string closestTarget;
    int minDist = INT_MAX;


    for (const auto& hero : heroes) {
        std::string targetPos = getMap().getPlayerPosition(hero->getName());
        int dist = getMap().findShortestPath(currentPos, targetPos).size();
        if (dist < minDist && dist > 1) {
            minDist = dist;
            closestTarget = targetPos;
        }
    }


    for (const auto& villager : villagers) {
        std::string targetPos = getMap().getPlayerPosition(villager.first);
        int dist = getMap().findShortestPath(currentPos, targetPos).size();
        if (dist < minDist && dist > 1) {
            minDist = dist;
            closestTarget = targetPos;
        }
    }

    if (!closestTarget.empty()) {
        auto path = getMap().findShortestPath(currentPos, closestTarget);
        if (path.size() >= 2) {
            std::string nextStep = path;
            getMap().setPlayerPosition("Dracula", nextStep);
            std::cout << "Dracula" << " moved toward " << closestTarget << " to " << nextStep << "\n";
        }
    }
}

void Dracula::move() {

    auto current = getLocationMonsterPtr();
    if(!current) {
        std::cout << "Heo location unknwon";
        return;
    }
    // std::string n = "h";    

    std::cout << "Current location: " << current->getName() << "\nNeighbors: \n";
    
    auto neighbors = current->getNeighbors();
    for(size_t i = 0; i < neighbors.size(); ++i) {
        std::cout << i+1 << "." << neighbors[i]->getName() << "\n";
    }

    std::cout << "choose a location to move to (number): ";
    std::string newLocationHero;
    std::cin >> newLocationHero;

    // Location* newLocation = neighbors[newLocationHero - 1];
    getMap().setPlayerPosition("Dracula" , newLocationHero);
    std::cout << "Dracula" << " moved to " << newLocationHero << ".\n";

}


