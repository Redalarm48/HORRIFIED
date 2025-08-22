#pragma once
#include "PerkCard.hpp"
#include "Villagers.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "NameEnum.hpp"
#include <string>

enum class Status{
    Alive,
    Dade
};
class Map;
class Item;
class Location;
class Villager;

class Heroes {
private:

    const NameHeroes nameHero;
    NameLocation nameLocationHeroes;
    Map& locationHero;
    int numberActionTaken;
    int maxActions;
    Status statusHero;

    std::vector<std::pair<NameItem, NameLocation>> nameItemPickUpInvisibleMan;
    std::vector<PerkDeck> perkCards;
    
public:
    Heroes(int,const NameHeroes, Map&, const NameLocation&, PerkDeck&);
    virtual ~Heroes() = default;



    std::string getName() const;
    NameHeroes getNameHero() const;
    std::string changNameHeroesTheString(const NameHeroes&);
    std::vector<PerkDeck> getInGamePerkCards();
    std::vector<std::pair<NameItem, NameLocation>> getNameItemPickUpInvisibleMan() const;

    void setPerkCard(const PerkDeck&);

    NameLocation getLocationHero() const;
    bool canTakeAction() const;
    void resetActions();

    bool cheknumberDistance(const NameLocation&);


    void move(Villager&,const NameLocation&, bool, const std::vector<NameVillagers>&);
    void guide(Villager&, const NameVillagers&);
    void pickUp(Item&, const std::vector<NameItem>&);
    bool defieat(Monster&, Item&);


    int getNumberActionTaken() const;

    const std::vector<PerkDeck>& getPerkCards() const;
    void decreaseAction();


    void incrementAction();

    void setHeroesPosition(const NameLocation&);

};

class Archaeologist : public Heroes {
public:

    Archaeologist(Map&, PerkDeck&);

    void specialAction(Map&, const std::vector<Item*>& itemList);
};

class Mayor : public Heroes {
public:
    Mayor(Map&, PerkDeck&);
};

class Courier : public Heroes {
public:
    Courier(Map&, PerkDeck&);
};

class Scientist : public Heroes {
public:
    Scientist(Map&, PerkDeck&);
};