#ifndef battleship_hpp
#define battleship_hpp

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

const char HIT = 'h',
           MISS = 'm',
           EMPTY = ' ',
           HORIZONTAL = 'H',
           VERTICAL = 'V';

const std::pair<string, int> SHIPS[] =
{
    // Pairing ship names with lengths
    pair<string, int>("Carrier", 5),
    pair<string, int>("Battleship", 4),
    pair<string, int>("Cruiser", 3),
    pair<string, int>("Submarine", 3),
    pair<string, int>("Destroyer", 2)
};

struct Coordinates
{
    int x;
    int y;
};

class ExceptionShotCoordinatesOccupied { };
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
    bool attack(Coordinates c);
    inline void setPosX(int x) { posX = x; }
    inline void setPosY(int y) { posY = y; }
    void setLength(int len);
    inline void setOrientation(char o) { orientation = o; }
};

class Board : public Grid
{
public:
    enum PlayerType { Human, Computer };
    inline Board() : Grid(10, 10) { }
    Board(PlayerType);
    void attack(Coordinates c);
    void addShip(Ship newShip);
    void setPlayerType(PlayerType);
    void setName(string);
private:
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
    Coordinates getPlayerAttack(Board);
    Coordinates getAIAttack(Board[2]);
    void readShips(Board&);
    void run();
public:
    inline Game() { }
    void start();
};

#endif /* battleship_hpp */
