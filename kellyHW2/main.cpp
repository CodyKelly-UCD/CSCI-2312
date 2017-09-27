/*
 HW2
 Cody Kelly
 */

#include <iostream>
#include <vector>

#include "grid.hpp"

using namespace std;

void getInput(int &width, int &height)
{
    // Reads in user input and checks if input is valid
    
    cout << "Please input an integer width (-1 to quit): ";
    
    while (!(cin >> width) || width < -1)
    {
        cout << "Invalid input, try again.\n";
        cin.clear();
        cin.ignore();
    }
    
    if (width == -1)
    {
        return;
    }
    
    cout << "\nPlease input an integer height (-1 to quit): ";
    
    while (!(cin >> height) || height < -1)
    {
        cout << "Invalid input, try again.\n";
        cin.clear();
        cin.ignore();
    }
    
    if (height == -1)
    {
        return;
    }
}

int main()
{
    vector<Grid> grids(3);
    int width = 0, height = 0;
    
    cout << "\nWelcome to the Grid Comparison Program!\n\n";
    getInput(width, height);
    
    // If the user hasn't quit the program
    while (width != -1 && height != -1)
    {
        // Resize the grids
        for (vector<Grid>::iterator it = grids.begin(); it != grids.end(); it++)
        {
            it->resize(width, height);
        }
        
        // Fill them with ones
        grids[0].fill();
        grids[1].fill();
        grids[2] = getComparisonGrid(grids[0], grids[1]); // Get comparison
        
        // Output results
        cout << "\nGrid 1:\n" << grids[0] << "\nGrid 2:\n" << grids[1]
        << "\nComparison grid:\n" << grids[2] << endl;
        
        // And repeat
        getInput(width, height);
    }
    
    return 0;
}
