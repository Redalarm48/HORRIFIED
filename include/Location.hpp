#if !defined(LOCATION_H)
#define LOCATION_H

#include <string>
#include <istream>
#include <vector>

class Location {

friend std::ostream& operator<<(std::ostream& os, const Location& loc);

private:
    std::string nameLocation;
    std::vector<Location*> neighbors;
public:
    Location(const std::string& nameLocation);
    const std::string& getName() const;
    void addNeighbor(Location* neighbor);
    const std::vector<Location*>& getNeighbors() const;
};

#endif // LOCATION_H
