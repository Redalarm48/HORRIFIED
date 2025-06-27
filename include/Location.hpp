#if !defined(LOCATION_H)
#define LOCATION_H

#include <string>
#include <istream>
#include <vector>
#include <algorithm>


class Location {

friend std::ostream& operator<<(std::ostream& os, const Location& loc);

private:
    std::string nameLocation;
    std::vector<Location*> neighbors;
    std::vector<std::string> players;
public:
    Location(const std::string& nameLocation);
    const std::string& getName() const;
    void addNeighbor(Location* neighbor);
    const std::vector<Location*>& getNeighbors() const;
    void addPlayer(const std::string& name);
    void removePlayer(const std::string& name);
    std::vector<std::string> getPlayers() const;
};

#endif
