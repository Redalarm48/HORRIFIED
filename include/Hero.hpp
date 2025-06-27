#if !defined(HERO_H)
#define HERO_H
#include "PerkCard.hpp"
#include "Villagers.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include <string>
// #include "Villagers.hpp"
enum class Status{
    Alive,
    Dade
};

class Heroes {
private:
    std::string nameHero;
    Status statusHero;
    PerkDeck perkCard;
    Map& locationHero;
    int numberActionTaken;
    int maxActions;
    std::vector<Item*> inventory;


public:
    Heroes(int,const std::string, Map&);
    virtual ~Heroes() = default;

    std::string getName() const;
    Status getStatus() const;
    void setStatus(Status);

    Location* getLocationHeroPtr() const;
    std::string getLocationHero() const;
    bool canTakeAction() const;
    void resetActions();

    void move();
    void guide();
    void pickUp(Item* item);
    void Advance();
    void defeat();
    // virtual void specialAction() = 0;
    int getNumberActionTaken() const;
    void showInventory() const;
    void removeFromInventory(Item* item);
    std::vector<Item*> getInventory();


protected:
    void incrementAction();
};

class Archaeologist : public Heroes {
public:
    // Archaeologist(Map&);
    // void specialAction() override;
};

class Mayor : public Heroes {
public:
    // Mayor(Map&);
    // void specialAction() override;
};



#endif 
