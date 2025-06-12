// Map.h
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Location.hpp"
#include <memory>

class Map {
private:
    // std::string namePlayer;
    // std::unordered_map<std::string, Location*> locations;
    // std::unordered_map<std::string, Location*> playerPositions;

    std::unordered_map<std::string, std::shared_ptr<Location>> locations; 
    std::unordered_map<std::string, std::shared_ptr<Location>> playerPositions;  

    void addLoation(const std::string&);
    void connectLocaiton(const std::string&, const std::string&);
public:
    
    Map();
    Map(const Map&) = delete;
    Map operator =(const Map&) = delete;

    static Map& getInstance();

    void totalLocation();
    void negiborLocation();
    void getPlayersLocation(const std::string&);
    std::string findShortestPath(const std::string&, const std::string&);
    
    void setPlayerPosition(const std::string&, const std::string&);
    Location* getPlayerPosition(const std::string&) const;

    void printNeighbors();
    void print();
    void printPlayers() const;

};

#endif
