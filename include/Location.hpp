#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Monster.hpp"
#include "Hero.hpp"


class Location {

private:
    NameLocation nameLocation;
    
    std::vector<Location*> neighbors;

    std::vector<NameHeroes> heroes;
    std::vector<NameMonster> monsters;
    std::vector<NameVillagers> villagers;
    std::vector<NameItem> items;

public:
    Location(const NameLocation nameLocation);
    const NameLocation getNameLocation() const;
    const std::vector<NameHeroes> getNameHeroes() const;
    const std::vector<NameMonster> getNameMonsters() const;
    const std::vector<NameItem> getNameItems() const;
    const std::vector<NameVillagers> getNameVillagers() const;
    const std::vector<Location*>& getNeighbors() const;

    void addNeighbor(Location*);
    void addHeroes(const NameHeroes&);
    void addMonsters(const NameMonster&);
    void addItem(const NameItem&);
    void addVillagers(const NameVillagers&);

    void removeHeroes(const NameHeroes&);
    void removeMonsters(const NameMonster&);
    void removeItem(const NameItem&);
    void removeVillagers(const NameVillagers&);
};
