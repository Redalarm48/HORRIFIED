#include "Map.hpp"
#include "NameEnum.hpp"
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <memory>
#include <fstream>



Map::Map() {
    totalLocation();
    negiborLocation();
}

Map& Map::getInstance() {
    static Map instance;
    return instance;
}

std::ostream& operator<<(std::ostream& os, NameLocation namelocation) {
    switch (namelocation)
    {
    case NameLocation::ABBEY:
        os << "abbey";
    case NameLocation::CAVE: 
        os << "cave";
    case NameLocation::CAMP: 
        os << "camp";
    case NameLocation::PRECINCT: 
        os << "precinct";
    case NameLocation::INN: 
        os << "inn";
    case NameLocation::BARN:
        os << "barn";
    case NameLocation::DUNGEON: 
        os << "dungeon";
    case NameLocation::TOWER: 
        os << "tower";
    case NameLocation::MUSEUM: 
        os << "museum";
    case NameLocation::CRYPT: 
        os << "crypt";
    case NameLocation::MANSION: 
        os << "mansion";
    case NameLocation::SHOP: 
        os << "shop";
    case NameLocation::DOCKS: 
        os << "docks";
    case NameLocation::HOSPITAL: 
        os << "hospital";
    case NameLocation::CHURCH: 
        os << "church";
    case NameLocation::LABORATORY: 
        os << "laboratory";
    case NameLocation::GRAVEYARD: 
        os << "graveyard";
    case NameLocation::INSTITUTE: 
        os << "institute";
    case NameLocation::THEATRE: 
        os << "theatr";
    default:
        throw std::invalid_argument("");
    }
    return os;
}

void Map::addLoation(const NameLocation& nameLocation) {
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek == map.end()) {
        Location newLocation(nameLocation);
        map.emplace_back(nameLocation, newLocation);
    }

    else {
        throw std::invalid_argument("");
    }
}

void Map::connectLocaiton(const NameLocation& start, const NameLocation& end) {
    auto chek = std::find_if(map.begin(), map.end(), [&start](const auto& p) {
        return p.first == start;
    });

    auto chek2 = std::find_if(map.begin(), map.end(), [&end](const auto& p) {
        return p.first == end;
    });
    
    if(chek != map.end() && chek2 != map.end()) {
        chek->second.addNeighbor(&chek2->second);
        chek2->second.addNeighbor(&chek->second);
    }
}



void Map::totalLocation() {
    addLoation(NameLocation::CAVE);
    addLoation(NameLocation::CAMP);
    addLoation(NameLocation::PRECINCT);
    addLoation(NameLocation::INN);
    addLoation(NameLocation::BARN);
    addLoation(NameLocation::DUNGEON);
    addLoation(NameLocation::TOWER);
    addLoation(NameLocation::MUSEUM);
    addLoation(NameLocation::CRYPT);
    addLoation(NameLocation::ABBEY);
    addLoation(NameLocation::MANSION);
    addLoation(NameLocation::SHOP);
    addLoation(NameLocation::DOCKS);
    addLoation(NameLocation::HOSPITAL);
    addLoation(NameLocation::CHURCH);
    addLoation(NameLocation::LABORATORY);
    addLoation(NameLocation::GRAVEYARD);
    addLoation(NameLocation::INSTITUTE);
    addLoation(NameLocation::THEATRE);
}

void Map::negiborLocation() {
    connectLocaiton(NameLocation::CAVE, NameLocation::CAMP);
    connectLocaiton(NameLocation::CAMP, NameLocation::PRECINCT);
    connectLocaiton(NameLocation::CAMP, NameLocation::MANSION);
    connectLocaiton(NameLocation::CAMP, NameLocation::THEATRE);
    connectLocaiton(NameLocation::CAMP, NameLocation::INN);
    connectLocaiton(NameLocation::PRECINCT, NameLocation::INN);
    connectLocaiton(NameLocation::PRECINCT, NameLocation::MANSION);
    connectLocaiton(NameLocation::PRECINCT, NameLocation::THEATRE);
    connectLocaiton(NameLocation::INN, NameLocation::THEATRE);
    connectLocaiton(NameLocation::INN, NameLocation::MANSION);
    connectLocaiton(NameLocation::THEATRE, NameLocation::BARN);
    connectLocaiton(NameLocation::THEATRE, NameLocation::TOWER);
    connectLocaiton(NameLocation::THEATRE, NameLocation::SHOP);
    connectLocaiton(NameLocation::THEATRE, NameLocation::MANSION);
    connectLocaiton(NameLocation::MANSION, NameLocation::ABBEY);
    connectLocaiton(NameLocation::MANSION, NameLocation::SHOP);
    connectLocaiton(NameLocation::MANSION, NameLocation::CHURCH);
    connectLocaiton(NameLocation::MANSION, NameLocation::MUSEUM);
    connectLocaiton(NameLocation::ABBEY, NameLocation::CRYPT);
    connectLocaiton(NameLocation::MUSEUM, NameLocation::SHOP);
    connectLocaiton(NameLocation::MUSEUM, NameLocation::CHURCH);
    connectLocaiton(NameLocation::CHURCH, NameLocation::HOSPITAL);
    connectLocaiton(NameLocation::CHURCH, NameLocation::GRAVEYARD);
    connectLocaiton(NameLocation::CHURCH, NameLocation::SHOP);
    connectLocaiton(NameLocation::SHOP, NameLocation::LABORATORY);
    connectLocaiton(NameLocation::LABORATORY, NameLocation::INSTITUTE);
    connectLocaiton(NameLocation::TOWER, NameLocation::DUNGEON);
    connectLocaiton(NameLocation::TOWER, NameLocation::DOCKS);
}

std::vector<NameHeroes> Map::getHeroesLocation(const NameLocation& nameLocation) const {
    // std::vector<std::string> playersAtLocation;

    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {

        
        // for (const auto& pair : playerPositions) {
        //     const std::string& playerName = pair.first;
        //     auto loc = pair.second;
            
        //     if (loc && loc->getName() == nameLocation) {
        //         playersAtLocation.push_back(playerName);
        //     }
        // }
        
        return chek->second.getNameHeroes();

        // return playersAtLocation;
    }
}
std::vector<NameMonster> Map::getMonsterLocation(const NameLocation& nameLocation) const {
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {
        return chek->second.getNameMonsters();
    }
}
std::vector<NameItem> Map::getItemsLocation(const NameLocation& nameLocation) const {
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {
        return chek->second.getNameItems();
    }
}
std::vector<NameVillagers> Map::getVillagerLocaiton(const NameLocation& nameLocation) const {
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {
        return chek->second.getNameVillagers();
    }
}

std::vector<Location*> Map::getNeighborLocation(const NameLocation& nameLocation) const {
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {
        return chek->second.getNeighbors();
    }
}
NameLocation Map::findShortestPath(const NameLocation& start, const NameLocation& end) {
    std::unordered_map<NameLocation, NameLocation> parent;
    std::queue<Location*> q;

    // پیدا کردن اشاره‌گر به start
    Location* startPtr = nullptr;
    for (auto& pair : map) {
        if (pair.first == start) {
            startPtr = &pair.second;
            break;
        }
    }
    if (!startPtr) 
        throw std::invalid_argument("");

    q.push(startPtr);
    parent[start] = start;

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        // گرفتن نام فعلی
        NameLocation currentName;
        bool found = false;
        for (const auto& pair : map) {
            if (&pair.second == current) {
                currentName = pair.first;
                found = true;
                break;
            }
        }
        if (!found) continue;

        if (currentName == end) break;

        for (Location* neighbor : current->getNeighbors()) {
            // گرفتن نام neighbor
            NameLocation neighName;
            bool neighFound = false;
            for (const auto& pair : map) {
                if (&pair.second == neighbor) {
                    neighName = pair.first;
                    neighFound = true;
                    break;
                }
            }
            if (!neighFound) continue;

            if (parent.find(neighName) == parent.end()) {
                parent[neighName] = currentName;
                q.push(neighbor);
            }
        }
    }

    if (parent.find(end) == parent.end())
        throw std::invalid_argument("");
    std::vector<NameLocation> path;
    for (NameLocation at = end; at != start; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    if (path.size() >= 2) {
        // برگرداندن اسم مکان دوم در مسیر (قدم بعدی)
        NameLocation next = path[1];

        // پیدا کردن رشته اسم آن مکان
        for (const auto& pair : map) {
            if (pair.first == next)
                return pair.second.getNameLocation();
        }
    }

        throw std::invalid_argument("");
}

NameLocation Map::chengNameLocationTheString(const std::string& nameLocation) {
    static const std::unordered_map<std::string, NameLocation> nameMap = {
        {"cave", NameLocation::CAVE},
        {"camp", NameLocation::CAMP},
        {"precinct", NameLocation::PRECINCT},
        {"inn", NameLocation::INN},
        {"barn", NameLocation::BARN},
        {"dungeon", NameLocation::DUNGEON},
        {"tower", NameLocation::TOWER},
        {"museum", NameLocation::MUSEUM},
        {"crypt", NameLocation::CRYPT},
        {"abbey", NameLocation::ABBEY},
        {"mansion", NameLocation::MANSION},
        {"shop", NameLocation::SHOP},
        {"docks", NameLocation::DOCKS},
        {"hospital", NameLocation::HOSPITAL},
        {"church", NameLocation::CHURCH},
        {"laboratory", NameLocation::LABORATORY},
        {"graveyard", NameLocation::GRAVEYARD},
        {"institute", NameLocation::INSTITUTE},
        {"theatre", NameLocation::THEATRE}
    };

    auto it = nameMap.find(nameLocation);
    if (it != nameMap.end())
        return it->second;
    else
        throw std::invalid_argument("");
}


std::vector<NameLocation> Map::getAllLocationNames() const {
    std::vector<NameLocation> names;
    for (const auto& [name, loc] : map) {
        names.push_back(loc.getNameLocation());
    }
    return names;
}

std::vector<NameLocation> Map::getNeighbors(const NameLocation& nameLocation) const {
    std::vector<NameLocation> result;

    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });
    if(chek != map.end()) {

        const auto& loc = chek->second;
        for (Location* neighbor : loc.getNeighbors()) {
            result.push_back(neighbor->getNameLocation());
        }
        return result;
    }
    else {
        throw std::invalid_argument("");
    }
} 