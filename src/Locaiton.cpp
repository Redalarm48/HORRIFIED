#include "Location.hpp"

Location::Location(const std::string& nameLocaiton) {
    this->nameLocation = nameLocaiton;
}

const std::string& Location::getName() const {
    return nameLocation;
}

void Location::addNeighbor(Location* neighbor) {
    neighbors.push_back(neighbor);
}

const std::vector<Location*>& Location::getNeighbors() const {
    return neighbors;
}
std::ostream& operator<<(std::ostream& os, const Location& loc) {
    os << "Location: " << loc.getName(); // یا هر اطلاعات دیگه‌ای که خواستی
    return os;
}
void Location::addPlayer(const std::string& name) {
    players.push_back(name);
}

void Location::removePlayer(const std::string& name) {
    auto it = std::find(players.begin(), players.end(), name);
    if (it != players.end()) {
        players.erase(it);
    }
}

std::vector<std::string> Location::getPlayers() const {
    return players;
}

