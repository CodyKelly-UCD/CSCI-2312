#include "board.hpp"

Board::Board(PlayerType p) : playerType(p) { }

void Board::setName(string n) { playerName = n; }

void Board::setPlayerType(PlayerType p) { playerType = p; }

bool Board::attack(Coordinate c)
{
    bool hit = false;
    
    if (shotGrid.getValue(c.x, c.y) == EMPTY)
    {
        // If any of the ships report a hit, change the board value
        // and return true
        for (auto ship : ships)
        {
            if (ship.attack(c))
            {
                shotGrid.setValue(c.x, c.y, HIT);
                hit = true;
                break;
            }
        }
        
        // If no ships report a hit, mark it as miss
        if (!hit)
        {
            shotGrid.setValue(c.x, c.y, MISS);
        }
        
        return true; // attack was completed
    }
    
    return false; // attack failed, player needs to try again
}

void Board::addShip(Ship newShip)
{
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
            if (ship.containsCoordinate(coord))
            {
                // If they do then the space
                // is already occupied.
                throw ExceptionShipPlacementOccupied();
            }
        }
    }
    
    ships.push_back(newShip);
}
