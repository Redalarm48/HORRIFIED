#include "PerkCard.hpp"
#include "InvisibleMan.hpp"
#include "Map.hpp"
#include "Hero.hpp"
#include "Dracula.hpp"
#include "Game.hpp"

PerkDeck::PerkDeck() {
    this->initializeDeck();
}

void PerkDeck::initializeDeck() {

    addCard(PerkCardType::VisitFromDetective, 3);
    addCard(PerkCardType::BreakOfDawn, 3);
    addCard(PerkCardType::Overstock, 4);
    addCard(PerkCardType::LateIntoTheNight, 4);
    addCard(PerkCardType::Repel, 3);
    addCard(PerkCardType::Hurry, 3);

    shuffleDeck();
}

void PerkDeck::addCard(const PerkCardType& type, const int& count) {
    for (int i = 0; i < count; i++ ) {
        cards.emplace_back(type);
    }
}

void PerkDeck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}



PerkDeck PerkDeck::drawCard() {
    if(cards.empty()) {
        throw std::runtime_error("No more Perk cards!");
    }
    PerkDeck card = cards.back();
    cards.pop_back();
    inGameCards.emplace_back(card);
    
    return card;
}

bool PerkDeck::isEmpty() {
    return cards.empty();
}
std::vector<PerkDeck> PerkDeck::getInGamePerkCards() {
    return inGameCards;
}

void PerkDeck::visitFormTheDetective(Monster& invisibleMan, const NameLocation& newNameLocationInvisibleMan) const {
    invisibleMan.setMonsterPosition(newNameLocationInvisibleMan);
}

void PerkDeck::breakOfDawn(const Heroes& hero, Item& item) const {
    auto itemcard = item.addItemInGame();
    item.setItemsPosition(itemcard, hero.getLocationHero());
}

void PerkDeck::overstock(const Heroes& hero1, const Heroes& hero2, Item& item) const {
    auto itemcard = item.addItemInGame();
    item.setItemsPosition(itemcard, hero1.getLocationHero());

    itemcard = item.addItemInGame();
    item.setItemsPosition(itemcard, hero2.getLocationHero());
}

void PerkDeck::lateIntoTheNight(Heroes& hero) const {
    hero.decreaseAction();
}

bool PerkDeck::Repel(Monster& monster, const NameLocation& newNameLocationMonster) const {
    if(!monster.cheknumberDistance(newNameLocationMonster)) {
        return false;
    }
    monster.setMonsterPosition(newNameLocationMonster);
    return true;
}

bool PerkDeck::Hurry(Heroes& hero, const NameLocation& newNameLocationHero) const {
    if(!hero.cheknumberDistance(newNameLocationHero)) {
        return false;
    }
    hero.setHeroesPosition(newNameLocationHero);
    return true;
}

PerkCardType PerkDeck::getPerkType() const {
    return this->perkType;
}

std::vector<PerkDeck> PerkDeck::cards;
std::vector<PerkDeck> PerkDeck::inGameCards;
