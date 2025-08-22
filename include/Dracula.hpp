#pragma once

#include "Monster.hpp"
#include "Hero.hpp"

class Dracula : public Monster
{

    public :

        Dracula(Map& map);

        void power(Villager&, Heroes&, Heroes&) override;
        bool moveMonster(Villager&, Heroes&, Heroes&, Heroes&, Heroes&, bool = false) override;


};