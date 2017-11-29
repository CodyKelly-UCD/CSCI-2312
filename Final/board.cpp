#include "board.hpp"

Board::Board()
{
    shotGrid = Grid(10, 10);
    shipGrid = Grid(10, 10);
}

Board::Board(PlayerType p) : playerType(p)
{
    shotGrid = Grid(10, 10);
    shipGrid = Grid(10, 10);
}

ShotResult Board::attack(Coordinate c)
{
    // This function takes a coordinate and checks every ship in its ship vector
    // for a hit. It returns the results of the attack.
    
    ShotResult result;
    result.shotPosition = c;
    
    if (shipGrid.getValue(c.x, c.y) != HIT && shipGrid.getValue(c.x, c.y) != MISS)
    {
        // If any of the ships report a hit, change the board value
        // and record info on the hit
        for (auto ship : ships)
        {
            if (ship->attack(c))
            {
                shipGrid.setValue(c.x, c.y, HIT);
                result.hit = true;
                result.shipName = ship->getName();
                
                // If the ship is sunk, return its name as well.
                if (ship->getSunk())
                {
                    result.sunk = true;
                }
                
                break;
            }
        }
        
        // If no ships report a hit, mark it as miss
        if (!result.hit)
        {
            shipGrid.setValue(c.x, c.y, MISS);
        }
    }
    else
    {
        throw ExceptionShotCoordinateOccupied();
    }
    
    return result;
}

void Board::addShip(Ship newShip)
{
    // Adds a ship to the board if the ship doesn't overlap any others and
    // is fully contained within the board.
    
    // First we'll check to see if the ship extends off the board
    for (auto coord : newShip.getCoordinatesContained())
    {
        if (coord.x < 0 || coord.x >= 10 || coord.y < 0 || coord.y >= 10)
        {
            throw ExceptionShipOutOfBounds();
        }
    }
    
    // Now we'll check to see if this new ship overlaps with any other.
    // Loop through each existing ship:
    for (auto ship : ships)
    {
        // And each coordinate of the new ship:
        for (auto coord : newShip.getCoordinatesContained())
        {
            // And see if any overlap:
            if (ship->containsCoordinate(coord))
            {
                // If they do then the space
                // is already occupied.
                throw ExceptionShipPlacementOccupied();
            }
        }
    }
    
    for (auto coord : newShip.getCoordinatesContained())
    {
        shipGrid.setValue(coord.x, coord.y, newShip.getName()[0]);
    }
    
    ships.push_back(new Ship(newShip));
}

bool Board::getLost() const
{
    // seriously, get lost.
    // Whoops, I mean, this function returns true if
    // all ships on this board are sunk.
    
    for (auto ship : ships)
    {
        if (!ship->getSunk())
        {
            return false;
        }
    }
    
    return true;
}


void Board::markShot(Coordinate coord, bool hit)
{
    // Marks the result of a shot on this board's shotGrid
    
    char value = EMPTY;
    
    if (hit)
    {
        value = HIT;
    }
    else
    {
        value = MISS;
    }
    
    shotGrid.setValue(coord.x, coord.y, value);
}

void Board::printShipGrid() const
{
    cout << "Your ships:\n" << shipGrid;
}

void Board::removeShips()
{
    for (auto shipPtr : ships)
    {
        delete shipPtr;
    }
    
    shipGrid = Grid(10, 10);
    
    ships.resize(0);
}

int Board::shipsRemaining()
{
    // Returns the number of ships on the board that are NOT sunk.
    
    int shipsRemaining = 0;
    
    for (auto ship : ships)
    {
        if (!ship->getSunk())
        {
            shipsRemaining++;
        }
    }
    
    return shipsRemaining;
}

ostream& operator<< (ostream &os, const Board &board)
{
    os << "Shots you've made:\n" << board.shotGrid << endl
    << "Your ships:\n" << board.shipGrid;
    
    return os;
}

Board::~Board()
{
    for (auto shipPtr : ships)
    {
        delete shipPtr;
    }
}
