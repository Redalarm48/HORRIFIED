#include "..\include\Item.hpp"

Item::Item(itemType type , Position position) : type(type) , position(position) , collected(false){}


itemType Item::getType()const
{

    return type;
    
}
Position Item::getPosition()const
{

    return position;

}
bool Item::isCollected()const
{

    return collected;

}

void Item::collect()
{

    collected = true;

}
void Item::setPosition(Position newPosition)
{

    position = newPosition;

}
