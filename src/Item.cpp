#include "Item.hpp"
#include "Map.hpp"

Item::Item(Map& map) : locationItem(map) , nameItem(NameItem::ANALYSIS), typeItem(TypeItem::BLUE){}

Item::Item(TypeItem typeItem, Map& locationItem ,NameItem nameItem, NameLocation nameLocation, int power, TypeOwnership typeOwnsership) : typeItem(typeItem), locationItem(locationItem), nameItem(nameItem), nameLocationItem(nameLocation), power(power) {
    this->collected = false;
    this->typeOwnership = typeOwnership;
}

NameItem Item::getNameItem() const {
    return nameItem;
}

TypeItem Item::getTypeItem() const {
    return typeItem;   
}

bool Item::isCollected()const {
    return collected;
}

void Item::collectTrue() {
    collected = true;
}

NameLocation Item::getLocationItem() const {
    return nameLocationItem;
}

TypeOwnership Item::getTypeOwnsership() const {
    return typeOwnership;
}

NameItem Item::addItemInGame() {
    auto additem = this->itemList.addItemInGame();
    Item item(additem.typeitem, locationItem, additem.nameitem, additem.namelocation, additem.power);
    this->itemsInGame.emplace_back(additem.nameitem, item);
    auto chek = std::find_if(locationItem.map.begin(), locationItem.map.end(), [&additem](const auto& p) {
        return p.first == additem.namelocation;
    });
    if(chek == locationItem.map.end()) {
        throw std::invalid_argument("not fount item");
    }
    chek->second.addItem(item.nameItem);
    return item.nameItem;
}
void Item::removeItemInGame(const NameItem& nameItem) {
    auto chek = std::find_if(itemsInGame.begin(), itemsInGame.end(), [&nameItem](const auto& p) {
        return p.first == nameItem;
    });
     if(chek == itemsInGame.end()) {
        throw std::invalid_argument("not name item in the remove item in game");
     }
    auto chekNameItem = chek->second.getLocationItem();
    auto chek2 = std::find_if(this->locationItem.map.begin(), this->locationItem.map.end(), [&chekNameItem](const auto& p) {
        return p.first == chekNameItem;
    });
    if(chek != itemsInGame.end() && chek2 != this->locationItem.map.end()) {
        chek2->second.removeItem(nameItem);
        
    }
    this->itemsInGame.erase(chek);
}


void Item::setItemsPosition(const NameLocation& newLocationItem) {
    if(this->nameLocationItem == newLocationItem) {
        return;
    }
    auto chek = std::find_if(locationItem.map.begin(), locationItem.map.end(), [&newLocationItem](const auto& p) {
        return p.first == newLocationItem;
    });
    auto chek2 = std::find_if(locationItem.map.begin(), locationItem.map.end(), [this](const auto& p) {
        return p.first == this->nameLocationItem;
    });

    if(chek != locationItem.map.end() && chek2 != locationItem.map.end()) {
        chek->second.addItem(nameItem);
        chek2->second.removeItem(nameItem);
        this->nameLocationItem = newLocationItem;
    }
    else {
        throw std::invalid_argument("not found locaiton");
    }
}

void Item::setItemsPosition(const NameItem& nameItem, const NameLocation& newLocationItem) {
    auto chek = std::find_if(this->itemsInGame.begin(), this->itemsInGame.end(), [&nameItem](const auto& p) {
        return p.first == nameItem;
    });
    if(chek == this->itemsInGame.end()) {
        throw std::invalid_argument("not fount name item");
    }
    chek->second.setItemsPosition(newLocationItem);
}

void Item::setTypeOwnsership(const TypeOwnership& newTypeOwnsership) {
    this->typeOwnership = newTypeOwnsership;
}

void Item::pickUp(const NameHeroes& nameHero, const NameItem& nameItem) {
    auto chek = std::find_if(this->itemsInGame.begin(), this->itemsInGame.end(), [&nameItem](const auto& p) {
        return p.first == nameItem;
    });
    if(chek == this->itemsInGame.end()) {
        throw std::invalid_argument("not fount name item");
    }

    chek->second.setItemsPosition(NameLocation::Default);

    std::cout << chek->second.getLocationItem();


    switch (nameHero)
    {
    case NameHeroes::MAYOR:
        chek->second.setTypeOwnsership(TypeOwnership::MAYOR);
        return;
        break;
    case NameHeroes::ARCHAEOLOGIST:
        chek->second.setTypeOwnsership(TypeOwnership::ARCHAEOLOGIST);
        return;
        break;
    default:
        throw std::invalid_argument("hl");
        break;
    }

}

ItemList::ItemList(TypeItem typeitem,NameLocation namelocation, NameItem nameitem, int power)  {
    this->typeitem = typeitem;
    this->namelocation = namelocation;
    this->nameitem = nameitem;
    this->power = power;
}
ItemList::ItemList() {
    initializeItem();
    shuffleItem();   
}

void ItemList::addItemList(TypeItem type,NameLocation namelocation, NameItem name, int pow) {
    itemlist.emplace_back(type, namelocation, name, pow);
}

void ItemList::initializeItem() {
    addItemList(TypeItem::YELLOW, NameLocation::DOCKS  , NameItem::FLOWER , 2);
    addItemList(TypeItem::YELLOW, NameLocation::CAMP  , NameItem::TAROT_DECK , 3);
    addItemList(TypeItem::YELLOW, NameLocation::INN  , NameItem::GARLIC , 2);
    addItemList(TypeItem::YELLOW, NameLocation::MANSION  , NameItem::MIRRORED_BOX , 3);
    addItemList(TypeItem::YELLOW, NameLocation::ABBEY  , NameItem::STAKE , 3);
    addItemList(TypeItem::YELLOW, NameLocation::MUSEUM  , NameItem::SCROLL_OF_THOTH , 4);
    addItemList(TypeItem::YELLOW, NameLocation::CAMP  , NameItem::VIOLIN , 3);
    addItemList(TypeItem::YELLOW, NameLocation::MUSEUM  , NameItem::TABLET , 3);
    addItemList(TypeItem::YELLOW, NameLocation::CAMP  , NameItem::WOLFSBANE , 4);
    addItemList(TypeItem::YELLOW, NameLocation::CAMP  , NameItem::CHARM , 4);
    addItemList(TypeItem::RED, NameLocation::INN , NameItem::DART , 2);
    addItemList(TypeItem::RED, NameLocation::MANSION , NameItem::FIRE_POKER , 3);
    addItemList(TypeItem::RED, NameLocation::THEATRE , NameItem::RAPIER , 5);
    addItemList(TypeItem::RED, NameLocation::GRAVEYARD , NameItem::SHOVEL , 2);
    addItemList(TypeItem::RED, NameLocation::BARN , NameItem::TORCH , 5);
    addItemList(TypeItem::RED, NameLocation::BARN , NameItem::PITCHFORK , 4);
    addItemList(TypeItem::RED, NameLocation::BARN , NameItem::RIFLE , 6);
    addItemList(TypeItem::RED, NameLocation::SHOP , NameItem::SILVER_CANE , 6);
    addItemList(TypeItem::RED, NameLocation::DOCKS , NameItem::KNIFE , 3);
    addItemList(TypeItem::RED, NameLocation::PRECINCT , NameItem::PISTOL , 6);
    addItemList(TypeItem::RED, NameLocation::SHOP , NameItem::BEAR_TRAP , 4);
    addItemList(TypeItem::RED, NameLocation::INSTITUTE , NameItem::SPEARGUN , 4);
    addItemList(TypeItem::BLUE, NameLocation::INSTITUTE , NameItem::ANATOMY_TEXT , 1);
    addItemList(TypeItem::BLUE, NameLocation::LABORATORY , NameItem::CENTRIFUGE , 1);
    addItemList(TypeItem::BLUE, NameLocation::TOWER , NameItem::KITE , 1);
    addItemList(TypeItem::BLUE, NameLocation::TOWER , NameItem::RESARCH , 2);
    addItemList(TypeItem::BLUE, NameLocation::MANSION , NameItem::TELESCOPE , 2);
    addItemList(TypeItem::BLUE, NameLocation::PRECINCT , NameItem::SEARCHLIGHT , 2);
    addItemList(TypeItem::BLUE, NameLocation::LABORATORY , NameItem::EXPERIMENT , 2);
    addItemList(TypeItem::BLUE, NameLocation::INSTITUTE , NameItem::ANALYSIS , 2);
    addItemList(TypeItem::BLUE, NameLocation::INSTITUTE , NameItem::ROTENONE , 3);
    addItemList(TypeItem::BLUE, NameLocation::TOWER , NameItem::COSMIC_RAY_DIFFUSER , 3);
    addItemList(TypeItem::BLUE, NameLocation::TOWER , NameItem::NEBULARLUM , 3);
    addItemList(TypeItem::BLUE, NameLocation::INN , NameItem::MONOCANE_MIXTURE , 3);
    addItemList(TypeItem::BLUE, NameLocation::CAMP , NameItem::FOSSIL , 3);
}


void ItemList::shuffleItem() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(itemlist.begin(), itemlist.end(), g);
}


ItemList ItemList::addItemInGame() {
    if(itemlist.empty()) {
        throw std::runtime_error("No more Item");

    }
    ItemList itemAdd = itemlist.back();
    itemlist.pop_back();
    return itemAdd;
}


std::string Item::chengNameItemTheString(const NameItem& item) {
    switch (item) {
        case NameItem::FLOWER: return "Flower"; break;
        case NameItem::TAROT_DECK: return "Tarot Deck"; break;
        case NameItem::GARLIC: return "Garlic"; break;
        case NameItem::MIRRORED_BOX: return "Mirrored Box"; break;
        case NameItem::STAKE: return "Stake"; break;
        case NameItem::SCROLL_OF_THOTH: return "Scroll Of Thoth"; break;
        case NameItem::VIOLIN: return "Violin"; break;
        case NameItem::TABLET: return "Tablet"; break;
        case NameItem::WOLFSBANE: return "Wolfsbane"; break;
        case NameItem::CHARM: return "Charm"; break;
        case NameItem::DART: return "Dart"; break;
        case NameItem::FIRE_POKER: return "Fire Poker"; break;
        case NameItem::RAPIER: return "Rapier"; break;
        case NameItem::SHOVEL: return "Shovel"; break;
        case NameItem::TORCH: return "Torch"; break;
        case NameItem::PITCHFORK: return "Pitchfork"; break;
        case NameItem::RIFLE: return "Rifle"; break;
        case NameItem::SILVER_CANE: return "Silver Cane"; break;
        case NameItem::KNIFE: return "Knife"; break;
        case NameItem::PISTOL: return "Pistol"; break;
        case NameItem::BEAR_TRAP: return "Bear Trap"; break;
        case NameItem::SPEARGUN: return "Speargun"; break;
        case NameItem::ANATOMY_TEXT: return "Anatomy Text"; break;
        case NameItem::CENTRIFUGE: return "Centrifuge"; break;
        case NameItem::KITE: return "Kite"; break;
        case NameItem::RESARCH: return "Resarch"; break;
        case NameItem::TELESCOPE: return "Telescope"; break;
        case NameItem::SEARCHLIGHT: return "Searchlight"; break;
        case NameItem::EXPERIMENT: return "Experiment"; break;
        case NameItem::ANALYSIS: return "Analysis"; break;
        case NameItem::ROTENONE: return "Rotenone"; break;
        case NameItem::COSMIC_RAY_DIFFUSER: return "Cosmic Ray Diffuser"; break;
        case NameItem::NEBULARLUM: return "Nebularlum"; break;
        case NameItem::MONOCANE_MIXTURE: return "Monocane Mixture"; break;
        case NameItem::FOSSIL: return "Fossil"; break;
        default: throw std::invalid_argument(" ");
    }
    return "";
}

NameLocation Item::itemMaxLocation() {
    NameLocation nameLocationMaxItem = NameLocation::Default;
    int size = 0;
    for(const auto& [name, location] : this->locationItem.map) {
        if(size < location.getNameItems().size()) {
            nameLocationMaxItem = name;
            size = location.getNameItems().size();
        }
    }
    return nameLocationMaxItem;
}

void Item::removeAllItemLocation(const NameLocation& nameLocation) {
    auto chek = std::find_if(this->locationItem.map.begin(), this->locationItem.map.end(), [&nameLocation](const auto& p) {
        return p.first == nameLocation;
    });
    if(chek != this->locationItem.map.end()) {
        auto allItemLocation = chek->second.getNameItems();
        for(const auto& i : allItemLocation) {
            this->removeItemInGame(i);
        }
    }
    else {
        throw std::invalid_argument("not found name location the remove all item locaiton");
    }
}

std::list<std::pair<NameItem, Item>> Item::getItemsInGame() const {
    return itemsInGame;
}


int Item::getPower() const {
    return this->power;
}

std::list<std::pair<NameItem, Item>> Item::itemsInGame;
std::vector<ItemList> ItemList::itemlist;
ItemList Item::itemList;

