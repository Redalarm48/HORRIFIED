#include "PerkCard.hpp"
#include "InvisibleMan.hpp"
#include "Map.hpp"
#include "Hero.hpp"
#include "Dracula.hpp"
#include "Game.hpp"

inline std::ostream& operator<<(std::ostream& os, const PerkCardType& type) {
    switch (type) {
        case PerkCardType::VisitFromDetective:
            os << "VisitFromDetective";
            break;
        case PerkCardType::
            BreakOfDawn: os << "BreakOfDawn"; 
            break;
        case PerkCardType::Overstock:   
            os << "Overstock"; 
            break;
        case PerkCardType::LateIntoTheNight:   
            os << "LateIntoTheNight"; 
            break;
        case PerkCardType::Repel:   
            os << "Repel"; 
            break;
        case PerkCardType::Hurry:   
            os << "Hurry"; 
            break;

        default:                   
            os << "UNKNOWN"; 
            break;
    }
    return os;
}
PerkCard::PerkCard(PerkCardType perkType,const std::string& descriprion) {
    this->perkType = perkType;
    this->description = descriprion;
}

PerkCardType PerkCard::getType() const {
    return perkType;
}
std::string PerkCard::getDescription() const {
    return description;
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

void PerkDeck::addCard(PerkCardType type, const std::string& desc, const int count) {
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
    inGameCards.emplace_back(card);
    return card;
}

bool PerkDeck::isEmpty() {
    return cards.empty();
}
std::vector<PerkCard> PerkDeck::getInGamePerkCards() {
    return inGameCards;
}
std::ostream& operator<<(std::ostream& out, const PerkCard& perk) {
    out << perk.perkType;
    return out;
}

void PerkDeck::visitFormTheDetective() {
    std::string newLocationInvisibelMan;
    std::cout << "Enter name location invisibelman: ";
    std::cin >> newLocationInvisibelMan;

    Map::setPlayerPosition("invisibleMan", newLocationInvisibelMan);
    
}

void PerkDeck::Hurry(Heroes& hero1, Heroes& hero2) {

    std::cout << "Hero1: \n";
    hero1.move(true);
    std::cout << "Choose the second path for the Hero1.\n";
    hero1.move(true);
    
    std::cout << "Hero2: \n";
    hero2.move(true);
    std::cout << "Choose the second path for the Hero2.\n";
    hero2.move(true);

}

void PerkDeck::Repel(Dracula& dracula, InvisibleMan& invisibleMan) {
    dracula.move();
    dracula.move();
    invisibleMan.move();
    invisibleMan.move();
}

void PerkDeck::breakOfDawn(Heroes& hero, Game& game) {
    game.setMonsterPhaseTrue(false);  // Skip monster phase
    std::cout << "Monster phase will be skipped.\n";
    game.placeRandomItemAt(hero.getLocationHero(), 2);
    std::cout << "You received 2 random items at your location.\n";
}
void PerkDeck::overstock(Game& game, Heroes& hero1, Heroes& hero2) {
    game.placeRandomItemAt(hero1.getLocationHero(), 1);
    game.placeRandomItemAt(hero2.getLocationHero(), 1);
    std::cout << "Each hero received 1 item at their locations.\n";
}
void PerkDeck::lateIntoTheNight(Heroes& hero) {
    hero.decreaseAction();
    std::cout << "You received 2 extra actions this trun!\n";

}



std::vector<PerkCard> PerkDeck::cards;
std::vector<PerkCard> PerkDeck::inGameCards;
