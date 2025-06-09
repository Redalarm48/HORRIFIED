#include "..\include\Map.hpp"

Map::Map(int w, int h) : width(w) , height(h) , grid(h, std::vector<char>(w, '.')) {}

void Map::clear()
{

    for (int y = 0; y < height; ++y)
    {

        for (int x = 0; x < width; ++x)
        {

            grid[y][x] = '.';
        
        }
    
    }


}

void Map::placeItem(const Item& item)
{

    if (!item.isCollected())
    {

        Position pos = item.getPosition();
        char symbol = '?';

        switch (item.getType())
        {

            case itemType::RED:    symbol = 'R'; break;
            case itemType::BLUE:   symbol = 'B'; break;
            case itemType::YELLOW: symbol = 'Y'; break;
        
        }

        if (isValidPosition(pos))
        {

            grid[pos.getY()][pos.getX()] = symbol;

        }

    }

}

void Map::placeChar(const Position& pos, char symbol)
{

    if (isValidPosition(pos))
    {

        grid[pos.getY()][pos.getX()] = symbol;

    }


}

void Map::display() const
{

    for (int y = 0; y < height; ++y)
    {

        for (int x = 0; x < width; ++x)
        {

            std::cout << grid[y][x] << ' ';

        }
        std::cout << '\n';

    }

}

bool Map::isValidPosition(const Position& pos) const
{

    return (pos.getX() >= 0 && pos.getX() < width && pos.getY() >= 0 && pos.getY() < height);

}
