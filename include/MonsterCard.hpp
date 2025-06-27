#ifndef MONSTERCARD_HPP
#define MONSTERCARD_HPP

#include <string>
#include <vector>
#include "Monster.hpp"

enum MonsterCardType {
    FormOfTheBat,
    Sunrise,
    Thief,
    TheDelivery,
    FortuneTeller,
    FormerEmployer,
    HurriedAssistant,
    TheInnocent,
    EgyptianExpert,
    TheIchthyologist
};

class MonsterCard {
private:
    MonsterCardType type;
    std::string description;
    int diceCount;
    std::vector<Monster*> strikeOrder;

public:
    MonsterCard(MonsterCardType type, const std::string& description, int diceCount = 0, const std::vector<Monster*>& strikeOrder = {});

    const std::string& getDescription() const;
    int getDiceCount() const;
    const std::vector<Monster*>& getStrikeOrder() const;
    MonsterCardType getType() const;
};

class MonsterDeck {
private:
    std::vector<MonsterCard> cards;
    Monster* dracula;
    Monster* invisibleMan;
    Monster* frenzied;

    void addCard(MonsterCardType type, const std::string& desc, int diceCount, const std::vector<Monster*>& strikeOrder, int count);
    void shuffleDeck();

public:
    MonsterDeck(Monster* dracula, Monster* invisibleMan, Monster* frenzied);

    void initializeDeck();
    MonsterCard drawCard();
    bool isEmpty() const;

};

#endif
