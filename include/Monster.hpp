#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Item.hpp"
#include "Map.hpp"
#include "Villagers.hpp"
#include "Hero.hpp"
#include <iostream>
#include <vector>

class Monster
{

    private :

        std::string Name;
        int FrenzyOrder;
        Map& locationMonster;
        bool Dead;

    public :

        Monster(const std:: string& name , int frenzyorder , Map& locationmonster);

        virtual ~Monster();

        std::string getNameM() const;
        int getFrenzyOrder() const;
        bool isDead() const;

        void Defeated();
        Location* getLocationMonsterPtr() const;
        std::string getLocationMonster() const;
        Map& getMap() const;

        virtual void usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers);
        virtual void move(const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers);

};

#endif