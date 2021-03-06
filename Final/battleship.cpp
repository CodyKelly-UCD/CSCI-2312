#include <iomanip>
#include <limits>

#include "battleship.hpp"


const char  HIT = 'O',
            MISS = 'X',
            EMPTY = ' ',
            HORIZONTAL = 'H',
            VERTICAL = 'V';

const int HITCHANCENORMAL = 20;
const int HITCHANCEHARD = 30;
const int HITCHANCEEXTREME = 40;

bool debug = false;

const pair<string, int> SHIPTYPES[] =
{
    // Pairing ship names with lengths
    pair<string, int>("carrier", 5),
    pair<string, int>("battleship", 4),
    pair<string, int>("cruiser", 3),
    pair<string, int>("submarine", 3),
    pair<string, int>("destroyer", 2)
};

const string title = "  ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗ \n  ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗\n  ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝\n  ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝ \n  ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║     \n  ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝     \n                                                                               \n";

int getMenuChoice(int numChoices, string message)
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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
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

string toLowercase(string s)
{
    // Converts all uppercase letters in a string to lowercase letters
    for (auto it = s.begin(); it != s.end(); it++)
    {
        *it = tolower(*it);
    }
    
    return s;
}

void clearScreen()
{
    // Outputs a bunch of newlines, effectively "clearing" the screen
    int count = 500;
    
    if (debug)
    {
        count = 5;
    }
    
    while (count > 0)
    {
        cout << endl;
        count--;
    }
}

int getShipLengthFromName(string name)
{
    // We try to match the name given to our ship to a ship in our SHIPTYPES
    // array so we can set our ship to the desired length.
    bool validName = false;
    int length = 0;
    
    for (auto ship : SHIPTYPES)
    {
        if (ship.first == name)
        {
            length = ship.second;
            validName = true;
        }
    }
    
    // If the name given doesn't match up to anything, that's bad, m'kay.
    if (!validName)
    {
        throw ExceptionInvalidShipName();
    }
    
    return length;
}

void displayTitle()
{
    // Prints the title and other stuff and things.
    
    if (!debug)
    {
        clearScreen();
        cout << title;
        cout << std::setw(44) << "Cody Kelly" << endl;
        cout << std::setw(43) << "© 2017" << endl << endl;
        cout << "Press enter to continue.\n\n";
        cin.get();
    }
}

std::ostream& operator<< (std::ostream& os, const Coordinate c)
{
    // Formats a coordinate for easy printing.
    
    os << char(c.x + 'A') << c.y + 1;
    
    return os;
}
