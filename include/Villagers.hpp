#pragma once

#include <vector>
#include <list>
#include "Map.hpp"
#include "NameEnum.hpp"

enum class NameLocation;
class Map;
class PerkDeck;

class Villager {
private:

    NameVillagers nameVillager;
    NameLocation safeLocationVillager;
    NameLocation nameLocationVillagers;
    Map& locationVillager;
    PerkDeck& perkDeck;
    void addVillager(const NameVillagers&, const NameLocation&, const NameLocation&);
    static std::list<std::pair<NameVillagers, Villager>> villagers;
public:
    
    Villager(Map&, PerkDeck&); 
    Villager(Map&, PerkDeck&, const NameLocation&, const NameVillagers&, const NameLocation&);
    void setVillagersPosition(const NameLocation&);
    void setVillagersPosition(const NameVillagers&, const NameLocation, Heroes&);
    NameVillagers chengNameVillager(const std::string&);
    NameVillagers getNameVillager() const;
    NameLocation getLocationVillager() const;
    NameLocation getSafeLocationVillager() const;
    std::list<std::pair<NameVillagers, Villager>> getVillagers() const;


    void initializeVillagers(const NameVillagers&);
    void removeVillager(const NameVillagers&);
    void chekSafeLocationVillager(const NameVillagers&, Heroes&);
    
    std::string chengNameVillagerTheString(const NameVillagers&);
    std::vector<NameVillagers> moveLocation(const NameLocation&);
    NameVillagers guideVillager(std::vector<NameLocation>);
};