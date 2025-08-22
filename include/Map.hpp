#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Location.hpp"
#include "NameEnum.hpp"

enum class PathMode { Distance, NextStep };

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


    bool getcoffinDestroyed() const;
    bool getInvisibleItemCollecte() const;

    std::vector<NameHeroes> getHeroesLocation(const NameLocation&) const;
    std::vector<NameMonster> getMonsterLocation(const NameLocation&) const;
    std::vector<NameItem> getItemsLocation(const NameLocation&) const;
    std::vector<NameVillagers> getVillagerLocaiton(const NameLocation&) const;
    std::vector<NameLocation> getNeighbors(const NameLocation&) const;
    std::vector<Location*> getNeighborLocation(const NameLocation&) const;

    NameLocation chengNameLocationTheString(const std::string&);
    std::string chengNameLocationTheString(const NameLocation&);
    
    template <class T>
    T findShortestPath(const NameLocation&, const NameLocation&);
    std::vector<NameLocation> getAllLocationNames() const; 



};

