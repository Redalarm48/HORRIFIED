#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

class Position
{

    private :

        int X;
        int Y;

    public :

        Position();
        Position(int x , int y){}

        int getX() const;
        int getY() const;
        int setX(int x);
        int setY(int y);
        int set(int x , int y);
        bool isNear(const Position& other)const;
        int distanceFrom(const Position& other)const;
        bool operator==(const Position& other)const;

};

#endif

