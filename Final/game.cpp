#include <fstream>
#include <iostream>
#include <cstdlib>

#include "game.hpp"

using std::cout;
using std::cin;
using std::rand;

void Game::addShipFromPlayer(string name, Board* board)
{
    // This function asks the user for coordinates and orientation to place a
    // ship. The ship length is determined from the name variable, and the board
    // to place it in is given by the board variable.
    // This function also checks for valid coordinates and makes sure the ship
    // does not go out of bounds or overlaps other ships.
    
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
    // This function tries random positions and orientations for a ship until
    // a valid one if found. The length of the ship is determined by the name
    // variable, and the board it's placed in is given by the board variable.
    
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
    // This function places one ship of each kind on the given board until all
    // ship types are placed. If displayChoice is true, the function will
    // confirm ship placements with the player until they are satisfied.
    
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
    // This function reads in information from a number of ships, creates them,
    // and checks for errors when placing them. If an error is detected or a
    // type of ship is missing from the file, the function will ask the player
    // to either place it themselves or place it in a random position.
    
    ifstream file;
    
    try
    {
        file.open("./ship_placement.csv");
        file.ignore(256, '\n'); // ignore first line
    }
    catch (const ifstream::failure) { }
    
    if (file)
    {
        vector<string> shipNames; // This is used to tell if we're missing any
                                  // ships in the ship_placement file
        while (!file.eof())
        {
            string name;
            char x;
            int y;
            char orientation;
            
            getline(file, name, ',');
            shipNames.push_back(name);
            name = toLowercase(name);
            
            file >> x;
            file >> y;
            file.ignore(); // ignore comma
            
            file >> orientation;
            file.ignore(2); // go to next line
            
            Ship newShip = Ship(name, int(x - 'A'), y - 1, orientation);
            
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
        
        while (shipNames.size() < 5)
        {
            // Go through each known ship type
            for (auto shipType : SHIPTYPES)
            {
                bool alreadyAdded = false;
                
                // And each ship we've added
                for (auto shipName : shipNames)
                {
                    if (shipName == shipType.first)
                    {
                        alreadyAdded = true;
                        break;
                    }
                }
                
                // If the current ship type isn't in our list of names, we
                // have to add it manually.
                if (!alreadyAdded)
                {
                    clearScreen();
                    cout << "The position for the " << shipType.first << " wasn't detected in the file given.\n\n"
                    << "Would you like to:\n1) Enter a new position\n2) Get a random position";
                    
                    if (getMenuChoice(2) == 1)
                    {
                        addShipFromPlayer(shipType.first, board);
                    }
                    else
                    {
                        addShipRandomly(shipType.first, board);
                    }
                    
                    shipNames.push_back(shipType.first);
                }
            }
        }
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
    // (human or computer), sets the game mode, gets the names of the players,
    // and when the game is over it asks if the players would like to play again
    
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
    // This function attacks a spot on the player's board depending on the
    // difficulty setting. It generates a random variable, and if it's less than
    // the "HITCHANCE" corresponding to the difficulty level, it will hit a ship.
    // If the random variable is more than the hit chance, it will attack a
    // random coordinate. The attackerIndex variable is used to determine
    // which board is the computer's and which board is the player's.
    // This function returns the shot result when completed.
    
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
    // of attacking that coordinate. The attackerIndex variable is used to
    // determine which board belongs to the player attacking.
    
    // Since this is where the players will be providing the most input, we
    // also use this function to exit the game if the player wants to.
    
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
                
                cout << "Please enter a column letter (from A to J) or enter q to exit: ";
                cin >> column;
                column = toupper(column);
                
                if (tolower(column) == 'q')
                {
                    printBothBoards();
                    exit(0);
                }
                else if (!(column >= 'A' && column <= 'J'))
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
                
                cout << "Please enter a row number (from 1 to 10) or enter -1 to quit: ";
                cin >> row;
                
                if (row == -1)
                {
                    printBothBoards();
                    exit(0);
                }
                else if (!(row >= 1 && row <= 10))
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

void Game::printBothBoards()
{
    // This function outputs both boards to the screen. Used for when a match is
    // concluded so player can view where their opponent's ships were.
    
    clearScreen();
    cout << boards[0]->getName() << "'s board:\n" << *boards[0];
    cout << endl << endl << boards[1]->getName() << "'s board:\n" << *boards[1];
}

void Game::printOpponentTurnResults(vector<ShotResult> results)
{
    // This function prints shot results to the screen so a player can see where
    // their opponent fired at and the results of those attacks last turn. The
    // results vector are the opponent's shot results.
    
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

void Game::printCurrentTurnResults(vector<ShotResult> results, bool playSound = true)
{
    // This function prints the current player's shot results, given by the
    // results variable. If playSound is true, the function will output an
    // alert character, making a noise when the player scores a hit.
    
    if (currentMode == GameMode::Regular)
    {
        cout << "Shot at " << results[0].shotPosition << ": ";
        if (results[0].hit)
        {
            cout << "Hit!";
            
            if (playSound)
            {
                cout << "\a";
            }
            
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
        
        if (hit && playSound)
        {
            cout << "\a"; // Make alert noise if any hits were made
        }
    }
}

void Game::run()
{
    // This is the main game loop for the game. It loops through both boards,
    // getting each player's attacks and checking if either has won.
    
    vector< vector<ShotResult> > turnResults = {vector<ShotResult>(), vector<ShotResult>()}; // Holds shot results for both players
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
                
                // Display the opponent's shot results from their last turn
                // If they have any
                if (turnResults[otherPlayerIndex].size() != 0)
                {
                    printOpponentTurnResults(turnResults[otherPlayerIndex]);
                }
                
                // Display the current player's shot results from their last turn
                // If they have any
                if (turnResults[currentPlayerIndex].size() != 0)
                {
                    cout << "Your shot results from last turn:\n";
                    printCurrentTurnResults(turnResults[currentPlayerIndex], false);
                    turnResults[currentPlayerIndex].clear();
                    cout << endl << endl;
                }
                    
                // Display grids for player
                cout << *boards[currentPlayerIndex] << endl;
                
                if (currentMode == GameMode::Regular)
                {
                    cout << "Enter attack coordinate information:\n";
                    ShotResult result = playerAttack(currentPlayerIndex);
                    boards[currentPlayerIndex]->markShot(result.shotPosition, result.hit);
                    turnResults[currentPlayerIndex].push_back(result);
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
                        turnResults[currentPlayerIndex].push_back(result);
                        
                        // If the other player won, we can stop process their moves
                        if (boards[otherPlayerIndex]->getLost())
                        {
                            break;
                        }
                    }
                }
                
                clearScreen();
                cout << "Your turn results:\n";
                printCurrentTurnResults(turnResults[currentPlayerIndex]);
                
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
                    cin.clear();
                    cin.get();
                    printBothBoards();
                    cout << "\n\nPress enter to continue.";
                    cin.get();
                    return;
                }
            }
            else // if computer player
            {
                turnResults[currentPlayerIndex].clear();
                
                if (currentMode == GameMode::Regular)
                {
                    ShotResult result = AIAttack(currentPlayerIndex);
                    turnResults[currentPlayerIndex].push_back(result);
                    boards[currentPlayerIndex]->markShot(result.shotPosition, result.hit);
                }
                else if (currentMode == GameMode::Salvo)
                {
                    int availableShots = boards[currentPlayerIndex]->shipsRemaining();
                    
                    for (int count = 0; count < availableShots; count++)
                    {
                        ShotResult result = AIAttack(currentPlayerIndex);
                        turnResults[currentPlayerIndex].push_back(result);
                        boards[currentPlayerIndex]->markShot(result.shotPosition, result.hit);
                    }
                }
                
                // If the other player lost, then the current one won!
                if (boards[otherPlayerIndex]->getLost())
                {
                    clearScreen();
                    cout << "\"Gentlemen, it has been a privilage playing with you tonight.\"\n\n";
                    cout << "You were defeated in " << turnNumber << " turns.\n\n";
                    cout << "\n\nPress enter to continue.";
                    cin.clear();
                    cin.get();
                    printBothBoards();
                    cout << "\n\nPress enter to continue.";
                    cin.get();
                    return;
                }
            }
        }
        turnNumber++;
    }
}
