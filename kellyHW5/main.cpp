/*
 Homework #5
 Cody Kelly
 October 24th, 2017
 2312
*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

char getInput(vector<char> validOptions)
{
    // This function receives input from the user, checks the input for validity
    // and returns the result
    
    string input;
    char option;
    
    cout << "Please choose a direction (or -1 to quit): ";
    
    getline(cin, input); // get full input
    
    if (input == "-1")
    {
        exit(0);
    }
    
    option = tolower(input[0]); // extract choice from first character of string
    
    // If the first letter of the input isn't one of the valid options,
    // try again
    if (find(validOptions.begin(), validOptions.end(), option) == validOptions.end())
    {
        cout << "\nInvalid option. Please type one of the following and hit enter to confirm: ";
        for (auto option : validOptions)
        {
            cout << option << " ";
        }
        cout << endl;
        option = getInput(validOptions);
    }
    
    return option;
}

struct Node
{
    Node(char c) : name(c) {}
    char name;
    Node *north = nullptr, *east = nullptr, *south = nullptr, *west = nullptr;
};

void printMap(Node* currentRoom)
{
    // This function goes through each of the four direction pointers of a node
    // If the direction is NOT a nullpointer, then the function draws a connection
    // pointing in that direction. Otherwise, it prints whitespace
    if (currentRoom->north != nullptr)
    {
        cout << endl << setw(4) << '|' << endl;
    }
    else
    {
        cout << "\n\n";
    }
    
    if (currentRoom->west != nullptr)
    {
        cout << " --";
    }
    else
    {
        cout << "   ";
    }
    
    // Display current room name in the center
    cout << currentRoom->name;
    
    if (currentRoom->east != nullptr)
    {
        cout << "--\n";
    }
    else
    {
        cout << endl;
    }
    
    if (currentRoom->south != nullptr)
    {
        cout << setw(4) << '|' << endl << endl;
    }
    else
    {
        cout << "\n\n\n";
    }
}

int main()
{
    Node a = {'A'}, b = {'B'}, c = {'C'}, d = {'D'}, e = {'E'}, f = {'F'}, g = {'G'}, h = {'H'}, i = {'I'}, j = {'J'}, k = {'K'}, l = {'L'};
    Node* currentRoom = &a;
    
    // Create room connections
    a.east = &b;
    a.south = &e;
    
    b.south = &f;
    b.west = &a;
    
    c.south = &g;
    
    d.south = &h;
    
    e.north = &a;
    e.south = &i;
    
    f.north = &b;
    f.east = &g;
    
    g.north = &c;
    g.west = &f;
    g.east = &h;
    
    h.north = &d;
    h.west = &g;
    h.south = &l;
    
    i.north = &e;
    i.east = &j;
    
    j.west = &i;
    j.east = &k;
    
    k.west = &j;
    
    l.north = &h;
    
    // Main game loop
    while (currentRoom != &l)
    {
        vector<char> validOptions;
        
        printMap(currentRoom);
        
        // Display movement options
        cout << "You are in room " << currentRoom->name << " of a maze of twisty little passages, you may go in these directions: ";
        
        if(currentRoom->north != nullptr)
        {
            cout << "north ";
            validOptions.push_back('n');
        }
        if(currentRoom->east != nullptr)
        {
            cout << "east ";
            validOptions.push_back('e');
        }
        if(currentRoom->south != nullptr)
        {
            cout << "south ";
            validOptions.push_back('s');
        }
        if(currentRoom->west != nullptr)
        {
            cout << "west ";
            validOptions.push_back('w');
        }
        cout << endl;
        
        // Move player
        switch (getInput(validOptions))
        {
            case 'n':
                currentRoom = currentRoom->north;
                break;
            
            case 'e':
                currentRoom = currentRoom->east;
                break;
                
            case 's':
                currentRoom = currentRoom->south;
                break;
                
            case 'w':
                currentRoom = currentRoom->west;
                break;
                
            default:
                cout << "INVALID OPTION!\n";
                exit(1);
                break;
        }
    }
    
    cout << "\n\nYou made it out! Congrats!\n\n";
    
    return 0;
}
