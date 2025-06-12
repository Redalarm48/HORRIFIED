#include "Map.hpp"
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
    addLoation("tower"); 

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


void Map::getPlayersLocation(const std::string& locationName) {  
    std::cout << "People in location: " << locationName << "\n";

    bool found = false;
    for (const auto& pair : playerPositions) {
        const std::string& playerName = pair.first;
        auto loc = pair.second;

        if (loc && loc->getName() == locationName) {
            std::cout << " - " << playerName << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << " (no one is here)\n";
    }
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
    return path[1];
}

void Map::setPlayerPosition(const std::string& PlayerName, const std::string& locationName) {
    if(locations.find(locationName) != locations.end()) {
        playerPositions[PlayerName] = locations[locationName];
    }
}

Location* Map::getPlayerPosition(const std::string& playerName) const {
    auto it = playerPositions.find(playerName);
    if(it != playerPositions.end()) {
        return it->second.get();
    }
    return nullptr;
}
void Map::printPlayers() const {
    std::cout << "\nPlayer Positions:\n";
    for (const auto& pair : playerPositions) {
        std::cout << " " << pair.first << " → " << pair.second->getName() << "\n";
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