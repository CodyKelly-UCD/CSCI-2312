#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "battleship.hpp"

using namespace std;
using namespace Battleship;

const string title = "  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗ \n  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗\n  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝\n  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝ \n  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║     \n  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝     \n                                                                               \n";

int getMenuChoice(int numChoices)
{
    int choice; // Holds user's choice
    bool valid = false;
    
    // Keep asking for choice until a valid choice is made
    cout << "\n>";
    
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
        choice = getMenuChoice(numChoices);
    }
    
    return choice;
}

void makeLowercase(string &s)
{
    for (auto c : s)
    {
        c = tolower(c);
    }
}

void clearScreen()
{
    int count = 300;
    
    while (count > 0)
    {
        cout << endl;
        count--;
    }
}

/*
 Ship Implementation
 */

Ship::Ship(string name, int len, int x, int y, bool horiz) : length(len), posX(x), posY(y), horizontal(horiz), hits(len) {}

Ship::Ship(string n, int len) : length(len), posX(0), posY(0), horizontal(true), hits(len), name(n) {}

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

bool Ship::attack(Coordinates c)
{
    bool hit = false;
    
    // Check if shot is a hit
    if (horizontal && c.y == posY && c.x >= posX && c.x < posX + length)
    {
        hits[c.x - posX] = true;
        hit = true;
    }
    else if (!horizontal && c.x == posX && c.y >= posY && c.y < posY + length)
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

void Ship::setLength(int len)
{
    length = len;
    hits.resize(len);
};

Board::Board() : Grid(10, 10) {}

bool Board::attack(Coordinates c)
{
    bool hit = false;
    try
    {
        if (getValue(c.x, c.y) == ' ')
        {
            // If any of the ships report a hit, change the board value
            // and return true
            for (auto ship : ships)
            {
                if (ship.attack(c))
                {
                    setValue(c.x, c.y, HITCHAR);
                    hit = true;
                    break;
                }
            }
            
            // If no ships report a hit, mark it as misss
            if (!hit)
            {
                setValue(c.x, c.y, MISSCHAR);
            }
        }
        else
        {
            throw ShotAlreadyFired(c);
        }
    }
    catch (ShotAlreadyFired shot)
    {
        // If the coordinates given have already been tried, tell the user and return
        // the value already on the board.
        
        Coordinates c = shot.getCoordinates();
        cout << "These coordinates have already been tried. Enter another.\n";
        hit = getValue(c.x, c.y) == 'h';
    }
    
    return hit;
}

Game::Game() { }

void Game::start()
{
    int choice;
    
    clearScreen();
    cout << title;
    cout << setw(44) << "Cody Kelly" << endl;
    cout << setw(43) << "© 2017" << endl << endl;
    cout << "Press enter to continue.\n\n";
    cin.get();
    clearScreen();
    
    cout << "\n\nWelcome to Battleship!\n\n";
    cout << "Main Menu\n1) Single player game\n2) Two player game";
    choice = getMenuChoice(2);
    clearScreen();
    
    switch (choice)
    {
        case 1:
            //singlePlayerGame();
            break;
            
        case 2:
            //twoPlayerGame();
            break;
            
        default:
            break;
    }
    
    clearScreen();
    cout << "Would you like to play again?\n1) Yes\n2) No";
    choice = getMenuChoice(2);
    
    if (choice == 1)
    {
        start();
    }
}
