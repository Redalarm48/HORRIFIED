#ifndef DRACULA_HPP
#define DRACULA_HPP

#include "Monster.hpp"

class Dracula : public Monster
{

    public :

        Dracula();

        void usePower() override;
        void move(const Position& target) override;
        void attack() override;
        void applyItem(const std::vector<Item>& items) override;

};

#endif