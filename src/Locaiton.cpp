#include "../include/Location.hpp"
#include "../include/Item.hpp"
Location::Location(const NameLocation nameLocaiton) {
    this->nameLocation = nameLocaiton;
}

const NameLocation Location::getNameLocation() const {
    return this->nameLocation;
}
const std::vector<NameHeroes> Location::getNameHeroes() const {
    return this->heroes;
}
const std::vector<NameMonster> Location::getNameMonsters() const {
    return this->monsters;
}
const std::vector<NameItem> Location::getNameItems() const {
    return this->items;
}
const std::vector<NameVillagers> Location::getNameVillagers() const {
    return this->villagers;
}
const std::vector<Location*>& Location::getNeighbors() const {
    return neighbors;
}

void Location::addNeighbor(Location* neighbor) {
    neighbors.push_back(neighbor);
}
void Location::addHeroes(const NameHeroes& nameHeroes) {
    heroes.push_back(nameHeroes);
}

void Location::addMonsters(const NameMonster& nameMonsters) {
    monsters.push_back(nameMonsters);
}
void Location::addItem(const NameItem& nameItems) {
    if(std::find(items.begin(), items.end(), nameItems) == items.end()) {
        items.push_back(nameItems);
    }

}
void Location::addVillagers(const NameVillagers& nameVillagers) {
    villagers.push_back(nameVillagers);
}

void Location::removeHeroes(const NameHeroes& nameHeroes) {
    auto chek = std::find(heroes.begin(), heroes.end(), nameHeroes);
    if (chek != heroes.end()) {
        heroes.erase(chek);
    }
    else {
        throw std::invalid_argument("The hero you are looking for could not be found");
    }
}
void Location::removeMonsters(const NameMonster& nameMonsters) {
    auto chek = std::find(monsters.begin(), monsters.end(), nameMonsters);
    if(chek != monsters.end()) {
        monsters.erase(chek);
    }
    else {
        throw std::invalid_argument("The monster you are looking for could not be found");
    }
}
void Location::removeItem(const NameItem& nameItem) {
    auto chek = std::find(items.begin(), items.end(), nameItem);
    if(chek != items.end()) {
        items.erase(chek);
    }
    else {
        throw std::invalid_argument("The item you are looking for could not be found");
    }
}
void Location::removeVillagers(const NameVillagers& nameVillagers) {
    auto chek = std::find(villagers.begin(), villagers.end(), nameVillagers);
    if(chek != villagers.end()) {
        villagers.erase(chek);
    }
    else {
        throw std::invalid_argument("The villager you are looking for could not be found");
    }
}