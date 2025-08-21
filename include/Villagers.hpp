#pragma once

#include <vector>
#include "Map.hpp"
#include "NameEnum.hpp"

enum class NameLocation;
class Map;

class Villager {
private:

    NameVillagers nameVillager;
    NameLocation safeLocationVillager;
    NameLocation nameLocationVillagers;
    Map& locationVillager;
    void addVillager(const NameVillagers&, const NameLocation&, const NameLocation&);
    static std::vector<std::pair<NameVillagers, Villager>> villagers;
public:
    
    Villager(Map&);
    Villager(Map&,const NameLocation&, const NameVillagers&, const NameLocation&);
    void setVillagersPosition(const NameLocation&);
    void setVillagersPosition(const NameVillagers&, const NameLocation);
    NameVillagers chengNameVillager(const std::string&);
    NameVillagers getNameVillager() const;
    NameLocation getLocationVillager() const;
    NameLocation getSafeLocationVillager() const;

    void initializeVillagers(const NameVillagers&);
    void removeVillager(const NameVillagers&);
    void chekSafeLocationVillager(const NameVillagers&);
    
    std::string chengNameVillagerTheString(const NameVillagers&);
    std::vector<NameVillagers> moveLocation(const NameLocation&);
    NameVillagers guideVillager(std::vector<NameLocation>);
};