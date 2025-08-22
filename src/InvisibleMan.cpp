#include "InvisibleMan.hpp"
#include <climits>


InvisibleMan::InvisibleMan(Map& map) : Monster(NameMonster::INVISIBLE_MAN, map, NameLocation::GRAVEYARD){}


bool InvisibleMan::moveMonster(Villager& villager, Heroes& hero1, Heroes& hero2, Heroes& hero3, Heroes& hero4, bool w) {
   
    std::vector<std::pair<NameLocation, int>> targets;
   
    for(auto& v : villager.getVillagers()) {
        if(v.second.getLocationVillager() == getNameLocationMonster()) {
            if(w && chek) {
                v.second.removeVillager(v.second.getNameVillager());
                this->chek = false;
            }
            return true;
        } 
            targets.emplace_back(v.second.getLocationVillager(), 0);
    }

    if(villager.getVillagers().empty()) {
        std::cerr << "not found viilager";
        return false;
    }

    int minDist = INT_MAX;

    for(auto& [name, number] : targets) {
        try {
            number = getLocationMonster().findShortestPath<int>(getNameLocationMonster(), name);
            if(number < minDist) {
                minDist = number;
            }
        } catch(...) {
        }
    }
    for(auto& [name, number] : targets) {
        if(number == minDist) {
            this->setMonsterPosition(getLocationMonster().findShortestPath<NameLocation>(getNameLocationMonster(), name));
            if(this->getNameLocationMonster() == name) {
                this->chek = true;
                return true;
            }
            return false;
        }
    }

    throw std::invalid_argument("error move Invisible man");
}
