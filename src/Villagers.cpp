#include "Villagers.hpp"
#include <algorithm>
#include <cctype>


Villager::Villager(Map& map,const NameLocation& locationVillager, const NameVillagers& nameVillager, const NameLocation& safeLocationVillager) : nameLocationVillagers(locationVillager), nameVillager(nameVillager), safeLocationVillager(safeLocationVillager), locationVillager(map) {}

Villager::Villager(Map& locationVIllager) : locationVillager(locationVIllager) , nameVillager(NameVillagers::Default), safeLocationVillager(NameLocation::Default) {}
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
void Villager::setVillagersPosition(const NameVillagers& nameVillager, const  NameLocation newNameLocationVillager) {
    auto chek = std::find_if(villagers.begin(), villagers.end(), [&nameVillager](const auto& p) {
        return p.first == nameVillager;
    });
    if(chek != villagers.end()) {
        chek->second.setVillagersPosition(newNameLocationVillager);
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

void Villager::addVillager(const NameVillagers& nameVillager, const NameLocation& nameLocationVillagerr, const NameLocation& safeLocationVillagerr) {
    Villager newVillager(locationVillager,nameLocationVillagerr, nameVillager, safeLocationVillagerr);
    villagers.emplace_back(nameVillager, newVillager);
    auto chek = std::find_if(this->locationVillager.map.begin(), this->locationVillager.map.end(),[&nameLocationVillagerr](const auto& p) {
        return p.first == nameLocationVillagerr;
    }) ;
    if(chek == this->locationVillager.map.end()) {
        throw std::invalid_argument("not fount locaiton villagere");
    }
    chek->second.addVillagers(nameVillager);
    // setVillagersPosition(nameVillager, nameLocationVillagerr);
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
    }
    else {
        throw std::invalid_argument("not found name location villager");
    }
}

std::vector<NameVillagers> Villager::moveLocation(const NameLocation& cheklocaitonVIllager) {
    
    if(villagers.empty()) {
        return {};
    }
    
    auto chek = std::find_if(locationVillager.map.begin(), locationVillager.map.end(), [&cheklocaitonVIllager](const auto& p) {
        return p.first == cheklocaitonVIllager;
    });
    auto villagersAtLocation = chek->second.getNameVillagers();

    
    if(chek != locationVillager.map.end()) {
        if(villagersAtLocation.empty()) {
            return {};
        }
    }
    else {
        throw std::invalid_argument("");
    }

    while (true)
    {
        
        
        std::cout << "Do you want to move the villagers with the hero? (yes,no): ";
        
        std::string yesOrNO;
        std::cin >> yesOrNO;
        std::transform(yesOrNO.begin(), yesOrNO.end(), yesOrNO.begin(), ::tolower);
        
        
        if(yesOrNO == "no") {
            return {};
        }
        else if(yesOrNO == "yes") {
            break;
        }
        std::cout << "Invalid input, Please enter 'yes' or 'no'\n";
    }
    
    for(const auto& coutNameVillager: villagersAtLocation) {
        // std::cout << coutNameVillager << std::endl;
    }

    int numberVillager;
    if(villagersAtLocation.size() ==1) {
        numberVillager = 1;
    }
    else {
        std::cout << "Enter the number of ordinary people you want to select: ";
        std::cin >> numberVillager;
    }

    
    if(numberVillager > villagersAtLocation.size() || numberVillager <= 0) {
        std::cout << "eshtebah!!!!!1" << std::endl;
        return {};
    }

    std::vector<NameVillagers> nameVillagerMove;

    std::cout << "Enter the name Villager move: ";

    for(int i = 0; i < numberVillager; ++i) {
        std::string name;
        std::cin >> name;

        nameVillagerMove.emplace_back(chengNameVillager(name));
    }

    for (const auto& name : nameVillagerMove) {
        if (std::find(villagersAtLocation.begin(), villagersAtLocation.end(), name) == villagersAtLocation.end()) {
            return {};
        }
    }

    return nameVillagerMove;
}

NameVillagers Villager::guideVillager(std::vector<NameLocation> nameLocations) {
    std::vector<NameVillagers> chekNameVillager;

    for(const auto& nameLocation : nameLocations) {
        auto chek = std::find_if(locationVillager.map.begin(), locationVillager.map.end(), [&nameLocation](const auto& p) {
            return p.first == nameLocation;
        });
        if(chek != locationVillager.map.end()) {
            auto nameVillagerInTheLocation = chek->second.getNameVillagers();
            if(nameVillagerInTheLocation.empty()) {
                // std::cout << nameLocation;

                for(const auto& nameVillagers : nameVillagerInTheLocation) {
                    // std::cout  << nameVillagers;
                    chekNameVillager.emplace_back(nameVillagers);
                }
            }
        }

    }
    bool trueOrfalse = true;
    
    std::cout << "Enter the name of the villager you want to take to the hero's location: ";
    std::string inputNameVillagerMove;
    std::cin >> inputNameVillagerMove;
    auto nameVillagerMove = chengNameVillager(inputNameVillagerMove);
    if (std::find(chekNameVillager.begin(), chekNameVillager.end(), nameVillagerMove) == chekNameVillager.end()) {
        throw std::invalid_argument("Villager not found");
    }
    else {
        return nameVillagerMove;
    }
}
void Villager::chekSafeLocationVillager(const NameVillagers& nameVilager) {
    auto chek = std::find_if(villagers.begin(), villagers.end(), [this](const auto& p) {
        return p.first == nameVillager;
    });
    if(chek != villagers.end()) {
        if(chek->second.getSafeLocationVillager() == chek->second.getLocationVillager()) {
            // std::cout << "Villager " << nameVilager << " safe location" << std::endl;
            chek->second.removeVillager(nameVilager);
        }
    }
    else {
        throw std::invalid_argument("");
    }
}

std::vector<std::pair<NameVillagers, Villager>> Villager::villagers;

