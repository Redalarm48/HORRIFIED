#include "PerkCard.hpp"

PerkCard::PerkCard(PerkCardType perkType,const std::string& descriprion) {
    this->perkType = perkType;
    this->description = descriprion;
}

void PerkDeck::initializeDeck() {
    addCard(PerkCardType::VisitFromDetective, "Place the Invisible Man at any location.", 3);
    addCard(PerkCardType::BreakOfDawn, "Skip next monster phase. Draw 2 items.", 3);
    addCard(PerkCardType::Overstock, "Each hero draws 1 item.", 4);
    addCard(PerkCardType::LateIntoTheNight, "Current hero gets 2 extra actions.", 4);
    addCard(PerkCardType::Repel, "Move each monster up to 2 spaces.", 3);
    addCard(PerkCardType::Hurry, "Move each hero up to 2 spaces.", 3);

    shuffleDeck();

}

void PerkDeck::addCard(PerkCardType type, const std::string desc, int count) {
    for (int i = 0; i < count; i++ ) {
        cards.emplace_back(type,desc);
    }
}

void PerkDeck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

PerkCard PerkDeck::drawCard() {
    if(cards.empty()) {
        throw std::runtime_error("No more Perk cards!");
    }
    PerkCard card = cards.back();
    cards.pop_back();
    return card;
}

bool PerkDeck::isEmpty() {
    return cards.empty();
}

std::vector<PerkCard> PerkDeck::cards;
