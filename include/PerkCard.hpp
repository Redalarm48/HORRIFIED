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
class Game;

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
    static void addCard(PerkCardType, const std::string&, const int);
    static void shuffleDeck();
    static PerkCard drawCard();
    static bool isEmpty();
    static std::vector<PerkCard> getInGamePerkCards();

    static void visitFormTheDetective();
    static void breakOfDawn(Heroes&, Game&);
    static void overstock(Game&, Heroes&, Heroes&);
    static void lateIntoTheNight(Heroes&);
    static void Repel(Dracula&, InvisibleMan&);
    static void Hurry(Heroes&, Heroes&);


};

#endif // PERK_CARD_H