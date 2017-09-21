#include <iostream>
#include <vector>

#include "grid.hpp"
#include "submarine.hpp"

using namespace std;

int getInput(int limit)
{
    int input;

    cout << "Enter integer from 1 to " << limit << " or enter -1 to quit: ";
    
    while (!(cin >> input) || input < -1 || input == 0 || input > limit)
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        input = getInput(limit);
    }
    
    if (input == -1)
    {
        exit(0);
    }
    
    return input;
}

int getInput()
{
    int input;
    
    cout << "Enter integer 0 or more or enter -1 to quit: ";

    while (!(cin >> input) || input < -1)
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        input = getInput();
    }
    
    if (input == -1)
    {
        exit(0);
    }
    
    return input;
}

void attackRandomly(Grid<char> grid, vector<Submarine> subs, int shots)
{
    vector<pair<int, int>()>
    for (int count = 0; count < shots; count++)
    {
        <#statements#>
    }
    for (auto sub : subs)
    {
        
    }
}
