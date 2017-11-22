#ifndef battleship_hpp
#define battleship_hpp

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

using namespace std;

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
    inline ShotAlreadyFired(Coordinates c) : coordinates(c) {}
    inline Coordinates getCoordinates() { return coordinates; }
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
    inline bool getSunk() const { return sunk; }
    int getNumberOfHits() const;
    bool attack(Coordinates c);
    inline void setPosX(int x) { posX = x; }
    inline void setPosY(int y) { posY = y; }
    void setLength(int len);
    inline void setHorizontal(bool h) { horizontal = h; }
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
