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
    bool attack(Coordinate c);
    void addShip(Ship newShip);
    void setPlayerType(PlayerType);
    void setName(string);
    friend ostream& operator<< (ostream&, const Board&);
private:
    Grid shotGrid;
    Grid shipGrid;
    string playerName;
    vector<Ship> ships;
    PlayerType playerType;
};

#endif /* board_hpp */
