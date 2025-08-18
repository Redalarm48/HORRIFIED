#include "Monster.hpp"

Monster::Monster(const NameMonster nameMonster , int frenzyorder , Map& locationmonster) : nameMonster(nameMonster) , FrenzyOrder(frenzyorder) , Dead(false) , locationMonster(locationmonster){}

Monster::~Monster(){}

void Monster::setMonsterPosition(const NameLocation& newNameLocaitonMonster) {
    if(this->nameLocationMonster == newNameLocaitonMonster) {
        return;
    }
    auto chek = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [&newNameLocaitonMonster](const auto& p) {
        return p.first == newNameLocaitonMonster;
    });
    auto chek2 = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [this](const auto& p) {
        return p.first == nameLocationMonster;
    });
    if(chek != locationMonster.map.end() && chek2 != locationMonster.map.end()) {
        chek->second.addMonsters(nameMonster);
        chek2->second.removeMonsters(nameMonster);
        nameLocationMonster = newNameLocaitonMonster;
    }
    else {
        throw std::invalid_argument(" ");
    }
}


NameMonster Monster::getNameM() const {

    return nameMonster;
}

int Monster::getFrenzyOrder() const {

    return FrenzyOrder;
}

bool Monster::isDead() const{
    return Dead;
}


void Monster::Defeated(){
    Dead = true;
}

NameLocation Monster::getNameLocationMonster() const {
    return nameLocationMonster;
}

bool Monster::cheknumberDistance(const NameLocation& nameLocation) {
    return (
        this->locationMonster.findShortestPath((this->locationMonster.findShortestPath(this->nameLocationMonster, nameLocation)),nameLocation) == nameLocation
    );
}