#ifndef battleship_hpp
#define battleship_hpp

#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::pair;
using std::cout;
using std::cin;
using std::endl;

extern const char HIT, MISS, EMPTY, HORIZONTAL, VERTICAL;

extern const pair<string, int> SHIPS[5];

struct Coordinate
{
    int x;
    int y;
    Coordinate(int _x, int _y) : x(_x), y(_y) { }
};

class ExceptionShotCoordinateOccupied { };
class ExceptionShipPlacementOccupied { };
class ExceptionShipOutOfBounds { };
class ExceptionInvalidShipName { };

extern const string title;

int getMenuChoice(int numChoices, string message = "");

string getStringInput();

string to_lowercase(string s);

void clearScreen();

#endif /* battleship_hpp */
