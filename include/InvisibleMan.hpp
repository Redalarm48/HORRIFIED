#ifndef INVISIBLE_HPP
#define INVISIBLE_HPP

#include "Monster.hpp"

class InvisibleMan : public Monster
{

    public :
    
        InvisibleMan(Map& map);

        void usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) override;
        void move( const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) override;
        void move();
        void attack() override;
        void applyItem(const std::vector<Item>& items) override;
};

#endif