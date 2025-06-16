#include "..\include\Monster.hpp"

Monster::Monster(const std:: string& name , int frenzyorder , Map& locationmonster) : Name(name) , FrenzyOrder(frenzyorder) , position(0 , 0) , Dead(false) , locationMonster(locationmonster){}

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