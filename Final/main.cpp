#include "game.hpp"

int main()
{
    do
    {
        Game game;
        
        game.start();
        
    } while (getMenuChoice(2, "Would you like to play again?\n1) Yes\n2) No") == 1);
    
    return 0;
}
