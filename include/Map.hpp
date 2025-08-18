#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Location.hpp"
// #include "../include/Item.hpp"
// #include "../include/Hero.hpp"
// #include "../include/Monster.hpp"
// #include "../include/Villagers.hpp"
// #include "../include/Item.hpp"

#include "../include/NameEnum.hpp"

#include <memory>

std::ostream& operator<<(std::ostream& os, NameLocation loc);

class Location;
enum class NameHeroes;
enum class NameMonster;
enum class NameVillagers;
enum class NameItem;

class Map {
private:
    void addLoation(const NameLocation&);
    void connectLocaiton(const NameLocation&, const NameLocation&);
    void totalLocation();
    void negiborLocation();
public:
    std::vector<std::pair<NameLocation, Location>> map;
    
    Map();
    Map(const Map&) = delete;
    Map operator =(const Map&) = delete;

    static Map& getInstance();

    std::vector<NameHeroes> getHeroesLocation(const NameLocation&) const;
    std::vector<NameMonster> getMonsterLocation(const NameLocation&) const;
    std::vector<NameItem> getItemsLocation(const NameLocation&) const;
    std::vector<NameVillagers> getVillagerLocaiton(const NameLocation&) const;
    std::vector<NameLocation> getNeighbors(const NameLocation&) const;
    std::vector<Location*> getNeighborLocation(const NameLocation&) const;

    NameLocation chengNameLocationTheString(const std::string&);

    // void setHeroesPosition(const std::string&);
    

    NameLocation findShortestPath(const NameLocation&, const NameLocation&);
    // bool isNeighbor(const std::string& from, const std::string& to) const;    static void setPlayerPosition(const std::string&, const std::string&);
    
    // std::string getPlayerPosition(const std::string&) const;
    // Location* getPlayerPositionPtr(const std::string&) const;
    // void printNeighbors();          
    // void print();
    // void printPlayers(const std::vector<Item*>& itemList) const;
    // void removePlayer(const std::string& name);
    // std::vector<Item*> getItemsAt(const std::string& location, const std::vector<Item*>& itemList) const;
    std::vector<NameLocation> getAllLocationNames() const; 


};

