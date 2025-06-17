#ifndef ITEM_HPP
#define ITEM_HPP


#include <string>
#include "Position.hpp"
#include "Map.hpp"

enum class itemType { RED, BLUE , YELLOW};

class Item
{

    private :

        std::string name;
        itemType type;
        bool collected;
        Map& locationItem;

    public :

        Item(itemType type , Map& locationitem , std::string Name);
        std::string getName()const;
        itemType getType()const;
        Position getPosition()const;
        bool isCollected()const;
        Location* getLocationItemPtr() const;
        std::string getLocationItem() const;

        void collect();

};

#endif