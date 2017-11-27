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
extern const int HITCHANCENORMAL, HITCHANCEHARD;
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

std::ostream& operator<< (std::ostream&, const Coordinate);

struct ShotResult
{
    Coordinate shotPosition;
    bool hit;
    bool sunk;
    string shipName;
    ShotResult() : shotPosition(Coordinate(0, 0)), hit(false), sunk(false), shipName("") { }
    ShotResult(Coordinate c, bool h, bool s1, string s2) : shotPosition(c), hit(h), sunk(s1), shipName(s2) { }
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
