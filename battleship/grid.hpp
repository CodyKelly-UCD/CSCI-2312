// grid class
#ifndef grid_hpp
#define grid_hpp

#include <vector>
#include <iomanip>

using namespace std;

class Grid
{
private:
    vector< vector<char> > grid;
    int width = 0, height = 0, tablePadding = 3;
    
public:
    Grid() : width(0), height(0), grid(vector< vector<char> >(0, vector<char>(0, ' '))) { };
    Grid(int w, int h) : width(w), height(h), grid(vector< vector<char> >(w, vector<char>(h, ' '))) { };;
    void resize(int, int);
    vector< vector<char> > getGrid() { return grid; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    char getValue(int, int);
    void setValue(int x, int y, char value) { grid[x][y] = value; }
    void setOutputPadding(int p) { tablePadding = p; }
    void setGrid(vector< vector<char> >);
    friend ostream& operator<< (ostream&, const Grid&);
};

#endif
