#ifndef ITEM_HPP
#define ITEM_HPP


#include <string>
#include "Position.hpp"

enum class itemType { RED, BLUE , YELLOW};

class Item
{

    private :

        itemType type;
        Position position;
        bool collected;

    public :

        Item(itemType type , Position position);
        itemType getType()const;
        Position getPosition()const;
        bool isCollected()const;

        void collect();
        void setPosition(Position newPosition);

};

#endif