#include <vector>

#include "animal.hpp"

int main()
{
    Dog dog;
    Fish fish;
    Horse horse;
    Monkey monkey;
    Lizard lizard;
    
    dog.readInput();
    dog.subtract10();
    
    fish.readInput();
    
    horse.readInput();
    horse.add1();
    
    monkey.readInput();
    monkey.changeEndangered();

    lizard.readInput();
    
    dog.printOutput();
    fish.printOutput();
    horse.printOutput();
    monkey.printOutput();
    lizard.printOutput();
    
    return 0;
}
