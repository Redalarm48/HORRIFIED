#include "..\include\Villagers.hpp"

Villager::Villager(std::string nameVillager,Map& locationVillager, std::string safeLocationVillager) : nameVillager(nameVillager), safeLocationVillager(safeLocationVillager), locationVillager(locationVillager) {
    //initializeVillagers();
}
Villager::Villager(Map& locationVillager) : locationVillager(locationVillager) {
    //initializeVillagers();

}

void Villager::setNameVillager(const std::string& nameVillage) {
    this->nameVillager = nameVillage; 
}
// void Villager::setStatusVillager(const Status& statusVillager) {
//     this->statusVillager = statusVillager;
// }
// void Villager::setLocationVillager(const Map& locationVillager) {
//     this->locationVillager = locationVillager;
// }
 
std::string Villager::getNameVillager() const {
    return nameVillager;
}
// Status Villager::getStatusVillager() const {
//     return statusVillager;
// }
std::string Villager::getLocationVillager() const {
    return locationVillager.getPlayerPosition(nameVillager);
}
std::string Villager::getSafeLocationVillager() const {
    return safeLocationVillager;
}

void Villager::addVillager(std::string nameVillager, std::string locationVillager, std::string safeLocationVillager) {
    this->locationVillager.setPlayerPosition(nameVillager, locationVillager);
    nameAndsafeLocationVilager.emplace_back(nameVillager, safeLocationVillager);
}

void Villager::initializeVillagers() {
    addVillager("Dr.crunly","percinct", "laboratory");
    addVillager("Maleva","shop", "camp");
    addVillager("Fritz","institute", "tower");
    addVillager("Maria","camp", "barn");
    addVillager("Prof.pearson","museum", "cave");
    addVillager("Dr.read","camp", "institute");

}
void Villager::removeVillager(std::string& nameVilager) {
    this->locationVillager.setPlayerPosition(nameVilager, "brake");
}

std::vector<std::string> Villager::moveLocation(std::string location) {
    // std::cout << location;c
    // int numberVillagerLive = 0;
    std::vector<std::string> villagersAtLocation;
    if(nameAndsafeLocationVilager.empty()) {
        return {};
    }

    std::cout << "Do you want to move the villagers with the hero? (yes,no): ";
    std::string yesOrNO;
    std::cin >> yesOrNO;
    if(yesOrNO == "no") {
        return {};
    }
    else if(yesOrNO != "yes") {
        std::cout << "try again: (yes, no): ";
        std::cin >> yesOrNO;
    }
    
    for(auto& i : nameAndsafeLocationVilager) {
        if(i.second == location) {
            villagersAtLocation.push_back(i.first);
            std::cout <<"-"<< i.first << std::endl;
        }
    }

    if(villagersAtLocation.empty()) {
        std::cout << "There are no villagers in this place." << std::endl;
        return {};
    }

    int numberVillager;
    if(villagersAtLocation.size() ==1) {
        numberVillager = 1;
    }
    else {
        std::cout << "Enter the number of ordinary people you want to select: ";
        std::cin >> numberVillager;
    }

    
    if(numberVillager > villagersAtLocation.size() && numberVillager <= 0) {
        std::cout << "eshtebah!!!!!1" << std::endl;
        return {};
    }

    std::vector<std::string> nameVillagerMove;

    std::cout << "Enter the name Villager move: ";

    for(int i = 0; i < numberVillager; ++i) {
        std::string name;
        std::cin >> name;
        nameVillagerMove.push_back(name);
    }

    for (const std::string& name : nameVillagerMove) {
        if (std::find(villagersAtLocation.begin(), villagersAtLocation.end(), name) == villagersAtLocation.end()) {
            std::cout << "name '" << name << "' was not found!\n";
            return {};
        }
    }

    return nameVillagerMove;
}

void Villager::chekSafeLocationVillager(std::string nameVilager) {
    for(auto& chek : nameAndsafeLocationVilager) {
        if(nameVilager == chek.first) {
            auto locationLiveVilager = locationVillager.getPlayerPosition(nameVilager);
            // std::cout << locationLiveVilager << "\n";
            if(chek.second == locationLiveVilager) {
                std::cout << "Villager " << nameVilager << " safe location." << std::endl;
                removeVillager(nameVilager);
            }
        }
    }
}
std::vector<std::pair<std::string, std::string>> Villager::nameAndsafeLocationVilager;


std::vector<std::pair<std::string, std::string>> Villager::getActiveVillagers() const {
    std::vector<std::pair<std::string, std::string>> result;

    for (const auto& pair : nameAndsafeLocationVilager) {
        std::string currentLocation = locationVillager.getPlayerPosition(pair.first);
        if (currentLocation != "brake") { // یعنی هنوز توی نقشه هست
            result.emplace_back(pair.first, currentLocation);
        }
    }

    return result;
}
