#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "grid.hpp"

using namespace std;

char Grid::getValue(int x, int y)
{
    char value;
    
    try
    {
        value = grid[x][y];
    }
    catch (out_of_range)
    {
        value = ' ';
    }
    
    return value;
}

void Grid::resize(int w, int h)
{
    // Creates a new grid with the specified dimensions
    width = w;
    height = h;
    
    grid.resize(w);
    for (int count = 0; count < w; count++)
    {
        grid[count].resize(h);
    }
}

void Grid::setGrid(vector< vector<char> > newGrid)
{
    // Sets the grid, granted the new grid contains vectors of equal size.
    auto length = newGrid[0].size();
    bool uniform = true;
    
    for (vector<char> vec : newGrid)
    {
        if (vec.size() != length)
        {
            uniform = false;
            break;
        }
    }
    
    if (uniform)
    {
        grid = newGrid;
    }
}

ostream& operator<< (ostream &os, const Grid &grid)
{
    // First output the x-axis labels
    for (int count = 0; count < grid.tablePadding; count++)
    {
        os << ' ';
    }
    
    for (int x = 0; x < grid.width; x++)
    {
        os << setw(grid.tablePadding) << char('A' + x);
    }
    
    os << endl;
    
    // Then output y-axis labels and grid contents
    for (int y = 0; y < grid.height; y++)
    {
        // Y-axis labels
        os << setw(grid.tablePadding) << y + 1;
        
        // Row of grid contents
        for (int x = 0; x < grid.width; x++)
        {
            os << setw(grid.tablePadding) << grid.grid[x][y];
        }
        
        // Output y-axis labels again
        os << setw(grid.tablePadding) << y + 1 << endl;
    }
    
    // Output the x-axis labels again
    for (int count = 0; count < grid.tablePadding; count++)
    {
        os << ' ';
    }
    
    for (int x = 0; x < grid.width; x++)
    {
        os << setw(grid.tablePadding) << char('A' + x);
    }
    
    os << endl;
    
    return os;
}
