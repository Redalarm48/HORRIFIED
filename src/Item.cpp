#include "Item.hpp"
#include "Map.hpp"

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
Item* Item::findByName(const std::string& name, const std::vector<Item*>& itemList) {
    for (Item* item : itemList) {
        if (item->getName() == name) return item;
    }
    return nullptr;
}

std::string Item::getPickedUpFrom() const
{

    return pickedUpFrom;

} 

void Item:: setPickedUpFrom(const std::string& loc) 
{ 
    pickedUpFrom = loc; 
}
