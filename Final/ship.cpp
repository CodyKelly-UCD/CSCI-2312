#include "ship.hpp"

Ship::Ship(string n, int x, int y, char o) : name(n), posX(x), posY(y), orientation(o)
{
    length = getShipLengthFromName(name);
}

Ship::Ship() : name(""), posX(0), posY(0), orientation(EMPTY) { }

bool Ship::attack(Coordinate c)
{
    bool hit = false;
    
    // Check if shot is a hit
    if (orientation == HORIZONTAL && c.y == posY && c.x >= posX && c.x < posX + length)
    {
        hit = true;
        hits++;
        
        // Check if the boat's been sunk
        if (hits == length)
        {
            sunk = true;
        }
    }
    else if (orientation == VERTICAL && c.x == posX && c.y >= posY && c.y < posY + length)
    {
        hit = true;
        hits++;
        
        // Check if the boat's been sunk
        if (hits == length)
        {
            sunk = true;
        }
    }
    
    return hit;
}

void Ship::setLength(int l)
{
    length = l;
}

vector<Coordinate> Ship::getCoordinatesContained() const
{
    vector<Coordinate> coordinates;
    
    for (int count = 0; count < length; count++)
    {
        if (orientation == HORIZONTAL)
        {
            coordinates.push_back(Coordinate(posX + count, posY));
        }
        else
        {
            coordinates.push_back(Coordinate(posX, posY + count));
        }
    }
    
    return coordinates;
}

bool Ship::containsCoordinate(Coordinate coord1)
{
    for (auto coord2 : getCoordinatesContained())
    {
        if (coord1.x == coord2.x && coord2.y == coord1.y)
        {
            return true;
        }
    }
    
    return false;
}
