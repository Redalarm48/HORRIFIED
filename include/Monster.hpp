#pragma once

#include "NameEnum.hpp"
#include "Map.hpp"
// #include "Games.hpp"
#include "Hero.hpp"
#include <iostream>
#include <vector>
#include <climits>

enum class DiceResult { None, Power, Attack };

class Map;
class Villager;
class Heroes;
class Item;
class Games;

class Monster
{
    private:

        static int terrorLevel;
        const NameMonster nameMonster;
        NameLocation nameLocationMonster;
        static NameMonster FrenzyOrder;
        Map& locationMonster;


    public :

        Monster(const NameMonster&, Map&, const NameLocation&);

        virtual ~Monster();


        NameMonster getNameM() const;
        NameMonster getFrenzyOrder() const;
        NameLocation getNameLocationMonster() const;
        Map& getLocationMonster() const;

        void setMonsterPosition(const NameLocation&);

        DiceResult rollDice();

        void removeMonster();

        bool cheknumberDistance(const NameLocation&);

};

#endif