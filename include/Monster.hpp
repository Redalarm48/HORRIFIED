#ifndef MONSTER_HPP
#define MONSTER_HPP
#include "NameEnum.hpp"
#include "Map.hpp"
#include <iostream>
#include <vector>

class Map;

class Monster
{
    private :

        const NameMonster nameMonster;
        NameLocation nameLocationMonster;
        int FrenzyOrder;
        Map& locationMonster;
        bool Dead;

    public :

        Monster(const NameMonster, int, Map&);

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