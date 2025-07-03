#if !defined(VILLAGERS_H)
#define VILLAGERS_H
#include "Hero.hpp"
#include <utility>
#include <vector>

class Map;

enum class NameVillagers{
    Dr_crunly, Maleva, 
    Fritz, Maria, 
    Prof_pearson, Dr_read
};


class Villager {
private:

    static std::vector<std::tuple<std::string, std::string, std::string>> nameAndsafeLocationVilager;
    std::string safeLocationVillager;
    std::string nameVillager;
    Map& locationVillager;

public:

    Villager(Map&);
    
    void setNameVillager(const std::string&);

    std::string getNameVillager() const;
    std::string getLocationVillager() const;
    std::string getSafeLocationVillager() const;

    void addVillager(const std::string, const std::string, const std::string);
    void initializeVillagers(const NameVillagers);
    void removeVillager(const std::string&);
    void chekSafeLocationVillager(const std::string);
    
    static void updateVillager(const std::string&, const std::string&);
    static std::vector<std::string> moveLocation(const std::string);
    static std::string guideVillager(std::vector<std::string>);


    std::vector<std::pair<std::string, std::string>> getActiveVillagers() const;

};


#endif // VILLAGERS_H
