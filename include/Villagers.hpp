#if !defined(VILLAGERS_H)
#define VILLAGERS_H
#include "Hero.hpp"
#include "Map.hpp"
#include <utility> // برای std::pair
#include <vector>
class Villager {
private:
    // Status statusVillager;
    std::string nameVillager;
    std::string safeLocationVillager;
    Map& locationVillager;
    static std::vector<std::pair<std::string, std::string>> nameAndsafeLocationVilager;
public:
    Villager(Map&);
    Villager(std::string, std::string, Map&);
    
    void setNameVillager(const std::string&);
    // void setStatusVillager(const Status&);
    // void setLocationVillager(const Map&);

    std::string getNameVillager() const;
    // Status getStatusVillager() const;
    std::string getLocationVillager() const;
    std::string getSafeLocationVillager() const;
    void addVillager(std::string, std::string, std::string);
    void initializeVillagers();
    void removeVillager(std::string&);
    void chekSafeLocationVillager(std::string);

    static std::vector<std::string> moveLocation(std::string);

};


#endif // VILLAGERS_H
