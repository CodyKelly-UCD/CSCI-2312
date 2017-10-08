#ifndef battleship_hpp
#define battleship_hpp

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

using namespace std;

namespace Battleship
{
    const char HITCHAR = 'h', MISSCHAR = 'm';
    
    struct Coordinates
    {
        int x;
        int y;
    };
    
    class ShotAlreadyFired
    {
    private:
        Coordinates coordinates;
    public:
        ShotAlreadyFired(Coordinates c) : coordinates(c) {}
        Coordinates getCoordinates() { return coordinates; }
    };
    
    class Ship
    {
    private:
        int length = 0, posX = 0, posY = 0;
        bool horizontal = false, sunk = false;
        vector<bool> hits;
        string name;
        
    public:
        Ship(string, int, int, int, bool);
        Ship(string, int);
        bool getSunk() const { return sunk; }
        int getNumberOfHits() const;
        bool attack(Coordinates c);
        void setPosX(int x) { posX = x; }
        void setPosY(int y) { posY = y; }
        void setLength(int len);
        void setHorizontal(bool h) { horizontal = h; }
    };
    
    class Board : public Grid
    {
        vector<Ship> ships;
        
    public:
        Board();
        bool attack(Coordinates c);
        void addShip(Ship newShip);
    };
    
    class Game
    {
    private:
        Board playerBoard;
        Board AIBoard;
    public:
        Game();
        void start();
    };
}

#endif /* battleship_hpp */
