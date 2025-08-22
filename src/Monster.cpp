#include "Monster.hpp"
#include "Games.hpp"
Monster::Monster(const NameMonster& nameMonster, Map& locationmonster, const NameLocation& newNameLocationMonster) : nameMonster(nameMonster), locationMonster(locationmonster){
     auto chek = std::find_if(locationmonster.map.begin(), locationmonster.map.end(), [&newNameLocationMonster](const auto& p) {
        return p.first == newNameLocationMonster;
        });
        if(chek != locationMonster.map.end()) {
            chek->second.addMonsters(nameMonster);
            nameLocationMonster = newNameLocationMonster;
        }
}

Monster::~Monster(){}

void Monster::setMonsterPosition(const NameLocation& newNameLocaitonMonster) {
    if(this->nameLocationMonster == newNameLocaitonMonster) {
        return;
    }
    auto chek = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [&newNameLocaitonMonster](const auto& p) {
        return p.first == newNameLocaitonMonster;
    });
    auto chek2 = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [this](const auto& p) {
        return p.first == nameLocationMonster;
    });
    if(chek != locationMonster.map.end() && chek2 != locationMonster.map.end()) {
        chek->second.addMonsters(nameMonster);
        chek2->second.removeMonsters(nameMonster);
        nameLocationMonster = newNameLocaitonMonster;
    }
    else {
        throw std::invalid_argument(" ");
    }
}

void Monster::removeMonster() {
    auto chek = std::find_if(locationMonster.map.begin(), locationMonster.map.end(), [this](const auto& p) {
        return p.first == this->nameLocationMonster;
    });
    if(chek == locationMonster.map.end()) {
        throw std::invalid_argument("");
    }
    chek->second.removeMonsters(nameMonster);
}

NameMonster Monster::getNameM() const {

    return nameMonster;
}

Map& Monster::getLocationMonster() const {
    return this->locationMonster;
}

void Monster::strike(int diceCount, Villager& villager,
                     Heroes& mayor, Heroes& archaeologist,
                     Heroes& courier, Heroes& scientist, Item& items, Games* game) 
{
    auto diceResult = rollDice();

    switch (DiceResult::Attack)
    {
    case DiceResult::Attack: {
        if(this->nameMonster == NameMonster::DRACULA) {
            game->cout("Equal monster dice (!)");
            for (auto& [name, map] : this->locationMonster.map) {
                if(name == this->nameLocationMonster) {
                    Heroes* hero;
                    if(!map.getNameHeroes().empty()) {
                        TypeOwnership type;
                        switch (map.getNameHeroes().back()) {
                            case NameHeroes::MAYOR:
                            hero = &mayor;
                            type =TypeOwnership::MAYOR;
                            break;
                            case NameHeroes::ARCHAEOLOGIST:
                            hero = &archaeologist;
                            type =TypeOwnership::ARCHAEOLOGIST;
                            break;
                            case NameHeroes::COURIER:
                            hero = &courier;
                            type =TypeOwnership::COURIER;
                            break;
                            case NameHeroes::SCIENTIST:
                            hero = &scientist;
                            type =TypeOwnership::SCIENTIST;
                            break;
                            default:
                            throw std::invalid_argument("not found hero");
                            break;
                        }
                        bool hasItem = false;
                        for (const auto& [nameItem, item] : items.getItemsInGame()) {
                            if (item.getTypeOwnsership() == type) {
                                hasItem = true;
                                game->cout("Do you want to spend an item to fight the monster?");
                                if (game->yesOrNo()) {
                                    items.removeItemInGame(nameItem);
                                    return;
                                }
                                else {                                
                                    hero->setHeroesPosition(NameLocation::HOSPITAL);
                                    game->cout("Hero has no items! Sent to hospital.");
                                    
                                }
                                break;
                            }
                            else {
                                hero->setHeroesPosition(NameLocation::HOSPITAL);
                                game->cout("Hero has no items! Sent to hospital.");
                            }
                        }
                        
                    }
                }
            }
            break;
        }
    }
        case DiceResult::Power: {
        game->cout("Equal monster dice (*)");
        this->power(villager, mayor, scientist);
    }
    
    default:
        break;
    }

}

DiceResult Monster::rollDice() {
    int r = rand() % 6;
    if(r < 2) return DiceResult::None;
    else if(r < 4) return DiceResult::Attack;
    else return DiceResult::Power;
}

NameMonster Monster::getFrenzyOrder() const {

    return FrenzyOrder;
}


NameLocation Monster::getNameLocationMonster() const {
    return nameLocationMonster;
}

bool Monster::cheknumberDistance(const NameLocation& nameLocation) {
    int numberDistance = this->locationMonster.findShortestPath<int>(this->nameLocationMonster, nameLocation);
    return (
        numberDistance == 2
    );
}


NameMonster Monster::FrenzyOrder = NameMonster::DRACULA;

