#include "Position.hpp"

Position::Position() : X(0) , Y(0){}

Position::Position(int x , int y) : X(x) , Y(y){}

int Position::getX() const
{

    return X;

}

int Position::getY() const
{

    return Y;

}

int Position::setX(int x)
{

    X = x;

}

int Position::setY(int y)
{

    Y = y;

}

int Position::set(int x , int y)
{

    X = x;
    Y= y;

}

bool Position::isNear(const Position& other)const
{

    int dx = std:: abs(X - other.X);
    int dy = std:: abs(Y - other.Y);
    return (dx + dy == 1);

}

int Position::distanceFrom(const Position& other)const
{

    return(std:: abs(X - other.X) + std:: abs(Y - other.Y));

}

bool Position::operator==(const Position& other)const
{

    return(X == other.X && Y == other.Y);

}
