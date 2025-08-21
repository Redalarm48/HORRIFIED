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

    std::vector<PerkDeck> perkCards;
    
public:
    Heroes(int,const NameHeroes, Map&, const NameLocation&);
    virtual ~Heroes() = default;

    std::string getName() const;
    NameHeroes getNameHero() const;
    std::string changNameHeroesTheString(const NameHeroes&);
    Status getStatus() const;
    std::vector<PerkDeck> getInGamePerkCards();

    NameLocation getLocationHero() const;
    bool canTakeAction() const;
    void resetActions();

    bool cheknumberDistance(const NameLocation&);


    void move(Villager&,const NameLocation&, bool);
    void guide(Villager&, const NameVillagers&);
    void pickUp(Item&, const std::vector<NameItem>&);

    int getNumberActionTaken() const;

    const std::vector<PerkDeck>& getPerkCards() const;
    void decreaseAction();

    void incrementAction();

    void setHeroesPosition(const NameLocation&);

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