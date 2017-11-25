#include "ship.hpp"

Ship::Ship(string n, int x, int y, char o) : name(n), posX(x), posY(y), orientation(o)
{
    length = getShipLengthFromName(name);
    hits.resize(length);
}

Ship::Ship() { }

int Ship::getNumberOfHits() const
{
    int count = 0;
    
    for (bool hit : hits)
    {
        if (hit)
        {
            count++;
        }
    }
    
    return count;
}

bool Ship::attack(Coordinate c)
{
    bool hit = false;
    
    // Check if shot is a hit
    if (orientation == HORIZONTAL && c.y == posY && c.x >= posX && c.x < posX + length)
    {
        hits[c.x - posX] = true;
        hit = true;
    }
    else if (orientation == VERTICAL && c.x == posX && c.y >= posY && c.y < posY + length)
    {
        hits[c.y - posY] = true;
        hit = true;
    }
    
    // Check if the boat's been sunk
    if (getNumberOfHits() == length)
    {
        sunk = true;
    }
    
    return hit;
}

void Ship::setLength(int l)
{
    length = l;
    hits.resize(l);
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
