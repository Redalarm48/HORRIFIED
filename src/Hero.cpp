#include "Hero.hpp"
#include "Villagers.hpp"
#include "Game.hpp"
#include "Map.hpp"

std::string Heroes::changNameHeroesTheString(const NameHeroes& nameHeroes) {
    switch (nameHeroes)
    {
    case NameHeroes::ARCHAEOLOGIST: 
        return "Archaeologist";
        break;
    case NameHeroes::MAYOR:
        return "Mayor";
        break;
    
    default:
        throw std::invalid_argument("");
    }
}

void Heroes::setHeroesPosition(const NameLocation& newNameLocationHeroes) {
    if(this->nameLocationHeroes == newNameLocationHeroes) {
        return;
    }
    auto chek = std::find_if(locationHero.map.begin(), locationHero.map.end(), [&newNameLocationHeroes](const auto& p) {
        return p.first == newNameLocationHeroes;
    });
    auto chek2 = std::find_if(locationHero.map.begin(), locationHero.map.end(), [this](const auto& p) {
        return p.first == nameLocationHeroes;
    });
    if(chek != locationHero.map.end() && chek2 != locationHero.map.end()) {
        chek->second.addHeroes(nameHero);
        chek2->second.removeHeroes(nameHero);
        nameLocationHeroes = newNameLocationHeroes;
    }
}

Heroes::Heroes(int maxAction, const NameHeroes nameHero, Map& locationHero, const NameLocation& newNameLocationHeroes, PerkDeck& perkDeck)  : nameHero(nameHero), statusHero(Status::Alive), locationHero(locationHero),
    numberActionTaken(0), maxActions(maxAction) {
        this->setPerkCard(perkDeck.drawCard());
        auto chek = std::find_if(locationHero.map.begin(), locationHero.map.end(), [&newNameLocationHeroes](const auto& p) {
        return p.first == newNameLocationHeroes;
        });
        if(chek != locationHero.map.end()) {
            chek->second.addHeroes(nameHero);
            nameLocationHeroes = newNameLocationHeroes;
        }
    }

NameLocation Heroes::getLocationHero() const {
    
    return this->nameLocationHeroes;
}

bool Heroes::canTakeAction() const {
    return this->numberActionTaken < this->maxActions;
}

void Heroes::resetActions() {
    numberActionTaken = 0;
}


void Heroes::incrementAction() {
    ++numberActionTaken;
    
}

void Heroes::decreaseAction() {
    numberActionTaken-=2;
    if(numberActionTaken < 0)
        numberActionTaken = 0;
    
}

int Heroes::getNumberActionTaken() const {
    return numberActionTaken;
    
}



void Heroes::move(Villager& villager,const NameLocation& newNameLocationHero, bool yesOrno, const std::vector<NameVillagers>& villagersMove) {

    auto neighbors = locationHero.getNeighborLocation(nameLocationHeroes);
    

    bool chek = false;


    for(const auto& neighbor: neighbors) {
        if (neighbor->getNameLocation() == newNameLocationHero) {
            chek = true;
            break;
        }
    }
    if(!chek) {
        throw std::invalid_argument("invalid location move hero");
    }
    
    
    if(yesOrno) {   

        for(auto& villagerMove : villagersMove) {
            villager.setVillagersPosition(villagerMove, newNameLocationHero, *this);
        }
    }
    this->setHeroesPosition(newNameLocationHero);

    incrementAction();
}


void Heroes::guide(Villager& villager, const NameVillagers& nameVillager) {  


    villager.setVillagersPosition(nameVillager, this->getLocationHero(), *this);


    incrementAction();
}


bool Heroes::cheknumberDistance(const NameLocation& nameLocation) {
    int numberdistance = this->locationHero.findShortestPath<int>(this->getLocationHero(), nameLocation);
    return (
        (numberdistance == 2)
    );
}

void Heroes::pickUp(Item& item, const std::vector<NameItem>& nameItem) {
    
 if(
        this->nameLocationHeroes == NameLocation::INN||
        this->nameLocationHeroes == NameLocation::BARN||
        this->nameLocationHeroes == NameLocation::INSTITUTE||
        this->nameLocationHeroes == NameLocation::LABORATORY||
        this->nameLocationHeroes == NameLocation::MANSION) {
            this->nameItemPickUpInvisibleMan.emplace_back(nameItem.back(),this->nameLocationHeroes);
        }
    for(const auto& name : nameItem) {
        item.pickUp(this->nameHero, name);
    }

    incrementAction();
    
}

bool Heroes::defieat(Monster& monster, Item& item) {
    TypeOwnership typeOnserShip;
    switch (nameHero)
    {
    case NameHeroes::ARCHAEOLOGIST:
        typeOnserShip = TypeOwnership::ARCHAEOLOGIST;
        break;
    case NameHeroes::MAYOR:
        typeOnserShip = TypeOwnership::MAYOR;
        break;
    

    default:
        throw std::invalid_argument(" ");
        break;

    }
    int chekNumberItem = 0;
    std::vector<Item> advanceItem;
    if(monster.getNameM() == NameMonster::DRACULA) {


        for(auto& [name,item] : item.getItemsInGame()) {
            if(chekNumberItem >= 6) {
                break;
            }
            if(item.getTypeOwnsership() == typeOnserShip) {
                if(item.getTypeItem() == TypeItem::YELLOW) {
                    chekNumberItem += item.getPower();
                    advanceItem.emplace_back(item);
                }
            }

        }

        if(chekNumberItem < 6) {
            return false;
        }

        for(auto& item : advanceItem) {
            item.removeItemInGame(item.getNameItem());
        }

        monster.removeMonster();
        return true;

    }
    else if(monster.getNameM() == NameMonster::INVISIBLE_MAN) {
        for(auto& [name,item] : item.getItemsInGame()) {
            if(chekNumberItem >= 9) {
                break;
            }
            if(item.getTypeOwnsership() == typeOnserShip) {
                if(item.getTypeItem() == TypeItem::RED) {
                    chekNumberItem += item.getPower();
                    advanceItem.emplace_back(item);
                }
            }
        }

        if(chekNumberItem < 9) {
            return false;
        }

        for(auto& item : advanceItem) {
            item.removeItemInGame(item.getNameItem());
        }

        monster.removeMonster();
        return true;

    }
    incrementAction();

}

NameHeroes Heroes::getNameHero() const {
    return this->nameHero;
}

std::string Heroes::getName() const {
    switch (nameHero)
    {
    case NameHeroes::ARCHAEOLOGIST:
        return "Archaeologist";
    case NameHeroes::MAYOR:
        return "Mayor";
    default:
        throw std::invalid_argument("not found Hero");
    }
}

void Heroes::setPerkCard(const PerkDeck& newCard) {
    this->perkCards.emplace_back(newCard);
}

std::vector<std::pair<NameItem, NameLocation>> Heroes::getNameItemPickUpInvisibleMan() const {
    return this->nameItemPickUpInvisibleMan;
}

Archaeologist::Archaeologist(Map& map, PerkDeck& perkDeck) : Heroes(1,NameHeroes::ARCHAEOLOGIST, map, NameLocation::DOCKS, perkDeck) {
    // بدنه سازنده
}

Mayor::Mayor(Map& map, PerkDeck& perkDeck) : Heroes(1,NameHeroes::MAYOR, map, NameLocation::THEATRE, perkDeck) {
    // بدنه سازنده

}

Scientist::Scientist(Map& map, PerkDeck& perkDeck) : Heroes(4,NameHeroes::SCIENTIST, map, NameLocation::INSTITUTE, perkDeck) {
    // بدنه سازنده
}

Courier::Courier(Map& map, PerkDeck& perkDeck) : Heroes(4,NameHeroes::COURIER, map, NameLocation::SHOP, perkDeck) {
    // بدنه سازنده
}

const std::vector<PerkDeck>& Heroes::getPerkCards() const {
    return this->perkCards;
}