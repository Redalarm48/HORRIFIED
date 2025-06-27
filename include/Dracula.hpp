#ifndef DRACULA_HPP
#define DRACULA_HPP

#include "Monster.hpp"

class Dracula : public Monster
{

    public :

        Dracula(Map& map);

        void usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) override;
        void move(const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) override;
        void attack() override;
        void applyItem(const std::vector<Item>& items) override;

};

#endif