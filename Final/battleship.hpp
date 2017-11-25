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
extern const pair<string, int> SHIPTYPES[5];
extern const string title;

extern bool debug;

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

int getMenuChoice(int numChoices, string message = "");
string getStringInput();
string toLowercase(string s);
void clearScreen();
int getShipLengthFromName(string);
void displayTitle();

#endif /* battleship_hpp */
