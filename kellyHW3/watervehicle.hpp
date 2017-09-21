#ifndef watervehicle_hpp
#define watervehicle_hpp

#include <cstdlib>
#include <utility>
#include <vector>

using namespace std;

class WaterVehicle
{
public:
    enum Orientation { horizontal, vertical };
    void setLength(int);
    int getLength();
    void setPosition(pair<int, int>);
    pair<int, int> getPosition();
    void setOrientation(Orientation);
    Orientation getOrientation();
    bool getSunk();
    bool attack(pair<int, int>);
    
private:
    int length = 0;
    pair<int, int> position = pair<int, int>(0, 0);
    Orientation _orientation = horizontal;
    bool sunk = false;
    vector< pair<int, int> > hits;
};

#endif /* watervehicle_hpp */
