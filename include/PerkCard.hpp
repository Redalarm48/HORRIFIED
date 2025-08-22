#pragma once

#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Hero.hpp"
#include "Map.hpp"
#include "Monster.hpp"

class Heroes;
class Monster;
class Game;
class Item;


enum class PerkCardType{
    VisitFromDetective,
    BreakOfDawn,
    Overstock,
    LateIntoTheNight,
    Repel,
    Hurry
};


class PerkDeck {
private:
    PerkCardType perkType;
    static std::vector<PerkDeck> cards;
    static std::vector<PerkDeck> inGameCards;

public:
    PerkDeck();
    PerkDeck(const PerkCardType& type) : perkType(type) {}

    PerkCardType getPerkType()const;
    void initializeDeck();
    void addCard(const PerkCardType&, const int&);
    void shuffleDeck();
    PerkDeck drawCard();
    bool isEmpty();
    std::vector<PerkDeck> getInGamePerkCards();
    void visitFormTheDetective(Monster&, const NameLocation&) const;
    void breakOfDawn(const Heroes&, Item&) const; 
    void overstock(const Heroes&, const Heroes&, Item&) const; 
    void lateIntoTheNight(Heroes&) const;
    bool Repel(Monster&, const NameLocation&) const;
    bool Hurry(Heroes&, const NameLocation&) const;


};
