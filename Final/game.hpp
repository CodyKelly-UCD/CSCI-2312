#ifndef game_hpp
#define game_hpp

#include <string>

#include "board.hpp"
#include "battleship.hpp"
#include "ship.hpp"

using std::pair;
using std::string;

class Game
{
private:
    enum Difficulty { Easy, Normal, Hard };
    enum GameMode { Regular, Salvo };
    GameMode currentMode = GameMode::Regular;
    Difficulty currentDifficulty = Difficulty::Easy;
    bool singlePlayer = true;
    Board* boards[2]; // Holds board for both players
    void randomizeShips(Board*, bool);
    ShotResult playerAttack(int);
    ShotResult AIAttack(int);
    void addShipRandomly(string, Board*);
    void addShipFromPlayer(string, Board*);
    void printLastTurnResults(vector<ShotResult>);
    void printCurrentTurnResults(vector<ShotResult>);
    void readShips(Board*);
    void run();
public:
    inline Game() { }
    void start();
};

#endif /* game_hpp */
