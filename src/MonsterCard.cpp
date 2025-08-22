#include "MonsterCard.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
#include "Dracula.hpp"
#include "InvisibleMan.hpp"


MonsterDeck::MonsterDeck(){
    this->initializeDeck();
}

MonsterDeck::MonsterDeck(const int ItemCount, const int diceCount, const int moveCount, const MonsterCardType& monsterType, const std::vector<NameMonster>& striceOrder) : ItemCount(ItemCount), diceCount(diceCount), moveCount(moveCount), monsterType(monsterType), striceOrder(striceOrder) {}



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

void MonsterDeck::playDrawCard(const MonsterCardType& monsterType,MonsterDeck& card, Villager& villager, Heroes& hero, Heroes& hero1, Heroes& hero2, Heroes& hero3, Dracula& dracula, InvisibleMan& invsibleMan, Item& item, Games* game) {
    for(size_t i = 0; i < card.ItemCount; ++i) {
        item.addItemInGame();
    }
    bool chek;
    
    
    switch (monsterType)
    {
    case MonsterCardType::EgyptianExpert:
        this->egyptianExpert(villager);
        break;    
    case MonsterCardType::FormerEmployer:
        this->formerEmployer(villager);
        break;    
    case MonsterCardType::FormOfTheBat:
        this->formOfTheBat(hero, dracula, item);
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
        this->thief(invsibleMan, item);
        break;    
    default:
        throw std::invalid_argument("not fount monster card type");
        break;
    }
    Monster* monster;
    for(auto& mon: card.striceOrder) {
        switch (mon)
        {
        case NameMonster::DRACULA:
            monster = &dracula;
            break;
        case NameMonster::INVISIBLE_MAN:
            monster = &invsibleMan;
            break;
        case NameMonster::FRENZI:
            switch (monster->getFrenzyOrder())
            {
            case NameMonster::DRACULA:
                monster = &dracula;
                break;
            case NameMonster::INVISIBLE_MAN:
                monster = &invsibleMan;
                break;
            }
        default:
            break;
        }
        for (size_t i = 0; i < card.moveCount; i++)
        {
            chek = monster->moveMonster(villager, hero, hero1, hero2, hero3);
        }
        if(chek) {
            for (size_t i = 0; i < card.diceCount; i++)
            {
                monster->strike(0, villager, hero, hero1, hero2, hero3, item, game);
            }
        }
            
    }
}

MonsterDeck MonsterDeck::drawCard(Item& item, Villager& villager, Heroes& hero, Heroes& hero1, Heroes& hero2, Heroes& hero3, Dracula& dracula, InvisibleMan& invisbleMan, Games* game) {
    if (cards.empty()) {
        throw std::runtime_error("No more Monster cards!");
    }
    MonsterDeck card = cards.back();
    cards.pop_back();
    inGameCards.emplace_back(card);

    for(int i = 0; i < card.ItemCount; i++) {
        item.addItemInGame();
    }

    this->playDrawCard(card.monsterType, card, villager, hero, hero1, hero2, hero3, dracula, invisbleMan, item, game);

    return card;
}

bool MonsterDeck::isEmpty() const {
    return cards.empty();
}

void MonsterDeck::formOfTheBat(Heroes& heroNow, Monster& draacula, Item& item) {
    for(int i = 0; i < 2; i++) {
        item.addItemInGame();
    }
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

MonsterCardType MonsterDeck::getTypeItem() const {
    return this->monsterType;
}

std::vector<MonsterDeck> MonsterDeck::cards;
std::vector<MonsterDeck> MonsterDeck::inGameCards;


