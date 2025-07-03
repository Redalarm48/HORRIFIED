// Map.h
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Location.hpp"
#include "Item.hpp"
#include <memory>

class Item;

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
    std::vector<std::string> getPlayersLocation(const std::string&) const;
    std::string findShortestPath(const std::string&, const std::string&);
    bool isNeighbor(const std::string& from, const std::string& to) const;

    void setPlayerPosition(const std::string&, const std::string&);
    std::string getPlayerPosition(const std::string&) const;
    Location* getPlayerPositionPtr(const std::string&) const;
    void printNeighbors();
    void print();
    void printPlayers() const;
    void removePlayer(const std::string& name);
    std::vector<Item*> getItemsAt(const std::string& location) const;
    std::vector<std::string> getAllLocationNames() const; 


};

#endif
