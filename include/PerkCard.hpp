#if !defined(PERK_CARD_H)
#define PERK_CARD_H
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
// #include "Hero.hpp"

class Heroes;
class Dracula;
class InvisibleMan;

enum class PerkCardType{
    VisitFromDetective,
    BreakOfDawn,
    Overstock,
    LateIntoTheNight,
    Repel,
    Hurry
};

class PerkCard {
private:
    PerkCardType perkType;
    std::string description;
public:
    PerkCard(PerkCardType,const std::string&);
    friend std::ostream& operator<<(std::ostream&, const PerkCard&);
    PerkCardType getType() const;
    std::string getDescription() const;
};

class PerkDeck {
    // friend class Hero;
private:
    static std::vector<PerkCard> cards;
    static std::vector<PerkCard> inGameCards;
public:
    // PerkDeck();
    static void initializeDeck();
    static void addCard(PerkCardType, const std::string, int);
    static void shuffleDeck();
    static PerkCard drawCard();
    static bool isEmpty();
    static std::vector<PerkCard> getInGamePerkCards();

    static void visitFormTheDetective();
    static void breakOfDawn();
    static void overstock();
    static void lateIntoTheNight();
    static void Repel(Dracula&, InvisibleMan&);
    static void Hurry(Heroes&, Heroes&);


};

#endif // PERK_CARD_H