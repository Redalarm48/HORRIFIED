#include "Monster.hpp"

Monster::Monster(const std:: string& name , int frenzyorder) : Name(name) , FrenzyOrder(frenzyorder) , position(0 , 0) , Dead(false) {}

Monster::~Monster(){

}

std::string Monster::getName() const
{

    return Name;

}

int Monster::getFrenzyOrder() const
{

    return FrenzyOrder;

}

Position Monster::getPosition() const{

    return position;

}

bool Monster::isDead() const
{

    return Dead;

}

void Monster::setPosition(const Position& newPos)
{

    position = newPos;

}

void Monster::Defeated()
{

    Dead = true;

}

void Monster::usePower() {

}

void Monster::move(const Position& target) {

}

void Monster::attack() {

}

void Monster::applyItem(const std::vector<Item>& items) {

}