#include <string>
#include <iostream>
#include <cstdlib>

#include "grid.hpp"

using namespace std;

const char HITCHAR = 'h', MISSCHAR = 'm';
const int NUMBER_OF_SHOTS = 15;

int getInput(string message, int limit)
{
    int input;
    
    cout << message << endl;
    cout << "Enter integer from 1 to " << limit << " or enter -1 to quit: ";
    
    if (!(cin >> input) || input < -1 || input == 0 || input > limit)
    {
        cout << "\nInvalid input\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        input = getInput(message, limit);
    }
    
    cout << endl;
    
    if (input == -1)
    {
        exit(0);
    }
    
    return input;
}

int getInput(string message)
{
    int input;
    
    cout << message << endl;
    cout << "Enter integer 0 or greater or enter -1 to quit: ";
    
    if (!(cin >> input) || input < -1)
    {
        cout << "\nInvalid input\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        input = getInput(message);
    }
    
    cout << endl;
    
    if (input == -1)
    {
        exit(0);
    }
    
    return input;
}

class WaterVehicle
{
protected:
    int length = 0, posX = 0, posY = 0;
    bool horizontal = false, sunk = false;
    vector<bool> hits;
    
public:
    WaterVehicle(int len, int x, int y, bool horiz) : length(len), posX(x), posY(y), horizontal(horiz), hits(len) {}
    bool getSunk() const { return sunk; }
    int getNumberOfHits() const
    {
        int count = 0;
        
        for (bool hit : hits)
        {
            if (hit)
            {
                count++;
            }
        }
        
        return count;
    }
    bool attack(int x, int y)
    {
        bool hit = false;
        
        // Check if shot is a hit
        if (horizontal && y == posY && x >= posX && x < posX + length)
        {
            hits[x - posX] = true;
            hit = true;
        }
        else if (!horizontal && x == posX && y >= posY && y < posY + length)
        {
            hits[y - posY] = true;
            hit = true;
        }
        
        // Check if the boat's been sunk
        for (int count = 0; count < length; count++)
        {
            if (!hits[count])
            {
                break;
            }
            
            sunk = true;
        }
        
        return hit;
    }
    
    void setLength(int len)
    {
        length = len;
        hits.resize(len);
    };
    
    void setPosX(int x) { posX = x; }
    void setPosY(int y) { posY = y; }
    void setHorizontal(bool h) { horizontal = h; }
};

class Submarine : public WaterVehicle
{
    int diveDepth;
    bool surfaced;
    
public:
    Submarine(int len, int x, int y, bool horiz, int depth) : WaterVehicle(len, x, y, horiz)
    {
        setDiveDepth(depth);
    }
    bool getSurfaced() { return surfaced; }
    int getDiveDepth() { return diveDepth; }
    void setDiveDepth(int depth)
    {
        diveDepth = depth;
        
        surfaced = diveDepth == 0;
    }
    
    void operator= (Submarine sub2)
    {
        length = sub2.length;
        posX = sub2.posX;
        posY = sub2.posY;
        horizontal = sub2.horizontal;
        diveDepth = sub2.diveDepth;
        hits = sub2.hits;
    }
    
    friend ostream& operator<< (ostream&, const Submarine&);
};

ostream& operator<< (ostream& out, const Submarine& sub)
{
    int hitCount = sub.getNumberOfHits();
    
    out << "\nSubmarine details:\n";
    out << "Length: " << sub.length << endl;
    out << "Position: (" << sub.posX + 1 << ", " << char('A' + sub.posY) << ")\n";
    out << "Orientation: ";
    
    if (sub.horizontal)
    {
        out << "Horizontal\n";
    }
    else
    {
        out << "Vertical\n";
    }
    
    out << "Dive depth: " << sub.diveDepth << endl;
    out << "Surfaced: ";
    
    if (sub.surfaced)
    {
        out << "Yes\n";
    }
    else
    {
        out << "No\n";
    }
    
    out << "Hit: ";
    
    if (hitCount == 0)
    {
        out << "No";
    }
    else
    {
        out << "Yes (" << hitCount << " hits)\n";
    }
    
    out << "Sunk: ";
    
    if (sub.sunk)
    {
        out << "Yes\n";
    }
    else
    {
        out << "No\n";
    }
    
    return out;
}

int main()
{
    int length = 0, lengthLimit = 0, posX = 0, posY = 0, orientation = 0, depth = 0;
    Grid grid = Grid(10, 10);
    
    // Get position from user and subtract one (so the input is 0 - 9 instead of 1 - 10)
    posX = getInput("Submarine X position:", 10) - 1;
    posY = getInput("Submarine Y position:", 10) - 1;
    
    orientation = getInput("Submarine orientation (1 for horizontal, 2 for vertical):", 2);
    
    // Make sure the sub doesn't go off-grid
    if (orientation == 1)
    {
        lengthLimit = 10 - posX - length;
    }
    else
    {
        lengthLimit = 10 - posY - length;
    }
    
    length = getInput("Length of submarine:", lengthLimit);
    depth = getInput("Submarine depth:");
    
    Submarine sub = Submarine(length, posX, posY, orientation == 1, depth);
    
    for (int count  = 0; count < NUMBER_OF_SHOTS; count++)
    {
        int randX = rand() % 10;
        int randY = rand() % 10;
        
        if (grid.getValue(randX, randY) == ' ')
        {
            if (sub.attack(randX, randY))
            {
                grid.setValue(randX, randY, HITCHAR);
            }
            else
            {
                grid.setValue(randX, randY, MISSCHAR);
            }
        }
        else
        {
            count--;
        }
    }
    
    Submarine sub2 = sub;
    
    cout << grid << endl << sub2 << endl;
    
    return 0;
}
