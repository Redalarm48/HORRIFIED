#include "Dracula.hpp"

Dracula::Dracula() : Monster("Dracula" , 1) {}

        void Dracula::usePower()
        {

            //باید کد اجرای قدرت هیولا زده شه اول

            std::cout << "Dracula Hypnotized someone , nearest entity moves 1 step closer.\n";

        }

        void Dracula::move(const Position& target)
        {

            std::cout << "Dracula moves from (" << getPosition().getX() << "," << getPosition().getY() << ") to (" << target.getX() << "," << target.getY() << "\n";
            setPosition(target);

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
