#ifndef INVISIBLE_HPP
#define INVISIBLE_HPP

#include "Monster.hpp"

class InvisibleMan : public Monster
{

    public :
    
        InvisibleMan();

        void usePower() override;
        void move(const Position& target) override;
        void attack() override;
        void applyItem(const std::vector<Item>& items) override;
};

#endif