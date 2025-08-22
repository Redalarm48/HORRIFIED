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
        break;
    case NameLocation::CAVE: 
        os << "cave";
        break;
    case NameLocation::CAMP: 
        os << "camp";
        break;
    case NameLocation::PRECINCT: 
        os << "precinct";
        break;
    case NameLocation::INN: 
        os << "inn";
        break;
    case NameLocation::BARN:
        os << "barn";
        break;
    case NameLocation::DUNGEON: 
        os << "dungeon";
        break;
    case NameLocation::TOWER: 
        os << "tower";
        break;
    case NameLocation::MUSEUM: 
        os << "museum";
        break;
    case NameLocation::CRYPT: 
        os << "crypt";
        break;
    case NameLocation::MANSION: 
        os << "mansion";
        break;
    case NameLocation::SHOP: 
        os << "shop";
        break;
    case NameLocation::DOCKS: 
        os << "docks";
        break;
    case NameLocation::HOSPITAL: 
        os << "hospital";
        break;
    case NameLocation::CHURCH: 
        os << "church";
        break;
    case NameLocation::LABORATORY: 
        os << "laboratory";
        break;
    case NameLocation::GRAVEYARD: 
        os << "graveyard";
        break;
    case NameLocation::INSTITUTE: 
        os << "institute";
        break;
    case NameLocation::THEATRE: 
        os << "theatr";
        break;
    case NameLocation::Default:
        os << "default";
        break;
    default:
        throw std::invalid_argument("not found location");
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
        throw std::invalid_argument("not found name location ");
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
    addLoation(NameLocation::Default);
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
    auto chek = std::find_if(map.begin(), map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });

    if(chek != map.end()) {
                return chek->second.getNameHeroes();
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

template <class T>
T Map::findShortestPath(const NameLocation& start, const NameLocation& end) {
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
        throw std::invalid_argument("Start location not found");

    q.push(startPtr);
    parent[start] = start;

    while (!q.empty()) {
        Location* current = q.front();
        q.pop();

        // گرفتن نام فعلی
        NameLocation currentName = NameLocation::Default;
        for (const auto& pair : map) {
            if (&pair.second == current) {
                currentName = pair.first;
                break;
            }
        }
        if (currentName == NameLocation::Default) {
            throw std::runtime_error("Current location not found in map");
        }
        if (currentName == end) break;

        for (Location* neighbor : current->getNeighbors()) {
            // گرفتن نام neighbor
            NameLocation neighName = NameLocation::Default;
            for (const auto& pair : map) {
                if (&pair.second == neighbor) {
                    neighName = pair.first;
                    break;
                }
            }
            if (neighName == NameLocation::Default) {
                throw std::runtime_error("Neighbor not found in map");
            }

            if (parent.find(neighName) == parent.end()) {
                parent[neighName] = currentName;
                q.push(neighbor);
            }
        }
    }

    if (parent.find(end) == parent.end())
        throw std::invalid_argument("No path found");

    std::vector<NameLocation> path;
    for (NameLocation at = end; at != start; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());

    if (path.size() >= 1) {
        // برگرداندن اسم مکان دوم در مسیر (قدم بعدی)
         if constexpr (std::is_same_v<T, int>) {
            return static_cast<int>(path.size() - 1);
        } else if constexpr (std::is_same_v<T, NameLocation>) {
            return path[1];
        } else {
            static_assert(sizeof(T) == 0, "Unsupported type for findShortestPath");
        }
    }
    throw std::runtime_error("Path too short");
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
        throw std::invalid_argument("not found name locaiton");
}

std::string Map::chengNameLocationTheString(const NameLocation& nameLocaiton) {
    switch (nameLocaiton)
    {
        case NameLocation::CAVE:        return "cave";
        case NameLocation::CAMP:        return "camp";
        case NameLocation::PRECINCT:    return "precinct";
        case NameLocation::INN:         return "inn";
        case NameLocation::BARN:        return "barn";
        case NameLocation::DUNGEON:     return "dungeon";
        case NameLocation::TOWER:       return "tower";
        case NameLocation::MUSEUM:      return "museum";
        case NameLocation::CRYPT:       return "crypt";
        case NameLocation::ABBEY:       return "abbey";
        case NameLocation::MANSION:     return "mansion";
        case NameLocation::SHOP:        return "shop";
        case NameLocation::DOCKS:       return "docks";
        case NameLocation::HOSPITAL:    return "hospital";
        case NameLocation::CHURCH:      return "church";
        case NameLocation::LABORATORY:  return "laboratory";
        case NameLocation::GRAVEYARD:   return "graveyard";
        case NameLocation::INSTITUTE:   return "institute";
        case NameLocation::THEATRE:     return "theatre";
    }
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
        throw std::invalid_argument("not found neighbors");
    }
} 

bool Map::getInvisibleItemCollecte() const {
    for(const auto& [name, map] : map) {
        if( name == NameLocation::INN||
            name == NameLocation::BARN||
            name == NameLocation::INSTITUTE||
            name == NameLocation::LABORATORY||
            name == NameLocation::MANSION ) {
                if(!map.getInvisibleItemCollecte()) {
                    return false;
                }
        }
    }
    return true;
}


bool Map::getcoffinDestroyed() const {
    for(const auto& [name, map] : map) {
        if( name == NameLocation::CAVE||
            name == NameLocation::CRYPT||
            name == NameLocation::DUNGEON||
            name == NameLocation::GRAVEYARD ) {
                if(!map.getCoffindestroyed()) {
                    return false;
                }
        }
    }
    return true;
}

template int Map::findShortestPath<int>(const NameLocation&, const NameLocation&);
template NameLocation Map::findShortestPath<NameLocation>(const NameLocation&, const NameLocation&);
