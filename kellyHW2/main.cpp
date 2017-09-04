/*
 Grid Comparison Program
 By Cody Kelly
 */

#include <iostream>
#include <vector>

#include "grid.hpp"

using namespace std;

void getInput(int &width, int &height)
{
    cout << "Please input an integer width (-1 to quit): ";
    cin >> width;
    
    if (width == -1)
    {
        return;
    }
    
    cout << "Please input an integer height (-1 to quit): ";
    cin >> height;
    
    if (height == -1)
    {
        return;
    }
}

int main()
{
    vector<Grid> grids(3);
    int width = 0, height = 0;
    
    cout << "\nWelcome to the Grid Comparison Program!\n";
    getInput(width, height);
    
    while (width != -1 && height != -1)
    {
        for (vector<Grid>::iterator it = grids.begin(); it != grids.end(); it++)
        {
            it->resize(width, height);
        }
        
        grids[0].fill();
        grids[1].fill();
        grids[2] = getComparisonGrid(grids[0], grids[1]);
        
        cout << "Grid 1:\n" << grids[0] << "\nGrid 2:\n" << grids[1]
        << "\nComparison grid:\n" << grids[2] << endl;
        
        getInput(width, height);
    }
    
    return 0;
}
