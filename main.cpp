#include <iostream>
#include "Villagers.hpp"
#include "Hero.hpp"
#include "Map.hpp"

int main() {
    Map& map = Map::getInstance();

    Villager vil(map);
    
    Heroes h(10,"parsa", map);
    Heroes sss(4,"reza", map);
    map.setPlayerPosition("parsa", "camp");
    map.setPlayerPosition("reza", "cave");
    h.move();
    // vil.chekSafeLocationVillager("Maleva");

    auto getlcation = map.getPlayersLocation("cave");
    for(auto& i : getlcation) {
        std::cout << i <<  std::endl;
    }

    return 0;
}