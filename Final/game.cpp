#include <fstream>
#include <iostream>
#include <cstdlib>

#include "game.hpp"

using std::cout;
using std::cin;
using std::rand;

void Game::addShipFromPlayer(string, Board*)
{
    
}

void Game::addShipRandomly(string name, Board* board)
{
    bool valid = true;
    Ship ship;
    int length = getShipLengthFromName(name);
    
    ship.setLength(length);
    ship.setName(name);
    
    do
    {
        valid = true;
        
        int orientation = rand() % 2;
        int x = 0, y = 0;
        
        if (orientation == 1) // horizontal
        {
            x = rand() % (10 - length);
            y = rand() % 10;
            ship.setOrientation(HORIZONTAL);
        }
        else // vertical
        {
            x = rand() % 10;
            y = rand() % (10 - length);
            ship.setOrientation(VERTICAL);
        }
        
        ship.setPosX(x);
        ship.setPosY(y);
        
        try
        {
            board->addShip(ship);
        }
        catch (ExceptionShipPlacementOccupied)
        {
            valid = false;
        }
    } while (!valid);
}

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
        name = toLowercase(name);
        
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
                addShipFromPlayer(name, board);
            }
            else
            {
                addShipRandomly(name, board);
            }
        }
        catch (ExceptionShipPlacementOccupied)
        {
            clearScreen();
            cout << "The position for the " << name << " read in from the file was occupied by another ship.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                addShipFromPlayer(name, board);
            }
            else
            {
                addShipRandomly(name, board);
            }
        }
    }
    
    file.close();
}

void Game::randomizeShips(Board *board)
{
    // Adds one ship of each kind to a random location
    // on the given board.
    
    for (auto ship : SHIPTYPES)
    {
        addShipRandomly(ship.first, board);
    }
}

void Game::start()
{
    // This function sets up a game.
    // It prints the title, creates boards of specific types
    // (human or computer), gets the names of the players, and when the game
    // is over it asks if the players would like to play again.
    
    srand(int(time(NULL)));
    
    if (!debug)
    {
        // Display title
        clearScreen();
        cout << title;
        cout << setw(44) << "Cody Kelly" << endl;
        cout << setw(43) << "© 2017" << endl << endl;
        cout << "Press enter to continue.\n\n";
        cin.get();
    }
    
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
            
            if (!debug)
            {
                cout << "Please enter your name: ";
                name = getStringInput();
                boards[0]->setName(name);
            }
            
            boards[1]->setName("Computer");
                
            readShips(boards[0]); // Read ships from file for player
            randomizeShips(boards[1]); // Get a random ship layout for AI
        }
        else
        {
            // Setup multiplayer game
            string name;
            
            boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Human);
            
            cout << "Player 1, please enter your name: ";
            name = getStringInput();
            boards[0]->setName(name);
            
            clearScreen();
            cout << "Would you like to: \n";
            cout << "1) Choose ship locations manually or\n";
            cout << "2) Randomize ship locations";
            
            if (getMenuChoice(2) == 1)
            {
                for (auto ship : SHIPTYPES)
                {
                    addShipFromPlayer(ship.first, boards[0]);
                }
            }
            else
            {
                randomizeShips(boards[0]);
            }
            
            clearScreen();
            cout << "Player 2, please enter your name: ";
            name = getStringInput();
            boards[1]->setName(name);
            
            clearScreen();
            cout << "Would you like to: \n";
            cout << "1) Choose ship locations manually or\n";
            cout << "2) Randomize ship locations";
            
            if (getMenuChoice(2) == 1)
            {
                for (auto ship : SHIPTYPES)
                {
                    addShipFromPlayer(ship.first, boards[1]);
                }
            }
            else
            {
                randomizeShips(boards[1]);
            }
        }
        
        // Now that the game is set up, we may run it.
        run();
        
        // Delete all board pointers in boards array
        for (auto boardPointer : boards)
        {
            delete boardPointer;
        }
        
        clearScreen();
        
    } while (getMenuChoice(2, "Would you like to play again?\n1) Yes\n2) No") == 1);
}

ShotResult Game::playerAttack(int attackerIndex)
{
    Coordinate coord;
    bool validCoordinate = true;
    int otherPlayerIndex;
    ShotResult result;
    
    if (attackerIndex == 0)
    {
        otherPlayerIndex = 1;
    }
    else
    {
        otherPlayerIndex = 0;
    }
    
    cout << "Enter attack coordinate information:\n";
    
    do
    {
        try
        {
            bool validColumn = true;
            bool validRow = true;
            validCoordinate = true;
            
            // Get x coordinate
            do
            {
                char column;
                
                validColumn = true;
                
                cout << "Please enter a column letter (from A to J): ";
                cin >> column;
                column = toupper(column);
                
                if (!(column >= 'A' && column <= 'J'))
                {
                    validColumn = false;
                    cout << "\nInvalid column. Please enter a letter from A to J.\n";
                }
                else
                {
                    coord.x = int(column - 'A');
                }
            } while (!validColumn);
            
            // Get y coordinate
            do
            {
                int row;
                
                validRow = true;
                
                cout << "Please enter a row number (from 1 to 10): ";
                cin >> row;
                
                if (!(row >= 1 && row <= 10))
                {
                    validRow = false;
                    cout << "\nInvalid row. Please enter a number from 1 to 10.\n";
                }
                else
                {
                    coord.y = row - 1;
                }
            } while (!validRow);
            
            // Try attack
            result = boards[otherPlayerIndex]->attack(coord);
        }
        catch (ExceptionShotCoordinateOccupied)
        {
            cout << "\nThat position has been fired at already. Please choose another.\n";
            validCoordinate = false;
        }
    }
    while (!validCoordinate);
    
    return result;
}

void Game::run()
{
    string winner = "";
    ShotResult lastShot;
    int turnNumber = 1;
    
    while (true)
    {
        if (singlePlayer)
        {
            
        }
        else
        {
            for (int count = 0; count < 2; count++)
            {
                int otherPlayerIndex = 0;
                
                if (count == 0)
                {
                    otherPlayerIndex = 1;
                }
                else
                {
                    otherPlayerIndex = 0;
                }
                
                clearScreen();
                cout << "Your turn, " << boards[count]->getName() << ".\n";
                cout << "Press enter when ready.";
                cin.get();
                
                clearScreen();
                
                // First tell the player where the other player shot last.
                if (turnNumber != 1)
                {
                    cout << "Last enemy shot: " << char('A' + lastShot.shotPosition.x) << lastShot.shotPosition.y + 1;
                    
                    if (lastShot.sunk)
                    {
                        cout << "\nThey sank your " << lastShot.shipName << "!";
                    }
                    else if(lastShot.hit)
                    {
                        cout << "\nThey hit your " << lastShot.shipName << "!";
                    }
                    
                    cout << endl << endl;
                }
                
                // Display grids for player
                cout << *boards[count] << endl;
                
                // Get the player's choice for a shot and process it
                ShotResult shotResult = playerAttack(count);
                boards[count]->markShot(shotResult.shotPosition, shotResult.hit);
                
                // Give the player shot results..
                clearScreen();
                if (shotResult.hit)
                {
                    cout << "Hit!";
                    
                    if (shotResult.sunk)
                    {
                        cout << "\nYou sank their " << shotResult.shipName << "!";
                    }
                }
                else
                {
                    cout << "Miss.";
                }
                
                cout << "\n\nPress enter to continue.";
                cin.ignore();
                cin.get();
                
                // If the other player lost, then the current one won!
                if (boards[otherPlayerIndex]->getLost())
                {
                    clearScreen();
                    cout << "Congratulations, " << boards[count]->getName()
                    << "! You've sunk the enemy's entire fleet.\n\nYou win!!";
                    cout << "\n\nPress enter to continue.";
                    cin.get();
                    return;
                }
                
                lastShot = shotResult;
                turnNumber++;
            }
        }
    }
}
