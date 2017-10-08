#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "battleship.hpp"

using namespace std;
using namespace Battleship;

void makeLowercase(string &s)
{
    for (auto c : s)
    {
        c = tolower(c);
    }
}

/*
Ship Implementation
*/

Ship::Ship(string name, int len, int x, int y, bool horiz) : length(len), posX(x), posY(y), horizontal(horiz), hits(len) {}

Ship::Ship(string n, int len) : length(len), posX(0), posY(0), horizontal(true), hits(len), name(n) {}

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

bool Ship::attack(Coordinates c)
{
    bool hit = false;
    
    // Check if shot is a hit
    if (horizontal && c.y == posY && c.x >= posX && c.x < posX + length)
    {
        hits[c.x - posX] = true;
        hit = true;
    }
    else if (!horizontal && c.x == posX && c.y >= posY && c.y < posY + length)
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

void Ship::setLength(int len)
{
    length = len;
    hits.resize(len);
};

Board::Board() : Grid(10, 10) {}

bool Board::attack(Coordinates c)
{
    bool hit = false;
    try
    {
        if (getValue(c.x, c.y) == ' ')
        {
            // If any of the ships report a hit, change the board value
            // and return true
            for (auto ship : ships)
            {
                if (ship.attack(c))
                {
                    setValue(c.x, c.y, HITCHAR);
                    hit = true;
                    break;
                }
            }
            
            // If no ships report a hit, mark it as misss
            if (!hit)
            {
                setValue(c.x, c.y, MISSCHAR);
            }
        }
        else
        {
            throw ShotAlreadyFired(c);
        }
    }
    catch (ShotAlreadyFired shot)
    {
        // If the coordinates given have already been tried, tell the user and return
        // the value already on the board.
        
        Coordinates c = shot.getCoordinates();
        cout << "These coordinates have already been tried. Enter another.\n";
        hit = getValue(c.x, c.y) == 'h';
    }
    
    return hit;
}

void Board::addShip(Ship newShip)
{
    ships.push_back(newShip);
}

Game::Game() { }

void Game::start()
{
    string choice;
    int players = 0;
    
    cout << "\n\nWelcome to Battleship!\n\n";
    cout << "One player or two: ";
    
    do
    {
        getline(cin, choice);
        makeLowercase(choice);
        
        if (choice == "1" || choice[0] == 'o')
        {
            cout << "Starting a one player game...\n";
            players = 1;
        }
        else if (choice == "2" || choice[0] == 't')
        {
            cout << "Starting a two player game...\n";
            players = 2;
        }
        else
        {
            cout << "Invalid input, please input a 1 or 2: ";
        }
    } while (players == 0);
}
