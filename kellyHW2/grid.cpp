#include <vector>
#include <iomanip>
#include <cstdlib>

#include "grid.hpp"

using namespace std;

void Grid::fill()
{
    // This function fills 30% of the grid with ones
    vector< pair<int, int> > usedCoordinates(size() / 3); // Holds coordinates of elements
                                                          // already filled
    
    // First we find a set of unique coordinates to fill
    for (int count = 0; count < size() / 3; count++)
    {
        bool coordinateAlreadyUsed = false;
        pair<int, int> newCoordinate(rand() % width, rand() % height);
        
        // See if the new coordinate's being used already
        do
        {
            coordinateAlreadyUsed = false;
            
            for (vector< pair<int, int> >::iterator it = usedCoordinates.begin(); it != usedCoordinates.end(); it++)
            {
                if (newCoordinate == *it)
                {
                    // If the coordinate's being used, make another and repeat
                    coordinateAlreadyUsed = true;
                    newCoordinate = pair<int, int>(rand() % width, rand() % height);
                    break;
                }
            }
        } while(coordinateAlreadyUsed);
        
        // Finally, we put a one at the new coordinates
        usedCoordinates[count] = newCoordinate;
        
        int x = usedCoordinates[count].first, y = usedCoordinates[count].second;
        
        grid[x][y] = 1;
    }
}

void Grid::resize(int w, int h)
{
    width = w;
    height = h;
    
    grid = vector< vector<int> >(width, vector<int>(h));
}

ostream& operator<< (ostream &os, const Grid &grid)
{
    int tableWidth = 3; // Amount of padding between columns
    
    // First output the x-axis labels
    os << setw(tableWidth) << ' ';
    
    for (int x = 0; x < grid.width; x++)
    {
        os << setw(tableWidth) << x;
    }
    
    os << endl;
    
    // Then output y-axis labels and grid contents
    for (int y = 0; y < grid.height; y++)
    {
        // Y-axis labels
        os << setw(tableWidth) << y;
        
        // Row of grid contents
        for (int x = 0; x < grid.width; x++)
        {
            os << setw(tableWidth) << grid.grid[x][y];
        }
        
        os << endl;
    }
    
    os << endl;
    
    return os;
}

Grid getComparisonGrid(Grid g1, Grid g2)
{
    Grid newGrid(g1.width, g1.height);
    
    for (int y = 0; y < g1.height; y++)
    {
        for (int x = 0; x < g1.width; x++)
        {
            if (g1.grid[x][y] == 1 && g2.grid[x][y] == 1)
            {
                newGrid.grid[x][y] = 1;
            }
        }
    }
    
    return newGrid;
}
