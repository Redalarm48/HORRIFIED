#ifndef ITEM_HPP
#define ITEM_HPP


#include <string>
#include <vector>
#include "Position.hpp"
#include "Hero.hpp"
#include "Location.hpp"
#include "Map.hpp"

class Map;


enum class itemType { RED, BLUE , YELLOW};


class Item
{

    private :

        std::string name;
        itemType type;
        bool collected;
        Map* locationItem;
        std::string pickedUpFrom = "";
        

    public :

        Item(itemType type , Map* locationitem , const std::string& Name);
        Item(const Item&) = default;
        Item(Item&&) = default;
        Item& operator=(const Item&) = default;
        Item& operator=(Item&&) = default;
        std::string getName()const;
        itemType getType()const;
        Position getPosition()const;
        bool isCollected()const;
        Location* getLocationItemPtr() const;
        std::string getLocationItem() const;
        static Item* findByName(const std::string& name);
        static std::vector<Item*> allItems;
        std::string getPickedUpFrom() const; 
        void setPickedUpFrom(const std::string& loc);

        void collect();

};

#endif