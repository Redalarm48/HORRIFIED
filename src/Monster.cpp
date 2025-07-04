#include "Monster.hpp"

Monster::Monster(const std:: string& name , int frenzyorder , Map& locationmonster) : Name(name) , FrenzyOrder(frenzyorder) , Dead(false) , locationMonster(locationmonster){}

Monster::~Monster(){

}

std::string Monster::getNameM() const
{

    return Name;

}

int Monster::getFrenzyOrder() const
{

    return FrenzyOrder;

}

bool Monster::isDead() const
{

    return Dead;

}


void Monster::Defeated()
{

    Dead = true;

}

Location* Monster::getLocationMonsterPtr() const
{

    return this->locationMonster.getPlayerPositionPtr(Name); 

}

std::string Monster::getLocationMonster() const 
{

    return this->locationMonster.getPlayerPosition(Name);

}

Map& Monster::getMap() const
{

    return locationMonster;

}

void Monster::usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) {

}

void Monster::move(const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) {

}

void Monster::attack() {

}

void Monster::applyItem(const std::vector<Item>& items) {

}