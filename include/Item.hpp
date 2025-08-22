#pragma once

#include <string>
#include <vector>
#include "Hero.hpp"
#include "Location.hpp"
#include "Map.hpp"
#include <list>

class Map;

enum class TypeOwnership {
    ARCHAEOLOGIST, MAYOR, 
    COURIER, SCIENTIST,
    NO_OWNERSHIP
};

enum class TypeItem { 
    RED, BLUE , YELLOW
};


struct ItemList
{
public:
   
    TypeItem typeitem;
    NameItem nameitem;
    NameLocation namelocation;
    int power;
    static std::vector<ItemList> itemlist;
    ItemList(TypeItem typeitem,NameLocation namelocation, NameItem nameitem, int power);
    ItemList();
    void addItemList(TypeItem type, NameLocation, NameItem name, int pow);
    void initializeItem();
    void shuffleItem();
    ItemList addItemInGame();
};

class Item
{

private :

    static ItemList itemList;
    Map& locationItem;
    const NameItem nameItem;
    const TypeItem typeItem;
    TypeOwnership typeOwnership;
    NameLocation nameLocationItem;
    int power;
    bool collected;
    
public :
    
    static std::list<std::pair<NameItem, Item>> itemsInGame;
    
    Item(TypeItem, Map&, NameItem, NameLocation, int, TypeOwnership = TypeOwnership::NO_OWNERSHIP);
    Item(Map&);
    Item(const Item&) = default;
    Item(Item&&) = default;
    Item& operator=(const Item&) = default;
    Item& operator=(Item&&) = default;

    int getPower() const;
    NameLocation getLocationItem() const;
    NameItem getNameItem() const;
    TypeItem getTypeItem()const;
    TypeOwnership getTypeOwnsership() const;
    std::list<std::pair<NameItem, Item>> getItemsInGame() const;


    bool isCollected()const;
    void collectTrue();
    NameItem addItemInGame();
    void removeItemInGame(const NameItem&); 

    void setItemsPosition(const NameLocation&);
    void setItemsPosition(const NameItem&, const NameLocation&);
    void setTypeOwnsership(const TypeOwnership&);

    static std::string chengNameItemTheString(const NameItem&);

    void pickUp(const NameHeroes&, const NameItem&);
    NameLocation itemMaxLocation();
    void removeAllItemLocation(const NameLocation&);

};