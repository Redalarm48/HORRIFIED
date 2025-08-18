#include "MonsterCard.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>

// MonsterCard::MonsterCard(MonsterCardType type, int diceCount, const std::vector<Monster*>& strikeOrder)
//     : type(type), diceCount(diceCount), strikeOrder(strikeOrder) {}


// int MonsterCard::getDiceCount() const {
//     return diceCount;
// }

// const std::vector<Monster*>& MonsterCard::getStrikeOrder() const {
//     return strikeOrder;
// }

// MonsterCardType MonsterCard::getType() const
// {

//     return this->type;

// };
MonsterDeck::MonsterDeck(){
    this->initializeDeck();
}

MonsterDeck::MonsterDeck(const int ItemCount, const int diceCount, const int moveCount, const MonsterCardType& monsterType, const std::vector<NameMonster>& striceOrder) : ItemCount(ItemCount), diceCount(diceCount), moveCount(moveCount), monsterType(monsterType), striceOrder(striceOrder) {}


// MonsterDeck::MonsterDeck(Monster* dracula, Monster* invisibleMan, Monster* frenzied)
//     : dracula(dracula), invisibleMan(invisibleMan), frenzied(frenzied) {
//     initializeDeck();
// }

void MonsterDeck::addCard(const int count, const int ItemCount, const int diceCount, const int moveCount, const MonsterCardType& monsterType, const std::vector<NameMonster>& striceOrder){
    for (int i = 0; i < count; ++i) {
        cards.emplace_back(ItemCount, diceCount, moveCount, monsterType, striceOrder);
    }
}

void MonsterDeck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

void MonsterDeck::initializeDeck() {
    addCard(3, 2, 2, 1, MonsterCardType::FormOfTheBat, {NameMonster::INVISIBLE_MAN});
    addCard(3, 0, 2, 1, MonsterCardType::Sunrise, {NameMonster::FRENZI , NameMonster::INVISIBLE_MAN });
    addCard(5, 2, 3, 1, MonsterCardType::Thief, { NameMonster::DRACULA , NameMonster::INVISIBLE_MAN });
    addCard(1, 3, 3, 1, MonsterCardType::TheDelivery, { NameMonster::FRENZI });
    addCard(1, 3, 2, 1, MonsterCardType::FortuneTeller, { NameMonster::FRENZI });
    addCard(1, 3, 2, 1, MonsterCardType::FormerEmployer, { NameMonster::FRENZI , NameMonster::INVISIBLE_MAN });
    addCard(1, 3, 3, 2, MonsterCardType::HurriedAssistant, { NameMonster::DRACULA });
    addCard(1, 3, 3, 1, MonsterCardType::TheInnocent, {NameMonster::INVISIBLE_MAN, NameMonster::DRACULA, NameMonster::FRENZI });
    addCard(1, 3, 2, 2, MonsterCardType::EgyptianExpert, {NameMonster::DRACULA , NameMonster::DRACULA  });
    addCard(1, 3, 2, 1, MonsterCardType::TheIchthyologist, { NameMonster::FRENZI });
    addCard(2, 2, 2, 1, MonsterCardType::HypnoticGaze, { NameMonster::INVISIBLE_MAN });
    addCard(2, 3, 2, 3, MonsterCardType::OnTHeMove, { NameMonster::FRENZI });
    
    shuffleDeck();
}

void MonsterDeck::playDrawCard(const MonsterCardType& monsterType, Villager& villager, Heroes& hero, Monster& dracula, Monster& invisibleMan, Item& item) {
    switch (monsterType)
    {
    case MonsterCardType::EgyptianExpert:
        this->egyptianExpert(villager);
        break;    
    case MonsterCardType::FormerEmployer:
        this->formerEmployer(villager);
        break;    
    case MonsterCardType::FormOfTheBat:
        this->formOfTheBat(hero, dracula);
        break;    
    case MonsterCardType::FortuneTeller:
        this->fortuneTeller(villager);
        break;    
    case MonsterCardType::HurriedAssistant:
        this->hurriedAssistant(villager);
        break;    
    case MonsterCardType::HypnoticGaze:
        // this.hy
        break;    
    case MonsterCardType:: OnTHeMove:
        break;    
    case MonsterCardType::Sunrise:
        this->sunrise(dracula);
        break;    
    case MonsterCardType::TheDelivery:
        this->theDelivery(villager);
        break;    
    case MonsterCardType::TheIchthyologist:
        this->theIchthyologist(villager);
        break;    
    case MonsterCardType::TheInnocent:
        this->theInnocent(villager);
        break;    
    case MonsterCardType::Thief:
        this->thief(invisibleMan, item);
        break;    
    default:
        throw std::invalid_argument("not fount monster card type");
        break;
    }
}

MonsterDeck MonsterDeck::drawCard(Item& item, Villager& villager, Heroes& hero, Monster& dracula, Monster& invisibleMan ) {
    if (cards.empty()) {
        throw std::runtime_error("No more Monster cards!");
    }
    MonsterDeck card = cards.back();
    cards.pop_back();
    inGameCards.emplace_back(card);

    for(int i = 0; i < card.ItemCount; i++) {
        item.addItemInGame();
    }

    this->playDrawCard(card.monsterType, villager, hero, dracula, invisibleMan, item);

    return card;
}

bool MonsterDeck::isEmpty() const {
    return cards.empty();
}

void MonsterDeck::formOfTheBat(Heroes& heroNow, Monster& draacula) {
    draacula.setMonsterPosition(heroNow.getLocationHero());
}

void MonsterDeck::sunrise(Monster& dracula) {
    dracula.setMonsterPosition(NameLocation::CRYPT);
}

void MonsterDeck::thief(Monster& invisibleMan, Item& item) {
    invisibleMan.setMonsterPosition(item.itemMaxLocation());
    item.removeAllItemLocation(item.itemMaxLocation());
}

void MonsterDeck::theDelivery(Villager& wilburAndChick) {
    wilburAndChick.initializeVillagers(NameVillagers::WilnureAndChick);
}

void MonsterDeck::fortuneTeller(Villager& maleva) {
    maleva.initializeVillagers(NameVillagers::Maleva);
}

void MonsterDeck::formerEmployer(Villager& drCranly) {
    drCranly.initializeVillagers(NameVillagers::Dr_crunly);
}

void MonsterDeck::hurriedAssistant(Villager& fritz) {
    fritz.initializeVillagers(NameVillagers::Fritz);
}

void MonsterDeck::theInnocent(Villager& maria) {
    maria.initializeVillagers(NameVillagers::Maria);
}

void MonsterDeck::egyptianExpert(Villager& pearson) {
    pearson.initializeVillagers(NameVillagers::Prof_pearson);
}

void MonsterDeck::theIchthyologist(Villager& drRead) {
    drRead.initializeVillagers(NameVillagers::Dr_read);
}


std::vector<MonsterDeck> MonsterDeck::cards;
std::vector<MonsterDeck> MonsterDeck::inGameCards;


