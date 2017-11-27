#include <fstream>
#include <iostream>
#include <cstdlib>

#include "game.hpp"

using std::cout;
using std::cin;
using std::rand;

void Game::addShipFromPlayer(string name, Board* board)
{
    bool valid = true;
    char x;
    int y;
    Ship ship;
    int length = getShipLengthFromName(name);
    string part; // This will tell the player what part of the ship they're
                 // placing
    
    do
    {
        valid = true;
        
        char orientation;
        int validXRange = int('J' - 'A'), validYRange = 10;
        
        clearScreen();
        board->printShipGrid();
        cout << "\nYou're placing: " << name;
        cout << "\nIt looks like this: ";
        
        // Get length
        for (int count = 0; count < length; count++)
        {
            cout << name[0];
        }
        
        // Get orientation
        cout << "\n\nChoose orientation:\n1) Horizontal\n2) Vertical";
        if (getMenuChoice(2) == 1)
        {
            orientation = HORIZONTAL;
            validXRange = int('J' - length - 'A') + 1;
            part = "leftmost";
        }
        else
        {
            orientation = VERTICAL;
            validYRange -= length - 1;
            part = "top";
        }
        
        // Get x position
        bool validX = true;
        cout << "Please enter a column to put the " << part << " of the ship.";
        do
        {
            validX = true;
            cout << "\nMust be a letter from A to " << char('A' + validXRange);
            cout << "\n> ";
            cin >> x;
            x = toupper(x);
            
            // I'm not sure why I have to do this but I do..
            if (x < 'A' || x > char(validXRange + 'A'))
            {
                validX = false;
            }
        } while (!validX);
        
        // Get y position
        bool validY = true;
        cout << "\nPlease enter a row to put the " << part << " part of the ship.";
        do
        {
            validY = true;
            cout << "\nMust be a number from 1 to " << validYRange;
            cout << "\n> ";
            cin >> y;
            
            if (y < 1 || y > validYRange)
            {
                validY = false;
            }
        } while (!validY);
        
        // Set values
        ship.setPosX(int(x - 'A'));
        ship.setPosY(y - 1);
        ship.setOrientation(orientation);
        ship.setName(name);
        ship.setLength(length);
        
        // Try to place ship
        try
        {
            board->addShip(ship);
        }
        catch (ExceptionShipPlacementOccupied)
        {
            valid = false;
            clearScreen();
            cout << "Your ship overlaps another ship. Would you like to"
            << "\n1) Try again\n2) Place ship randomly";
            
            if (getMenuChoice(2) == 2)
            {
                valid = true;
                addShipRandomly(name, board);
            }
        }
        
    } while (!valid);
    
}

void Game::addShipRandomly(string name, Board* board)
{
    bool valid = true;
    Ship ship;
    int length = getShipLengthFromName(name);
    
    ship.setLength(length);
    ship.setName(name);
    
    do
    {
        valid = true;
        
        int orientation = rand() % 2;
        int x = 0, y = 0;
        
        if (orientation == 1) // horizontal
        {
            x = rand() % (10 - length);
            y = rand() % 10;
            ship.setOrientation(HORIZONTAL);
        }
        else // vertical
        {
            x = rand() % 10;
            y = rand() % (10 - length);
            ship.setOrientation(VERTICAL);
        }
        
        ship.setPosX(x);
        ship.setPosY(y);
        
        try
        {
            board->addShip(ship);
        }
        catch (ExceptionShipPlacementOccupied)
        {
            valid = false;
        }
    } while (!valid);
}

void Game::randomizeShips(Board *board, bool displayChoice = true)
{
    // Adds one ship of each kind to a random location
    // on the given board.
    
    if (displayChoice)
    {
        do
        {
            clearScreen();
            board->removeShips();
            
            for (auto ship : SHIPTYPES)
            {
                addShipRandomly(ship.first, board);
            }
            
            board->printShipGrid();
            
        } while (getMenuChoice(2, "\nWould you like to keep these positions or generate a new fleet?\n1) Keep positions\n2) Generate new ships") == 2);
    }
    else
    {
        board->removeShips();
        
        for (auto ship : SHIPTYPES)
        {
            addShipRandomly(ship.first, board);
        }
    }
}

void Game::readShips(Board *board)
{
    ifstream file;
    
    try
    {
        file.open("./ship_placement.csv");
        file.ignore(256, '\n'); // ignore first line
    }
    catch (const ifstream::failure) { }
    
    if (file)
    {
        for (int shipCount = 5; shipCount > 0; shipCount--)
        {
            string name;
            char x, y;
            char orientation;
            
            getline(file, name, ',');
            name = toLowercase(name);
            
            file >> x;
            file >> y;
            file.ignore(); // ignore comma
            
            file >> orientation;
            file.ignore(2); // go to next line
            
            Ship newShip = Ship(name, int(x - 'A'), int(y - '1'), orientation);
            
            try
            {
                board->addShip(newShip);
            }
            catch (ExceptionShipOutOfBounds)
            {
                clearScreen();
                cout << "The " << name << " from the file was out of bounds.\n\n"
                << "Would you like to:\n1) Enter a new position\n2) Get a random position";
                
                if (getMenuChoice(2) == 1)
                {
                    addShipFromPlayer(name, board);
                }
                else
                {
                    addShipRandomly(name, board);
                }
            }
            catch (ExceptionShipPlacementOccupied)
            {
                clearScreen();
                cout << "The position for the " << name << " read in from the file was occupied by another ship.\n\n"
                << "Would you like to:\n1) Enter a new position\n2) Get a random position";
                
                if (getMenuChoice(2) == 1)
                {
                    addShipFromPlayer(name, board);
                }
                else
                {
                    addShipRandomly(name, board);
                }
            }
        }
        
        file.close();
    }
    else
    {
        clearScreen();
        cout << "Would you like to: \n";
        cout << "1) Choose ship locations manually or\n";
        cout << "2) Randomize ship locations";
        
        if (getMenuChoice(2) == 1)
        {
            for (auto ship : SHIPTYPES)
            {
                addShipFromPlayer(ship.first, boards[0]);
            }
        }
        else
        {
            randomizeShips(boards[0]);
        }
    }
}

void Game::start()
{
    // This function sets up a game.
    // It prints the title, creates boards of specific types
    // (human or computer), gets the names of the players, and when the game
    // is over it asks if the players would like to play again.
    
    srand(int(time(NULL)));
    
    if (!debug)
    {
        // Display title
        clearScreen();
        cout << title;
        cout << setw(44) << "Cody Kelly" << endl;
        cout << setw(43) << "© 2017" << endl << endl;
        cout << "Press enter to continue.\n\n";
        cin.get();
    }
    
    do
    {
        // Display main menu
        clearScreen();
        cout << "\n\nWelcome to Battleship!\n\n";
        cout << "Main Menu\n1) Start classic mode\n2) Start salvo mode";
        int modeChoice = getMenuChoice(2);
        
        switch (modeChoice)
        {
            case 1:
                currentMode = GameMode::Regular;
                break;
            case 2:
                currentMode = GameMode::Salvo;
                
            default:
                break;
        }
        
        // Get number of players
        clearScreen();
        cout << "Please choose:\n1) One player\n2) Two players";
        singlePlayer = getMenuChoice(2) == 1;
        clearScreen();
        
        if(singlePlayer)
        {
            // Setup single player game
            string name;
            boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Computer);
            
            if (!debug)
            {
                cout << "Please enter your name: ";
                name = getStringInput();
                boards[0]->setName(name);
            }
            
            clearScreen();
            cout << "Please choose difficulty:\n1) Easy\n2) Normal\n3) Hard\n4) EXTREME!!";
            int choice = getMenuChoice(4);
            
            switch (choice)
            {
                case 1:
                    currentDifficulty = Difficulty::Easy;
                    break;
                    
                case 2:
                    currentDifficulty = Difficulty::Normal;
                    break;
                    
                case 3:
                    currentDifficulty = Difficulty::Hard;
                    break;
                    
                case 4:
                    currentDifficulty = Difficulty::Extreme;
                    break;
                    
                default:
                    break;
            }
            
            boards[1]->setName("Computer");
                
            readShips(boards[0]); // Read ships from file for player
            randomizeShips(boards[1], false); // Get a random ship layout for AI
        }
        else
        {
            // Setup multiplayer game
            string name;
            
            boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Human);
            
            cout << "Player 1, please enter your name: ";
            name = getStringInput();
            boards[0]->setName(name);
            
            clearScreen();
            cout << "Would you like to: \n";
            cout << "1) Choose ship locations manually or\n";
            cout << "2) Randomize ship locations";
            
            if (getMenuChoice(2) == 1)
            {
                for (auto ship : SHIPTYPES)
                {
                    addShipFromPlayer(ship.first, boards[0]);
                }
            }
            else
            {
                randomizeShips(boards[0]);
            }
            
            clearScreen();
            cout << "Player 2, please enter your name: ";
            name = getStringInput();
            boards[1]->setName(name);
            
            clearScreen();
            cout << "Would you like to: \n";
            cout << "1) Choose ship locations manually or\n";
            cout << "2) Randomize ship locations";
            
            if (getMenuChoice(2) == 1)
            {
                for (auto ship : SHIPTYPES)
                {
                    addShipFromPlayer(ship.first, boards[1]);
                }
            }
            else
            {
                randomizeShips(boards[1]);
            }
        }
        
        // Now that the game is set up, we may run it.
        run();
        
        // Delete all board pointers in boards array
        for (auto boardPointer : boards)
        {
            delete boardPointer;
        }
        
        clearScreen();
        
    } while (getMenuChoice(2, "Would you like to play again?\n1) Yes\n2) No") == 1);
}

ShotResult Game::AIAttack(int attackerIndex)
{
    // This function calculates an attack coordinate for the computer player
    
    ShotResult result;
    bool validCoordinate = true;
    int otherPlayerIndex;
    int hitChance = 0;
    int randNum = rand() % 100;
    
    if (attackerIndex == 0)
    {
        otherPlayerIndex = 1;
    }
    else
    {
        otherPlayerIndex = 0;
    }
    
    switch (currentDifficulty)
    {
        case Normal:
            hitChance = HITCHANCENORMAL;
            break;
            
        case Hard:
            hitChance = HITCHANCEHARD;
            break;
            
        case Extreme:
            hitChance = HITCHANCEEXTREME;
            break;
            
        default:
            break;
    }
    
    if (randNum < hitChance) // If we're guaranteed a hit
    {
        do
        {
            validCoordinate = true;
            
            int randShipNum = rand() % 5;
            
            // First we get a vector containing all the ships on the
            // other person's board
            vector<Ship*> ships = boards[otherPlayerIndex]->getShips();
            
            // Then we get a random ship from that vector
            Ship* ship = ships[randShipNum];
            
            // Now we choose a random coordinate within that ship
            int randShipCoordinateIndex = rand() % ship->getLength();
            Coordinate randCoord = ship->getCoordinatesContained()[randShipCoordinateIndex];
            
            // Then we attack that coordinate
            try
            {
                result = boards[otherPlayerIndex]->attack(randCoord);
            }
            catch (ExceptionShotCoordinateOccupied)
            {
                validCoordinate = false;
            }
            
        } while (!validCoordinate);
    }
    else // otherwise, pick a random coordinate
    {
        do
        {
            validCoordinate = true;
            
            // Get random coordinates
            int x = rand() % 10;
            int y = rand() % 10;
            
            // Try attack
            try
            {
                result = boards[otherPlayerIndex]->attack(Coordinate(x, y));
            }
            catch (ExceptionShotCoordinateOccupied)
            {
                validCoordinate = false;
            }
        } while (!validCoordinate);
    }
    
    return result;
}

ShotResult Game::playerAttack(int attackerIndex)
{
    // This function asks user for a coordinate, then returns the result
    // of attacking that coordinate
    
    Coordinate coord;
    bool validCoordinate = true;
    int otherPlayerIndex;
    ShotResult result;
    
    if (attackerIndex == 0)
    {
        otherPlayerIndex = 1;
    }
    else
    {
        otherPlayerIndex = 0;
    }
    
    do
    {
        try
        {
            bool validColumn = true;
            bool validRow = true;
            validCoordinate = true;
            
            // Get x coordinate
            do
            {
                char column;
                
                validColumn = true;
                
                cout << "Please enter a column letter (from A to J): ";
                cin >> column;
                column = toupper(column);
                
                if (!(column >= 'A' && column <= 'J'))
                {
                    validColumn = false;
                    cout << "\nInvalid column. Please enter a letter from A to J.\n";
                }
                else
                {
                    coord.x = int(column - 'A');
                }
            } while (!validColumn);
            
            // Get y coordinate
            do
            {
                int row;
                
                validRow = true;
                
                cout << "Please enter a row number (from 1 to 10): ";
                cin >> row;
                
                if (!(row >= 1 && row <= 10))
                {
                    validRow = false;
                    cout << "\nInvalid row. Please enter a number from 1 to 10.\n";
                }
                else
                {
                    coord.y = row - 1;
                }
            } while (!validRow);
            
            // Try attack
            result = boards[otherPlayerIndex]->attack(coord);
        }
        catch (ExceptionShotCoordinateOccupied)
        {
            cout << "\n\nThat position has been fired at already. Please choose another.\n";
            validCoordinate = false;
        }
    }
    while (!validCoordinate);
    
    return result;
}

void Game::printLastTurnResults(vector<ShotResult> results)
{
    if (currentMode == GameMode::Regular)
    {
        cout << "Last enemy shot: " << results[0].shotPosition;
        
        if (results[0].sunk)
        {
            cout << "\nThey sank your " << toLowercase(results[0].shipName) << "!";
        }
        else if(results[0].hit)
        {
            cout << "\nThey hit your " << toLowercase(results[0].shipName) << "!";
        }
        
        cout << endl;
    }
    else if (currentMode == GameMode::Salvo)
    {
        int count = 1;
        
        cout << "Enemy shot results:\n";
        for (auto shot : results)
        {
            cout << "Shot #" << count << " at position " << shot.shotPosition
            << ": ";
            
            if (shot.sunk)
            {
                cout << "Sunk your " << toLowercase(shot.shipName) << "!";
            }
            else if(shot.hit)
            {
                cout << "Hit your " << toLowercase(shot.shipName) << "!";
            }
            else
            {
                cout << "Missed.";
            }
            
            count++;
            cout << endl;
        }
    }
    
    cout << endl;
}

void Game::printCurrentTurnResults(vector<ShotResult> results)
{
    clearScreen();
    
    if (currentMode == GameMode::Regular)
    {
        if (results[0].hit)
        {
            cout << "\aHit!";
            
            if (results[0].sunk)
            {
                cout << "\nYou sank their " << toLowercase(results[0].shipName) << "!";
            }
        }
        else
        {
            cout << "Miss.";
        }
    }
    else if (currentMode == GameMode::Salvo)
    {
        int count = 1;
        bool hit = false;
        
        cout << "Your shot results:\n";
        for (auto shot : results)
        {
            cout << "Shot #" << count << " at position " << shot.shotPosition
            << ": ";
            
            if (shot.sunk)
            {
                cout << "Sank their " << toLowercase(shot.shipName) << "!";
                hit = true;
            }
            else if(shot.hit)
            {
                cout << "Hit their " << toLowercase(shot.shipName) << "!";
                hit = true;
            }
            else
            {
                cout << "Missed.";
            }
            
            count++;
            cout << endl;
        }
        
        if (hit)
        {
            cout << "\a"; // Make alert noise if any hits were made
        }
    }
}

void Game::run()
{
    vector<ShotResult> lastTurnResults;
    int turnNumber = 1;
    
    while (true)
    {
        for (int currentPlayerIndex = 0; currentPlayerIndex < 2; currentPlayerIndex++)
        {
            
            int otherPlayerIndex = 0;
            
            if (currentPlayerIndex == 0)
            {
                otherPlayerIndex = 1;
            }
            else
            {
                otherPlayerIndex = 0;
            }
            
            if (boards[currentPlayerIndex]->getPlayerType() == Board::PlayerType::Human)
            {
                if (!singlePlayer)
                {
                    clearScreen();
                    cout << "Your turn, " << boards[currentPlayerIndex]->getName() << ".\n";
                    cout << "Press enter when ready.";
                    cin.get();
                }
                
                clearScreen();
                if (turnNumber != 1)
                {
                    printLastTurnResults(lastTurnResults);
                    lastTurnResults.clear();
                }
                    
                // Display grids for player
                cout << *boards[currentPlayerIndex] << endl;
                
                // Process player's attacks
                if (currentMode == GameMode::Regular)
                {
                    cout << "Enter attack coordinate information:\n";
                    ShotResult result = playerAttack(currentPlayerIndex);
                    boards[currentPlayerIndex]->markShot(result.shotPosition, result.hit);
                    lastTurnResults.push_back(result);
                }
                else if (currentMode == GameMode::Salvo)
                {
                    int availableShots = boards[currentPlayerIndex]->shipsRemaining();
                    
                    cout << "You have " << availableShots << " available shots.";
                    
                    for (int count = 0; count < availableShots; count++)
                    {
                        // Get the player's choice for a shot and process it
                        cout << "\n\nEnter coordinates for attack #" << count + 1
                        << ":\n";
                        ShotResult result = playerAttack(currentPlayerIndex);
                        boards[currentPlayerIndex]->markShot(result.shotPosition, result.hit);
                        lastTurnResults.push_back(result);
                    }
                }
                
                printCurrentTurnResults(lastTurnResults);
                
                cout << "\n\nPress enter to continue.";
                cin.ignore();
                cin.get();
                
                // If the other player lost, then the current one won!
                if (boards[otherPlayerIndex]->getLost())
                {
                    clearScreen();
                    cout << "Congratulations, " << boards[currentPlayerIndex]->getName()
                    << "! You've sunk the enemy's entire fleet in "
                    << turnNumber << " turns.\n\nYou win!!";
                    cout << "\n\nPress enter to continue.";
                    cin.get();
                    return;
                }
            }
            else // if computer player
            {
                lastTurnResults.clear();
                
                if (currentMode == GameMode::Regular)
                {
                    lastTurnResults.push_back(AIAttack(currentPlayerIndex));
                }
                else if (currentMode == GameMode::Salvo)
                {
                    int availableShots = boards[currentPlayerIndex]->shipsRemaining();
                    
                    for (int count = 0; count < availableShots; count++)
                    {
                        lastTurnResults.push_back(AIAttack(currentPlayerIndex));
                    }
                }
            }
        }
        
        turnNumber++;
    }
}
