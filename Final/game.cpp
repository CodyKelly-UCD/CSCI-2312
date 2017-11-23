#include <fstream>
#include <iostream>

#include "game.hpp"

using std::cout;
using std::cin;

Ship Game::getShipFromPlayer(string, Board*) { return Ship("", 1, 1, '1'); }

Ship Game::getShipRandomly(string, Board*) { return Ship("", 1, 1, '1'); }

void Game::readShips(Board *board)
{
    ifstream file("./ship_placement.csv");
    file.ignore(256, '\n'); // ignore first line
    
    for (int shipCount = 5; shipCount > 0; shipCount--)
    {
        string name;
        char x, y;
        char orientation;
        
        getline(file, name, ',');
        name = to_lowercase(name);
        
        file >> x;
        file >> y;
        file.ignore(); // ignore comma
        
        file >> orientation;
        file.ignore(2); // go to next line
        
        Ship newShip = Ship(name, int(x - 'A'), int(y - '1'), orientation);
        
        try
        {
            board->addShip(newShip);
        }
        catch (ExceptionShipOutOfBounds)
        {
            clearScreen();
            cout << "The " << name << " from the file was out of bounds.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                board->addShip(getShipFromPlayer(name, board));
            }
            else
            {
                board->addShip(getShipRandomly(name, board));
            }
        }
        catch (ExceptionShipPlacementOccupied)
        {
            clearScreen();
            cout << "The position for the " << name << " read in from the file was occupied by another ship.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                board->addShip(getShipFromPlayer(name, board));
            }
            else
            {
                board->addShip(getShipRandomly(name, board));
            }
        }
    }
}

void Game::start()
{
    // This function sets up a game.
    // It prints the title, creates boards of specific types
    // (human or computer), gets the names of the players, and when the game
    // is over it asks if the players would like to play again.
    
    // Display title
    clearScreen();
    cout << title;
    cout << setw(44) << "Cody Kelly" << endl;
    cout << setw(43) << "© 2017" << endl << endl;
    cout << "Press enter to continue.\n\n";
    cin.get();
    
    do
    {
        // Display main menu
        clearScreen();
        cout << "\n\nWelcome to Battleship!\n\n";
        cout << "Main Menu\n1) Single player game\n2) Two player game";
        singlePlayer = getMenuChoice(2) == 1;
        clearScreen();
        
        if(singlePlayer)
        {
            // Setup single player game
            string name;
            boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Computer);
            
            cout << "Please enter your name: ";
            name = getStringInput();
            boards[0] -> setName(name);
            
            readShips(boards[0]);
        }
        else
        {
            // Setup multiplayer game
            string name;
            
            boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Human);
            
            cout << "Player 1, please enter your name: ";
            name = getStringInput();
            boards[0] -> setName(name);
            
            clearScreen();
            cout << "Player 2, please enter your name: ";
            name = getStringInput();
            boards[0] -> setName(name);
        }
        
        // Now that the game is set up, we may run it.
        run();
        
        // Delete all board pointer in boards array
        for (auto boardPointer : boards)
        {
            delete boardPointer;
        }
        
        // After someone wins, we ask if they want to play again
        clearScreen();
    } while (getMenuChoice(2, "Would you like to play again?\n1) Yes\n2) No") == 1);
}

void Game::run()
{
    bool gameOver = false;
    
    
    
    while (!gameOver)
    {
        gameOver = true;
    }
}
