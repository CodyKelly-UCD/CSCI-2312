#include <algorithm>

#include "watervehicle.hpp"

void WaterVehicle::setLength(int l)
{
    length = l;
    hits.resize(l);
}

int WaterVehicle::getLength()
{
    return length;
}

void WaterVehicle::setPosition(pair<int, int> pos)
{
    position = pos;
}

pair<int, int> WaterVehicle::getPosition()
{
    return position;
}

void WaterVehicle::setOrientation(Orientation o)
{
    _orientation = o;
}

WaterVehicle::Orientation WaterVehicle::getOrientation()
{
    return _orientation;
}

bool WaterVehicle::getSunk()
{
    return sunk;
}

bool WaterVehicle::attack(pair<int, int> shotPos)
{
    bool hit = false, alreadyHitAtPos = false;
    
    // First we'll check to see if there's already a hit at the given position.
    // If we have, we'll return true (signifying a hit), and we won't have to
    // do hit calculations.
    for (auto h : hits)
    {
        if (h == shotPos)
        {
            alreadyHitAtPos = true;
            hit = true;
        }
    }
    
    // If there isn't a hit at the position already, check if the shot is a hit
    if (!alreadyHitAtPos)
    {
        if (_orientation == vertical && shotPos.first == position.first && shotPos.second > position.second && shotPos.second < position.second + length)
        {
            hit = true;
            hits.push_back(shotPos);
        }
        else if (_orientation == horizontal && shotPos.second == position.second && shotPos.first > position.first && shotPos.first < position.first + length)
        {
            hit = true;
            hits.push_back(shotPos);
        }
    }
    
    return hit;
}
