/*
 
*/

#include <iostream>
#include <string>

#include "grid.hpp"

using namespace std;

int main()
{
    Grid<int> grid(5, 6);
    auto newGrid = grid.getGrid();
    int count = 0;
    
    grid.setOutputPadding(3);
    
    for (int x = 0; x < newGrid.size(); x++)
    {
        for (int y = 0; y < newGrid[x].size(); y++, count++)
        {
            newGrid[x][y] = count;
        }
    }
    
    grid.setGrid(newGrid);
    
    cout << grid << endl;
    
    return 0;
}
