
#if !defined(PERK_CARD_H)
#define PERK_CARD_H
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>

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
};

class PerkDeck {
private:
    static std::vector<PerkCard> cards;
public:
    // PerkDeck();
    static void initializeDeck();
    static void addCard(PerkCardType, const std::string, int);
    static void shuffleDeck();
    static PerkCard drawCard();
    static bool isEmpty();
};

#endif // PERK_CARD_H