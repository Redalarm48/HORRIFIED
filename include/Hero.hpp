#if !defined(HERO_H)
#define HERO_H
#include "PerkCard.hpp"
#include "Villagers.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include <string>

enum class itemType;
enum class Status{
    Alive,
    Dade
};

class Map;
class Item;
enum class itemType;


class Heroes {
private:

    std::string nameHero;
    PerkDeck perkCard;
    Status statusHero;
    Map& locationHero;
    int numberActionTaken;
    int maxActions;
    std::vector<Item*> inventory;
    std::vector<PerkCard> perkCards;

    
    static std::unordered_map<std::string, bool> invisibleItemCollected;
    static std::unordered_map<std::string, bool> coffinDestroyed;

    
public:
    Heroes(int,const std::string, Map&);
    virtual ~Heroes() = default;

    std::string getName() const;
    Status getStatus() const;
    std::vector<PerkCard> getInGamePerkCards();
    void setLocation(const std::string&, const std::string&);

    Location* getLocationHeroPtr() const;
    std::string getLocationHero() const;
    bool canTakeAction() const;
    void resetActions();

    void move(bool = false);
    void guide();
    void pickUp(Item*);
    void Advance(Game&);
    void defeat();
    int getNumberActionTaken() const;
    void showInventory() const;
    void removeFromInventory(Item* item);
    std::vector<Item*> getInventory();
    bool removeItems(itemType type, int count);
    bool hasItems(itemType type, int count) const;
    void addPerkCard(const PerkCard& card);
    void usePerkCard(int index);
    const std::vector<PerkCard>& getPerkCards() const;
    void decreaseAction();
    void increaseActionMax();
    int getMaxAction()const;
    void removePerkCard(int index);


    static std::unordered_map<std::string, bool>& getInvisibleItemCollected();
    static std::unordered_map<std::string, bool>& getcoffinDestroyed();

    void handlePickUp( Map& map, const std::vector<Item*>& itemList);

    void setNumberActionTaken(int num);
    void incrementAction();
    void showCoffinStatus();
    void handleAdvanceCoffin(const std::string& location);

};

class Archaeologist : public Heroes {
public:
    Archaeologist(Map&);
    void specialAction(Map&, const std::vector<Item*>& itemList);
};

class Mayor : public Heroes {
public:
    Mayor(Map&);
};



#endif 