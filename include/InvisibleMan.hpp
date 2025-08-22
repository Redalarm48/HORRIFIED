#pragma once
#include "Monster.hpp"

class InvisibleMan : public Monster
{

private:
    bool chek = false;

    public :
    
        InvisibleMan(Map& map);


        // void usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) override;
        bool moveMonster(Villager&,Heroes&, Heroes&, Heroes&, Heroes&, bool = false) override;
        void power(Villager&, Heroes&, Heroes&) override;
        // void move();
};