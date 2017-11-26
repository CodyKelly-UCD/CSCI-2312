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
    int x = 0;
    int y = 0;
    Coordinate() : x(0), y(0) { }
    Coordinate(int _x, int _y) : x(_x), y(_y) { }
};

struct ShotResult
{
    Coordinate shotPosition;
    bool hit;
    string shipSunk;
    ShotResult() : shotPosition(Coordinate(0, 0)), hit(false), shipSunk("") { }
    ShotResult(Coordinate c, bool h, string s) : shotPosition(c), hit(h), shipSunk(s) { }
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
