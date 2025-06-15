#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Position.hpp"
#include "Item.hpp"
#include <iostream>
#include <vector>

class Monster
{

    private :

        std::string Name;
        int FrenzyOrder;
        Position position;
        bool Dead;

    public :

        Monster(const std:: string& name , int frenzyorder);

        virtual ~Monster();

        std::string getName() const;
        int getFrenzyOrder() const;
        Position getPosition() const;
        bool isDead() const;

        void setPosition(const Position& newPos);
        void Defeated();

        virtual void usePower();
        virtual void move(const Position& target);
        virtual void attack();
        virtual void applyItem(const std::vector<Item>& items);

};

#endif