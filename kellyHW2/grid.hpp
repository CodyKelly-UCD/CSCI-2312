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
    Grid() : width(0), height(0) { }
    Grid(int w, int h) : width(w), height(h), grid(vector< vector<int > >(w, vector<int>(h))) { }
    void fill();
    void resize(int, int);
    inline int size() { return width * height; };
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    friend ostream& operator<< (ostream&, const Grid&);
    friend Grid getComparisonGrid(Grid, Grid);
};

#endif
