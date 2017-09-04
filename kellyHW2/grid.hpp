#ifndef grid_h
#define grid_h

#include <vector>

using namespace std;

class Grid
{
private:
    vector< vector<int> > grid;
    int width;
    int height;
    
public:
    Grid();
    Grid(int, int);
    void fill();
    void resize(int, int);
    inline int size() { return width * height; };
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    friend ostream& operator<< (ostream&, const Grid&);
    friend Grid getComparisonGrid(Grid, Grid);
};

#endif
