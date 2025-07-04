#include "Map.hpp"
#include "Item.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <memory>

Map::Map() {
    totalLocation();
    negiborLocation();
}

Map& Map::getInstance() {
    static Map instance;
    return instance;
}

void Map::addLoation(const std::string& nameLocation) {
    if(locations.find(nameLocation) == locations.end()) {
        // locations[nameLocation] = new Location(nameLocation);
        locations[nameLocation] = std::make_shared<Location>(nameLocation);

    }
    
}

void Map::connectLocaiton(const std::string& start, const std::string& end) {
    addLoation(start);
    addLoation(end);
    locations[start]->addNeighbor(locations[end].get());
    locations[end]->addNeighbor(locations[start].get());
}

void Map::totalLocation() {
    addLoation("cave");               addLoation("museum");             addLoation("hospital");
    addLoation("camp");               addLoation("crypt");              addLoation("church");
    addLoation("precinct");           addLoation("abbey");              addLoation("laboratory");
    addLoation("inn");                addLoation("mansion");            addLoation("graveyard");
    addLoation("barn");               addLoation("shop");               addLoation("institute");
    addLoation("dungeon");            addLoation("docks");              addLoation("theatre");           
    addLoation("tower");              addLoation("brake");

}

void Map::negiborLocation() {
    connectLocaiton("cave", "camp");
    connectLocaiton("camp", "precinct");
    connectLocaiton("camp", "mansion");
    connectLocaiton("camp", "theatre");
    connectLocaiton("camp", "inn");
    connectLocaiton("precinct", "inn");
    connectLocaiton("precinct", "mansion");
    connectLocaiton("precinct", "theatre");
    connectLocaiton("inn", "theatre");
    connectLocaiton("inn", "mansion");
    connectLocaiton("theatre", "barn");
    connectLocaiton("theatre", "tower");
    connectLocaiton("theatre", "shop");
    connectLocaiton("theatre", "mansion");
    connectLocaiton("mansion", "abbey");
    connectLocaiton("mansion", "shop");
    connectLocaiton("mansion", "church");
    connectLocaiton("mansion", "museum");
    connectLocaiton("abbey", "crypt");
    connectLocaiton("museum", "shop");
    connectLocaiton("museum", "church");
    connectLocaiton("church", "hospital");
    connectLocaiton("church", "graveyard");
    connectLocaiton("church", "shop");
    connectLocaiton("shop", "laboratory");
    connectLocaiton("laboratory", "institute");
    connectLocaiton("tower", "dungeon");
    connectLocaiton("tower", "docks");

}

std::vector<std::string> Map::getPlayersLocation(const std::string& locationName) const {
    std::vector<std::string> playersAtLocation;

    for (const auto& pair : playerPositions) {
        const std::string& playerName = pair.first;
        auto loc = pair.second;

        if (loc && loc->getName() == locationName) {
            playersAtLocation.push_back(playerName);
        }
    }

    return playersAtLocation;
}

std::string Map::findShortestPath(const std::string& start, const std::string& end) {
   
    std::unordered_map<std::string, std::string> parent;
    std::queue<Location*> loc;
    loc.push(locations[start].get());
    parent[start] = "";

    while (!loc.empty()) {
        Location* current = loc.front();
        loc.pop();
        std::string currentName = current->getName();
        if(currentName == end) 
            break;
        for (Location* neighbor : current->getNeighbors()) {
            std::string neighName = neighbor->getName();
            if(parent.find(neighName) == parent.end()) {
                parent[neighName] = currentName;
                loc.push(neighbor);
            }
        }
    }

    
    std::vector<std::string> path;
    for(std::string at = end; !at.empty(); at = parent[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    if (path.size() >= 2) {
    return path[1];  // مسیر بعدی از start
} else {
    return "";  // یا یه پیغام خطا، یا همون start
}

}

bool Map::isNeighbor(const std::string& from, const std::string& to) const {
    auto it = locations.find(from);
    if (it == locations.end()) return false;

    for (Location* neighbor : it->second->getNeighbors()) {
        if (neighbor->getName() == to) {
            return true;
        }
    }
    return false;
}


void Map::setPlayerPosition(const std::string& PlayerName, const std::string& locationName) {
    if(locations.find(locationName) != locations.end()) {
        auto locationPtr = locations[locationName];
        playerPositions[PlayerName] = locationPtr;
        locationPtr->addPlayer(PlayerName);
    }
}

std::string Map::getPlayerPosition(const std::string& playerName) const {
    auto it = playerPositions.find(playerName);
    if(it != playerPositions.end()) {
        return it->second->getName();
        
    }
    return "";
}

Location* Map::getPlayerPositionPtr(const std::string& name) const {
    auto it = playerPositions.find(name);
    if (it != playerPositions.end()) {
        return it->second.get();
    }
    return nullptr;
}

void Map::printPlayers() const {
    std::cout << "\nPlayer Positions:\n";
    for (const auto& pair : playerPositions) {
        std::cout << " " << pair.first << " in " << pair.second->getName() << "\n";
    }
}

void Map::print() {
    for(const auto& pair : locations) {
        auto loc = pair.second;
        std::cout << "Location: " << loc->getName() << "\n";
        std::cout << " Neighbors: ";
        for(Location* neighbor : loc->getNeighbors()) {
            std::cout << neighbor->getName() << " ";
        }
        std::cout << "\n";
    }
}

void Map::removePlayer(const std::string& name) {
    auto it = playerPositions.find(name);
    if (it != playerPositions.end()) {
        if (it->second) {
            it->second->removePlayer(name);
        }
        playerPositions.erase(it);
    }
}


std::vector<Item*> Map::getItemsAt(const std::string& locationName) const {
    std::vector<Item*> result;

    auto it = locations.find(locationName);  //  تغییر دادیم از playerPositions به locations
    if (it == locations.end()) {
        std::cout << "[Debug] Location '" << locationName << "' not found in locations.\n";
        return result;
    }

    std::cout << "[Debug] Checking items at location '" << locationName << "'.\n";

    for (const std::string& name : it->second->getPlayers()) {
        if (name.rfind("item_", 0) == 0) {
            Item* item = Item::findByName(name);
            if (item) {
                result.push_back(item);
            }
        }
    }

    return result;
}

std::vector<std::string> Map::getAllLocationNames() const {
    std::vector<std::string> names;
    for (const auto& [name, _] : locations) {
        names.push_back(name);
    }
    return names;
}


std::unordered_map<std::string, std::shared_ptr<Location>> Map::locations;
std::unordered_map<std::string, std::shared_ptr<Location>> Map::playerPositions;

