#include "Villagers.hpp"
#include <algorithm>
#include <cctype>


Villager::Villager(Map& map, PerkDeck& perkDeck,const NameLocation& locationVillager, const NameVillagers& nameVillager, const NameLocation& safeLocationVillager) : perkDeck(perkDeck), nameLocationVillagers(locationVillager), nameVillager(nameVillager), safeLocationVillager(safeLocationVillager), locationVillager(map) {}

Villager::Villager(Map& locationVIllager, PerkDeck& perkDeck): perkDeck(perkDeck), locationVillager(locationVIllager) , nameVillager(NameVillagers::Default), safeLocationVillager(NameLocation::Default) {}
// Villager::Villager(Map& locationVIllager) : locationVillager(locationVillager){}

void Villager::setVillagersPosition(const NameLocation& newNameLocationVillagers) {
    if(this->nameLocationVillagers == newNameLocationVillagers) {
        return;
    }
    auto chek = std::find_if(locationVillager.map.begin(), locationVillager.map.end(), [&newNameLocationVillagers](const auto& p) {
        return p.first == newNameLocationVillagers;
    });
    auto chek2 = std::find_if(locationVillager.map.begin(), locationVillager.map.end(), [this](const auto& p) {
        return p.first == nameLocationVillagers;
    });

    if(chek != locationVillager.map.end() && chek2 != this->locationVillager.map.end()) {
        chek->second.addVillagers(nameVillager);
        chek2->second.removeVillagers(nameVillager);
        nameLocationVillagers = newNameLocationVillagers;
    }
    else  {
        throw std::invalid_argument("not found VIllager or location");
    }
}
void Villager::setVillagersPosition(const NameVillagers& nameVillager, const  NameLocation newNameLocationVillager, Heroes& hero) {
    auto chek = std::find_if(villagers.begin(), villagers.end(), [&nameVillager](const auto& p) {
        return p.first == nameVillager;
    });
    if(chek != villagers.end()) {
        chek->second.setVillagersPosition(newNameLocationVillager);
        (this->chekSafeLocationVillager(nameVillager, hero));
    }
    else {
        throw std::invalid_argument(" ");
    }
}

std::string Villager::chengNameVillagerTheString(const NameVillagers& nameVillager) {
    switch (nameVillager)
    {
    case NameVillagers::Dr_crunly :
        return "Dr.crunly";
        break;
    
    case NameVillagers::Maleva :
        return "Maleva";
        break;

    case NameVillagers::Fritz :
        return "Fritz";
        break;

    case NameVillagers::Maria :
        return "Maria";
        break;

    case NameVillagers::Prof_pearson :
        return "Prof_pearson";
        break;

    case NameVillagers::Dr_read :
        return "Dr.read";
        break;
    case NameVillagers::WilnureAndChick:
        return "Wilnure & Chick";
        break;
        case NameVillagers::Default:
        return "default";
        break;
    }
    return "no";
}

NameVillagers Villager::chengNameVillager(const std::string& nameVillagersString) {

    if(nameVillagersString == "Dr.crunly") {
        return NameVillagers::Dr_crunly;
    }
    else if(nameVillagersString == "Maleva") {
        return NameVillagers::Maleva;
    }
    else if(nameVillagersString == "Fritz") {
        return NameVillagers::Fritz;
    }
    else if(nameVillagersString == "Maria") {
        return NameVillagers::Maria;
    }
    else if(nameVillagersString == "Prof.perarson") {
        return NameVillagers::Prof_pearson;
    }
    else if(nameVillagersString == "Dr.read") {
        return NameVillagers::Dr_read;
    }
    else if(nameVillagersString == "Wilnure & Chick") {
        return NameVillagers::WilnureAndChick;
    }
    else {
        throw std::bad_alloc();
    }
}


NameVillagers Villager::getNameVillager() const {
    return nameVillager;
}

NameLocation Villager::getLocationVillager() const {

    return nameLocationVillagers;
}

NameLocation Villager::getSafeLocationVillager() const {
    return safeLocationVillager;
}

std::list<std::pair<NameVillagers, Villager>> Villager::getVillagers() const {
    return villagers;
}



void Villager::addVillager(const NameVillagers& nameVillager, const NameLocation& nameLocationVillagerr, const NameLocation& safeLocationVillagerr) {
    Villager newVillager(locationVillager,perkDeck,nameLocationVillagerr, nameVillager, safeLocationVillagerr);
    villagers.emplace_back(nameVillager, newVillager);
    auto chek = std::find_if(this->locationVillager.map.begin(), this->locationVillager.map.end(),[&nameLocationVillagerr](const auto& p) {
        return p.first == nameLocationVillagerr;
    }) ;
    if(chek == this->locationVillager.map.end()) {
        throw std::invalid_argument("not fount locaiton villagere");
    }
    chek->second.addVillagers(nameVillager);
}

void Villager::initializeVillagers(const NameVillagers& nameVillager) {
    switch (nameVillager)
    {
    case NameVillagers::Dr_crunly :
        addVillager(NameVillagers::Dr_crunly, NameLocation::PRECINCT, NameLocation::LABORATORY);
        break;
    
    case NameVillagers::Maleva :
        addVillager(NameVillagers::Maleva, NameLocation::SHOP, NameLocation::CAMP);
        break;

    case NameVillagers::Fritz :
        addVillager(NameVillagers::Fritz, NameLocation::INSTITUTE, NameLocation::TOWER);
        break;

    case NameVillagers::Maria :
        addVillager(NameVillagers::Maria, NameLocation::CAMP, NameLocation::BARN);
        break;

    case NameVillagers::Prof_pearson :
        addVillager(NameVillagers::Prof_pearson, NameLocation::MUSEUM, NameLocation::CAVE);
        break;

    case NameVillagers::Dr_read :
        addVillager(NameVillagers::Dr_read, NameLocation::CAMP, NameLocation::INSTITUTE);
        break;
    case NameVillagers::WilnureAndChick:
        addVillager(NameVillagers::WilnureAndChick, NameLocation::PRECINCT, NameLocation::DOCKS);
        break;

    default:
        throw std::invalid_argument("");
        break;

    }

}
void Villager::removeVillager(const NameVillagers& nameVilager) {
    auto chekNameVillager = std::find_if(this->villagers.begin(), this->villagers.end(), [&nameVilager](const auto& p) {
        return p.first == nameVilager;
    });
    if(chekNameVillager == this->villagers.end()) {
        throw std::invalid_argument("not found name villager");
    }
    auto nameLocationVillagerRemove = chekNameVillager->second.nameLocationVillagers;
    auto chek = std::find_if(locationVillager.map.begin(), locationVillager.map.end(), [&nameLocationVillagerRemove](const auto& p) {
        return p.first == nameLocationVillagerRemove;
    });
    if(chek != locationVillager.map.end()) {
        chek->second.removeVillagers(nameVilager);
        villagers.erase(chekNameVillager);
    }
    else {
        throw std::invalid_argument("not found name location villager");
    }
}


void Villager::chekSafeLocationVillager(const NameVillagers& nameVilager, Heroes& hero) {
    auto chek = std::find_if(villagers.begin(), villagers.end(), [this](const auto& p) {
        return p.first == nameVillager;
    });
    if(chek != villagers.end()) {
        if(chek->second.getSafeLocationVillager() == chek->second.getLocationVillager()) {
            chek->second.removeVillager(nameVilager);
            hero.setPerkCard(this->perkDeck.drawCard());
        }
    }
    else {
        throw std::invalid_argument("");
    }
}

std::list<std::pair<NameVillagers, Villager>> Villager::villagers;

