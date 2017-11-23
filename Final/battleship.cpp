#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "battleship.hpp"

const string title = "  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗ \n  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗\n  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝\n  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝ \n  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║     \n  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝     \n                                                                               \n";

int getMenuChoice(int numChoices, string message = "")
{
    int choice; // Holds user's choice
    bool valid = false;
    
    cout << message;
    
    do
    {
        // Keep asking for choice until a valid choice is made
        cout << "\n> ";
        
        if (cin >> choice)
        {
            if (choice >= 1 && choice <= numChoices)
            {
                valid = true; // If the input is an int and within the limit, it's
                // valid
            }
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (!valid)
        {
            cout << "\nPlease select a choice from the menu.";
        }
        
    } while (!valid);
    
    return choice;
}

string getStringInput()
{
    // Returns a string given by user
    string input;
    getline(cin, input);
    return input;
}

string to_lowercase(string s)
{
    // Converts all uppercase letters in a string to lowercase letters
    for (auto c : s)
    {
        c = tolower(c);
    }
    
    return s;
}

void clearScreen()
{
    // Outputs a bunch of newlines, effectively "clearing" the screen
    int count = 500;
    
    while (count > 0)
    {
        cout << endl;
        count--;
    }
}

/*
 Ship Implementation
 */

Ship::Ship(string name, int x, int y, char o) : posX(x), posY(y), orientation(o)
{
    // We try to match the name given to our ship to a ship in our SHIPS array
    // so we can set our ship to the desired length.
    bool lengthSet = false;
    
    for (auto ship : SHIPS)
    {
        if (ship.first == name)
        {
            length = ship.second;
            hits.resize(ship.second);
            lengthSet = true;
        }
    }
    
    // If the name given doesn't match up to anything, that's bad, m'kay.
    if (!lengthSet)
    {
        throw ExceptionInvalidShipName();
    }
}

int Ship::getNumberOfHits() const
{
    int count = 0;
    
    for (bool hit : hits)
    {
        if (hit)
        {
            count++;
        }
    }
    
    return count;
}

bool Ship::attack(Coordinate c)
{
    bool hit = false;
    
    // Check if shot is a hit
    if (orientation == HORIZONTAL && c.y == posY && c.x >= posX && c.x < posX + length)
    {
        hits[c.x - posX] = true;
        hit = true;
    }
    else if (orientation == VERTICAL && c.x == posX && c.y >= posY && c.y < posY + length)
    {
        hits[c.y - posY] = true;
        hit = true;
    }
    
    // Check if the boat's been sunk
    if (getNumberOfHits() == length)
    {
        sunk = true;
    }
    
    return hit;
}

vector<Coordinate> Ship::getCoordinatesContained()
{
    vector<Coordinate> coordinates;
    
    for (int count = 0; count < length; count++)
    {
        if (orientation == HORIZONTAL)
        {
            coordinates.push_back(Coordinate(posX + count, posY));
        }
        else
        {
            coordinates.push_back(Coordinate(posX, posY + count));
        }
    }
    
    return coordinates;
}

Board::Board(PlayerType p) : playerType(p) { }

void Board::setName(string n) { playerName = n; }

void Board::setPlayerType(PlayerType p) { playerType = p; }

bool Board::attack(Coordinate c)
{
    bool hit = false;
    
    if (shotGrid.getValue(c.x, c.y) == EMPTY)
    {
        // If any of the ships report a hit, change the board value
        // and return true
        for (auto ship : ships)
        {
            if (ship.attack(c))
            {
                shotGrid.setValue(c.x, c.y, HIT);
                hit = true;
                break;
            }
        }
        
        // If no ships report a hit, mark it as miss
        if (!hit)
        {
            shotGrid.setValue(c.x, c.y, MISS);
        }
        
        return true; // attack was completed
    }
    
    return false; // attack failed, player needs to try again
}

void Board::addShip(Ship newShip)
{
    // First we'll check to see if the ship extends off the board
    for (auto coord : newShip.getCoordinatesContained())
    {
        if (coord.x < 0 || coord.x >= 10 || coord.y < 0 || coord.y >= 10)
        {
            throw ExceptionShipOutOfBounds();
        }
    }
    
    // Now we'll check to see if this new ship overlaps with any other.
    // Loop through each existing ship:
    for (auto ship : ships)
    {
        // And each coordinate of the new ship:
        for (auto coord : newShip.getCoordinatesContained())
        {
            // And see if any overlap:
            if (ship.containsCoordinate(coord))
            {
                // If they do then the space
                // is already occupied.
                throw ExceptionShipPlacementOccupied();
            }
        }
    }
    
    ships.push_back(newShip);
}

void Game::readShips(Board &board)
{
    ifstream file("./ship_placement.csv");
    file.ignore(1, '\n'); // ignore first line
    
    for (int shipCount = 5; shipCount > 0; shipCount++)
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
        file.ignore(); // go to next line
        
        Ship newShip = Ship(name, int(x - 'A'), int(y - '1'), orientation);
        
        try
        {
            board.addShip(newShip);
        }
        catch (ExceptionShipOutOfBounds)
        {
            clearScreen();
            std::cout << "The " << name << " from the file was out of bounds.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                board.addShip(getShipFromPlayer(name, board));
            }
            else
            {
                board.addShip(getShipRandomly(name, board));
            }
        }
        catch (ExceptionShipPlacementOccupied)
        {
            clearScreen();
            std::cout << "The position for the " << name << " read in from the file was occupied by another ship.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                board.addShip(getShipFromPlayer(name, board));
            }
            else
            {
                board.addShip(getShipRandomly(name, board));
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
        
    }
}
