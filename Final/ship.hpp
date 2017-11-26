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
    int hits = 0;
    string name = "";
    
public:
    Ship();
    Ship(string, int, int, char);
    inline string getName() const { return name; }
    inline void setName(string n) { name = n; }
    inline bool getSunk() const { return sunk; }
    bool attack(Coordinate c);
    inline void setPosX(int x) { posX = x; }
    inline void setPosY(int y) { posY = y; }
    inline int getLength() const { return length; }
    inline int getHits() const { return hits; }
    void setLength(int);
    inline void setOrientation(char o) { orientation = o; }
    inline char getOrientation() const { return orientation; }
    inline Coordinate getPosition() { return Coordinate(posX, posY); }
    vector<Coordinate> getCoordinatesContained() const;
    bool containsCoordinate(Coordinate);
};

#endif /* ship_hpp */
