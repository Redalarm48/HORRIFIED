#include "Dracula.hpp"

Dracula::Dracula(Map& map) : Monster("Dracula" , 1 , map) {}



        void Dracula::usePower(Heroes &h)
        {
            
            h.getLocation().setPlayerPosition(h.getName() , getLocationMonster());
            std::cout << "Dracula Hypnotized someone , Last Hero in charge moves to the Dracula.\n";
            //باید آخرین قهرمان آخرین بازیکنی که بازی کرده منتقل بشه

        }

        void Dracula::move(const Position& target)
        {

            //کوتاه ترین مسیرو نفهمیدم

        }

        void Dracula::attack()
        {

            //کد های مربوط به حمله هم کامل نیست هنوز
            std::cout << "Dracula attacks!!!\n";

        }

        void Dracula::applyItem(const std::vector<Item>& items)
        {

            //اینجا هم باید کد تاثیر یک آیتم بر دراکولا رو بزنیم
            std::cout << "Dracula affected by items\n";

        }
