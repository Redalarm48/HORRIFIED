#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Map.hpp"
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
    TheIchthyologist,
    HypnoticGaze,
    OnTHeMove,
    Default
};

class Dracula;
class InvisibleMan;

class MonsterDeck {
private:
    int ItemCount;
    int diceCount;
    int moveCount;
    MonsterCardType monsterType;
    std::vector<NameMonster> striceOrder;
    static std::vector<MonsterDeck> cards;
    static std::vector<MonsterDeck> inGameCards;

    void addCard(const int, const int, const int, const int, const MonsterCardType&, const std::vector<NameMonster>&);
    
public:
    MonsterDeck(const int, const int, const int, const MonsterCardType&, const std::vector<NameMonster>&);
    MonsterDeck();
    void shuffleDeck();
    void formOfTheBat(Heroes&, Monster&, Item&);
    void sunrise(Monster&);
    void thief(Monster&, Item&);
    void theDelivery(Villager&);
    void fortuneTeller(Villager&);
    void formerEmployer(Villager&);
    void hurriedAssistant(Villager&);
    void theInnocent(Villager&);
    void egyptianExpert(Villager&);
    void theIchthyologist(Villager&);
    void initializeDeck();
    void playDrawCard(const MonsterCardType&, MonsterDeck&, Villager&, Heroes&, Heroes&, Heroes&, Heroes&, Dracula&, InvisibleMan&, Item&, Games*);
    MonsterDeck drawCard(Item&, Villager&, Heroes&, Heroes&, Heroes&, Heroes&, Dracula&, InvisibleMan&, Games*);
    bool isEmpty() const;
    MonsterCardType getTypeItem() const;

};