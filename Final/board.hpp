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
    ~Board();
    ShotResult attack(Coordinate);
    void markShot(Coordinate, bool);
    void addShip(Ship);
    inline void setPlayerType(PlayerType p) { playerType = p; }
    inline PlayerType getPlayerType() const { return playerType; }
    inline void setName(string n) { playerName = n; }
    inline string getName() const { return playerName; }
    void printShipGrid() const;
    void removeShips();
    bool getLost() const;
    inline vector<Ship*> getShips() const { return ships; }
    friend ostream& operator<< (ostream&, const Board&);
private:
    Grid shotGrid;
    Grid shipGrid;
    string playerName;
    vector<Ship*> ships;
    PlayerType playerType;
};

#endif /* board_hpp */
