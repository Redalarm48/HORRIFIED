#ifndef DRACULA_HPP
#define DRACULA_HPP

#include "Monster.hpp"

class Dracula : public Monster
{

    public :

        Dracula(Map& map);

        void usePower(Heroes &h) override;
        void move(const Position& target) override;
        void attack() override;
        void applyItem(const std::vector<Item>& items) override;

};

#endif