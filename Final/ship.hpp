#ifndef ship_hpp
#define ship_hpp

#include <vector>
#include <string>

#include "battleship.hpp"

using std::string;
using std::vector;

class Ship
{
private:
    int length = 0, posX = 0, posY = 0;
    char orientation = ' ';
    bool sunk = false;
    vector<bool> hits = vector<bool>();
    string name = "";
    
public:
    Ship(string, int, int, char);
    inline bool getSunk() const { return sunk; }
    int getNumberOfHits() const;
    bool attack(Coordinate c);
    inline void setPosX(int x) { posX = x; }
    inline void setPosY(int y) { posY = y; }
    inline int getLength() { return length; }
    inline void setOrientation(char o) { orientation = o; }
    inline char getOrientation() { return orientation; }
    inline Coordinate getPosition() { return Coordinate(posX, posY); }
    vector<Coordinate> getCoordinatesContained();
    bool containsCoordinate(Coordinate);
};

#endif /* ship_hpp */
