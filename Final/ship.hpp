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
    Ship();
    inline string getName() const { return name; }
    inline void setName(string n) { name = n; }
    inline bool getSunk() const { return sunk; }
    int getNumberOfHits() const;
    bool attack(Coordinate c);
    inline void setPosX(int x) { posX = x; }
    inline void setPosY(int y) { posY = y; }
    inline int getLength() const { return length; }
    void setLength(int);
    inline void setOrientation(char o) { orientation = o; }
    inline char getOrientation() const { return orientation; }
    inline Coordinate getPosition() { return Coordinate(posX, posY); }
    vector<Coordinate> getCoordinatesContained() const;
    bool containsCoordinate(Coordinate);
    inline vector<bool> getHits() { return hits; }
};

#endif /* ship_hpp */
