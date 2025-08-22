#include <climits>
#include "Dracula.hpp"

Dracula::Dracula(Map& map) : Monster(NameMonster::DRACULA , map, NameLocation::CRYPT) {}


void Dracula::power(Villager& villager, Heroes& hero1, Heroes& hero2) {
    if(hero1.getLocationHero() != this->getNameLocationMonster()) {
        hero1.setHeroesPosition(this->getNameLocationMonster());
    }
    if(hero2.getLocationHero() != this->getNameLocationMonster()) {
        hero2.setHeroesPosition(this->getNameLocationMonster());
    }
}


bool Dracula::moveMonster(Villager& villager, Heroes& mayor, Heroes& archaeologist, Heroes& corier, Heroes& scientist, bool w) {
    if(getNameLocationMonster() == mayor.getLocationHero() ||
       getNameLocationMonster() == archaeologist.getLocationHero() ||
       getNameLocationMonster() == corier.getLocationHero() ||
       getNameLocationMonster() == scientist.getLocationHero()) {
        return true;
    }
    std::vector<std::pair<NameLocation, int>> targets;
   

    for(auto& v : villager.getVillagers()) {
        if(v.second.getLocationVillager() == getNameLocationMonster()) {
            return true;
        } 
            targets.emplace_back(v.second.getLocationVillager(), 0);
    }


    targets.emplace_back(mayor.getLocationHero(), 0);
    targets.emplace_back(archaeologist.getLocationHero(), 0);
    targets.emplace_back(corier.getLocationHero(), 0);
    targets.emplace_back(scientist.getLocationHero(), 0);
   
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
                return true;
            }
            return false;
        }
    }

    throw std::invalid_argument("error move dracula");

}

