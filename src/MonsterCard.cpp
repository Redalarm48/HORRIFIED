#include "..\include\MonsterCard.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>

MonsterCard::MonsterCard(MonsterCardType type, const std::string& description, int diceCount, const std::vector<Monster*>& strikeOrder)
    : type(type), description(description), diceCount(diceCount), strikeOrder(strikeOrder) {}

const std::string& MonsterCard::getDescription() const {
    return description;
}

int MonsterCard::getDiceCount() const {
    return diceCount;
}

const std::vector<Monster*>& MonsterCard::getStrikeOrder() const {
    return strikeOrder;
}

MonsterCardType MonsterCard::getType() const
{

    return this->type;

};

MonsterDeck::MonsterDeck(Monster* dracula, Monster* invisibleMan, Monster* frenzied)
    : dracula(dracula), invisibleMan(invisibleMan), frenzied(frenzied) {
    initializeDeck();
}

void MonsterDeck::addCard(MonsterCardType type, const std::string& desc, int diceCount, const std::vector<Monster*>& strikeOrder, int count) {
    for (int i = 0; i < count; ++i) {
        cards.emplace_back(type, desc, diceCount, strikeOrder);
    }
}

void MonsterDeck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

void MonsterDeck::initializeDeck() {
    addCard(MonsterCardType::FormOfTheBat, "Dracula moves to the latest hero position.", 2, { invisibleMan }, 3);
    addCard(MonsterCardType::Sunrise, "Dracula moves to Crypt.", 2, {frenzied , invisibleMan }, 3);
    addCard(MonsterCardType::Thief, "Invisible Man removes all items from the location with most items.", 3, { dracula , invisibleMan }, 5);
    addCard(MonsterCardType::TheDelivery, "Place Wilbur & Chick in Docks.", 3, { frenzied }, 1);
    addCard(MonsterCardType::FortuneTeller, "Place Maleva in Camp.", 2, { frenzied }, 1);
    addCard(MonsterCardType::FormerEmployer, "Place Dr. Crunly in Laboratory.", 2, { frenzied , invisibleMan }, 1);
    addCard(MonsterCardType::HurriedAssistant, "Place Fritz in Tower.", 3, { dracula }, 1);
    addCard(MonsterCardType::TheInnocent, "Place Maria in Barn.", 3, {invisibleMan, dracula, frenzied }, 1);
    addCard(MonsterCardType::EgyptianExpert, "Place Prof. Pearson in Cave.", 2, {frenzied , dracula  }, 1);
    addCard(MonsterCardType::TheIchthyologist, "Place Dr. Read in Institute.", 2, { frenzied }, 1);
    
    shuffleDeck();
}

MonsterCard MonsterDeck::drawCard() {
    if (cards.empty()) {
        throw std::runtime_error("No more Monster cards!");
    }
    MonsterCard card = cards.back();
    cards.pop_back();
    return card;
}

bool MonsterDeck::isEmpty() const {
    return cards.empty();
}

