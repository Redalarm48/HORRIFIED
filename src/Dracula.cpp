#include <climits>
#include "Dracula.hpp"

Dracula::Dracula(Map& map) : Monster(NameMonster::DRACULA , map, NameLocation::CAVE) {}


void Dracula::power(Villager& villager, Heroes& hero1, Heroes& hero2) {
    if(hero1.getLocationHero() != this->getNameLocationMonster()) {
        hero1.setHeroesPosition(this->getNameLocationMonster());
    }
    if(hero2.getLocationHero() != this->getNameLocationMonster()) {
        hero2.setHeroesPosition(this->getNameLocationMonster());
    }
}


