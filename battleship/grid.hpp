// grid class
#ifndef grid_hpp
#define grid_hpp

#include <vector>
#include <iomanip>

using namespace std;
template <class T> class Grid;
template<class T> ostream& operator<<(ostream&, const Grid<T>&);
Grid<int> getComparisonGrid(const Grid<int>&, const Grid<int>&);

template <class T>
class Grid
{
private:
    vector< vector<T> > grid;
    int width = 0, height = 0, tablePadding = 3;
    
public:
    inline Grid<T>() : width(0), height(0), grid(vector< vector<T> >(0, vector<T>(0))){ };
    inline Grid<T>(int w, int h) : width(w), height(h), grid(vector< vector<T> >(w, vector<T>(h))) { };
    void resize(int, int);
    inline vector< vector<T> > getGrid() { return grid; }
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline T getValue(int x, int y) { return grid[x][y]; }
    inline void setValue(int x, int y, T value) { grid[x][y] = value; }
    inline void setOutputPadding(int p) { tablePadding = p; }
    void setGrid(vector< vector<T> >);
    friend ostream& operator<< <T>(ostream&, const Grid&);
};

template <class T>
void Grid<T>::resize(int w, int h)
{
    // Creates a new grid with the specified dimensions
    width = w;
    height = h;
    
    grid = vector< vector<T> >(w, vector<T>(h));
}

template <class T>
void Grid<T>::setGrid(vector< vector<T> > newGrid)
{
    // Sets the grid, granted the new grid contains vectors of equal size.
    auto length = newGrid[0].size();
    bool uniform = true;
    
    for (vector<T> vec : newGrid)
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

template<class T>
ostream& operator<< (ostream &os, const Grid<T> &grid)
{
    // First output the x-axis labels
    os << ' ';
    
    for (int x = 0; x < grid.width; x++)
    {
        os << setw(grid.tablePadding) << x;
    }
    
    os << endl;
    
    // Then output y-axis labels and grid contents
    for (int y = 0; y < grid.height; y++)
    {
        // Y-axis labels
        os << y;
        
        // Row of grid contents
        for (int x = 0; x < grid.width; x++)
        {
            os << setw(grid.tablePadding) << grid.grid[x][y];
        }
        
        os << endl;
    }
    
    os << endl;
    
    return os;
}

#endif
