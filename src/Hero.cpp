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

Heroes::Heroes(int maxAction, const NameHeroes nameHero, Map& locationHero, const NameLocation& newNameLocationHeroes)  : nameHero(nameHero), statusHero(Status::Alive), locationHero(locationHero),
    numberActionTaken(0), maxActions(maxAction) {
        // perkCard.drawCard();
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



void Heroes::move(Villager& villager,const NameLocation& newNameLocationHero, bool skipVillager) {

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
    
    
    if(!skipVillager) {   
        std::vector<NameVillagers> villagersMove;
        villagersMove = villager.moveLocation(this->getLocationHero());
        for(auto& villagerMove : villagersMove) {
            villager.setVillagersPosition(villagerMove, newNameLocationHero);
        }
    }
    this->setHeroesPosition(newNameLocationHero);

    incrementAction();
}


void Heroes::guide(Villager& villager, const NameVillagers& nameVillager) {  

    villager.setVillagersPosition(nameVillager, this->getLocationHero());

    incrementAction();
}