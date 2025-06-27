#include "..\include\InvisibleMan.hpp"

InvisibleMan::InvisibleMan(Map& map) : Monster("InvisibleMan" , 6 , map){}

void InvisibleMan::usePower(Heroes &h ,const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers)
{

    std::cout << "InvisibleMan cause chaos \n";
    move(heroes , villagers);
}

void InvisibleMan::move(const std::vector<Heroes*>& heroes, const std::vector<std::pair<std::string, std::string>>& villagers) {
    std::string currentPos = getMap().getPlayerPosition("InvisibleMan");
    for(int steps = 0 ; steps < 2 ; ++steps)
    {    
        std::string closestTarget;
        int minDist = INT_MAX;


        // بررسی روستایی‌ها
        for (const auto& villager : villagers) {
            std::string targetPos = getMap().getPlayerPosition(villager.first);
            int dist = getMap().findShortestPath(currentPos, targetPos).size();
            if (dist < minDist && dist > 1) {
                minDist = dist;
                closestTarget = targetPos;
            }
        }

        if (!closestTarget.empty()) {
            auto path = getMap().findShortestPath(currentPos, closestTarget);
            if (path.size() >= 2) {
                std::string nextStep = path;
                getMap().setPlayerPosition("InvisibleMan", nextStep);
                std::cout << "InvisibleMan" << " moved toward " << closestTarget << " to " << nextStep << "\n";
            }
        }
    }
}



void InvisibleMan::attack()
{

    //کد های مربوط به حمله هم کامل نیست هنوز
    std::cout << "InvisibleMan attacks!!!\n";

}

void InvisibleMan::applyItem(const std::vector<Item>& items)
{

    //اینجا هم باید کد تاثیر یک آیتم بر دراکولا رو بزنیم
    std::cout << "InvisibleMan affected by items\n";

}