#ifndef ITEM_HPP
#define ITEM_HPP


#include <string>
#include <vector>
#include "Position.hpp"
#include "Location.hpp"


enum class itemType { RED, BLUE , YELLOW};

class Map; 

class Item
{

    private :

        std::string name;
        itemType type;
        bool collected;
        Map* locationItem;
        

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



        void collect();

};

#endif