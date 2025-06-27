#include "..\include\Item.hpp"
#include "..\include\Map.hpp"

Item::Item(itemType type , Map* locationitem , const std::string& Name) : type(type) , collected(false) , locationItem(locationitem) , name(Name) {}


std::string Item::getName()const
{

    return name;

}

itemType Item::getType()const
{

    return type;
    
}

bool Item::isCollected()const
{

    return collected;

}

void Item::collect()
{

    collected = true;

}

Location* Item::getLocationItemPtr() const
{

    return this->locationItem->getPlayerPositionPtr(name); 

}

std::string Item::getLocationItem() const 
{

    return this->locationItem->getPlayerPosition(name);

}
Item* Item::findByName(const std::string& name) {
    for (Item* item : allItems) {
        if (item->getName() == name) return item;
    }
    return nullptr;
}

std::vector<Item*> Item::allItems;