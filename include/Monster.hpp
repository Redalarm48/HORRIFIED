#pragma once

#include "NameEnum.hpp"
#include "Map.hpp"
// #include "Games.hpp"
#include "Hero.hpp"
#include <iostream>
#include <vector>
#include <climits>

class Map;
class Villager;
class Heroes;
class Item;
class Games;

class Monster
{
    private :

        static int terrorLevel;
        const NameMonster nameMonster;
        NameLocation nameLocationMonster;
        static NameMonster FrenzyOrder;
        Map& locationMonster;


    public :

        Monster(const NameMonster&, Map&, const NameLocation&);

        virtual ~Monster();


        NameMonster getNameM() const;
        int getFrenzyOrder() const;
        bool isDead() const;

        void setMonsterPosition(const NameLocation&);

        bool cheknumberDistance(const NameLocation&);

        void Defeated();
        NameLocation getNameLocationMonster() const;

};

#endif