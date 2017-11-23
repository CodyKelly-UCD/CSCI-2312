#ifndef battleship_hpp
#define battleship_hpp

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

using std::string;
using std::pair;

const char HIT = 'h',
           MISS = 'm',
           EMPTY = ' ',
           HORIZONTAL = 'H',
           VERTICAL = 'V';

const pair<string, int> SHIPS[] =
{
    // Pairing ship names with lengths
    pair<string, int>("Carrier", 5),
    pair<string, int>("Battleship", 4),
    pair<string, int>("Cruiser", 3),
    pair<string, int>("Submarine", 3),
    pair<string, int>("Destroyer", 2)
};

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

class Board
{
public:
    enum PlayerType { Human, Computer };
    inline Board() { }
    Board(PlayerType);
    bool attack(Coordinate c);
    void addShip(Ship newShip);
    void setPlayerType(PlayerType);
    void setName(string);
private:
    Grid shotGrid;
    string playerName;
    vector<Ship> ships;
    PlayerType playerType;
};

class Game
{
private:
    enum Difficulty { Easy, Normal, Hard };
    bool singlePlayer = true;
    Board* boards[2]; // Holds board for both players
    void randomizeShips(Board&);
    Coordinate getPlayerAttack(Board);
    Coordinate getAIAttack(Board[2]);
    Ship getShipFromPlayer(string, Board*);
    Ship getShipRandomly(string, Board*);
    void readShips(Board*);
    void run();
public:
    inline Game() { }
    void start();
};

#endif /* battleship_hpp */
