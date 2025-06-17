#include "InvisibleMan.hpp"

InvisibleMan::InvisibleMan(Map& map) : Monster("InvisibleMan" , 6 , map){}

void InvisibleMan::usePower(Heroes &h)
{

    //باید کد اجرای قدرت هیولا زده شه اول

    std::cout << "InvisibleMan cause chaos \n";

}

void InvisibleMan::move(const Position& target)
{

    //کوتاه ترین مسیرو نفهمیدم

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