#ifndef board_hpp
#define board_hpp

#include <string>
#include <vector>

#include "grid.hpp"
#include "battleship.hpp"
#include "ship.hpp"

using std::vector;
using std::string;

class Board
{
public:
    enum PlayerType { Human, Computer };
    Board();
    Board(PlayerType);
    ShotResult attack(Coordinate);
    void markShot(Coordinate, bool);
    void addShip(Ship newShip);
    inline void setPlayerType(PlayerType p) { playerType = p; }
    inline PlayerType getPlayerType() { return playerType; }
    inline void setName(string n) { playerName = n; }
    inline string getName() { return playerName; }
    bool getLost();
    friend ostream& operator<< (ostream&, const Board&);
private:
    Grid shotGrid;
    Grid shipGrid;
    string playerName;
    vector<Ship> ships;
    PlayerType playerType;
};

#endif /* board_hpp */
