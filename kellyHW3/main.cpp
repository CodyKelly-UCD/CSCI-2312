#include <iostream>
#include <utility>

#include "functions.hpp"
#include "grid.hpp"

using namespace std;

int main()
{
    Grid<char> grid;
    
    grid.resize(10, 10);
    
    while (true)
    {
        int length = 0;
        pair<int, int> position = pair<int, int>(0, 0);
        int orientation;
        int depth = 0;
        auto newGrid = grid.getGrid();
        int count = 0;
        
        for (int x = 0; x < newGrid.size(); x++)
        {
            for (int y = 0; y < newGrid[x].size(); y++, count++)
            {
                newGrid[x][y] = ' ';
            }
        }
        
        grid.setGrid(newGrid);
        
        cout << "Ship length: " << endl;
        length = getInput(10);
        
        cout << "X Position:" << endl;
        position.first = getInput(10);
        
        cout << "Y Position:" << endl;
        position.second = getInput(10);
        
        cout << "Dive depth:" << endl;
        depth = getInput();
        
        cout << "Orientation (1 for horizonal, 2 for vertical):" << endl;
        orientation = getInput(2);
        
        cout << grid << std::endl;
    }
    
    return 0;
}
