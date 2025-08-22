#include "Monster.hpp"
#include "Games.hpp"
Monster::Monster(const NameMonster& nameMonster, Map& locationmonster, const NameLocation& newNameLocationMonster) : nameMonster(nameMonster), locationMonster(locationmonster){
     auto chek = std::find_if(locationmonster.map.begin(), locationmonster.map.end(), [&newNameLocationMonster](const auto& p) {
        return p.first == newNameLocationMonster;
        });
        if(chek != locationMonster.map.end()) {
            chek->second.addMonsters(nameMonster);
            nameLocationMonster = newNameLocationMonster;
        }
}

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

void Monster::removeMonster() {
    auto chek = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [this](const auto& p) {
        return p.first == this->nameLocationMonster;
    });
    if(chek == locationMonster.map.end()) {
        throw std::invalid_argument("");
    }
    chek->second.removeMonsters(nameMonster);
}

NameMonster Monster::getNameM() const {

    return nameMonster;
}

Map& Monster::getLocationMonster() const {
    return this->locationMonster;
}

DiceResult Monster::rollDice() {
    int r = rand() % 6;
    if(r < 2) return DiceResult::None;
    else if(r < 4) return DiceResult::Attack;
    else return DiceResult::Power;
}

NameMonster Monster::getFrenzyOrder() const {

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