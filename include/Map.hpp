#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <iostream>
#include "Position.hpp"
#include "Item.hpp"

class Map {

    private:

        int width;
        int height;
        std::vector<std::vector<char>> grid;


    public:
    
        Map(int w = 10, int h = 10); 
        void clear();
        void placeItem(const Item& item);
        void placeChar(const Position& pos, char symbol);
        void display() const;
        bool isValidPosition(const Position& pos) const;

};

#endif
