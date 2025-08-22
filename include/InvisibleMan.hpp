#pragma once
#include "Monster.hpp"

class InvisibleMan : public Monster
{

private:
    bool chek = false;

    public :
    
        InvisibleMan(Map& map);
        

        bool moveMonster(Villager&,Heroes&, Heroes&, Heroes&, Heroes&, bool = false) override;
        void power(Villager&, Heroes&, Heroes&) override;
};

