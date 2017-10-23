/*
Implementation of all animal classes 
*/

#include <fstream>
#include <sstream>
#include <iostream>

#include "animal.hpp"

int getInt(ifstream &inputFile)
{
    // This function handles integer input from files
    // It will exit program if it receives bad input
    int input;
    
    if (inputFile >> input)
    {
        inputFile.ignore();
    }
    else
    {
        cout << "Bad input. Exiting...\n";
        exit(1);
    }
    
    return input;
}

bool getBool(ifstream &inputFile)
{
    // This function handles boolean input from files
    // It will exit program if it receives bad input

    string tempInput;
    bool input;
    
    getline(inputFile, tempInput, ',');
    
    for (auto &c : tempInput)
    {
        c = tolower(c);
    }
    
    if (tempInput == "true")
    {
        input = true;
    }
    else if (tempInput == "false")
    {
        input = false;
    }
    else
    {
        cout << "Bad input. Exiting...\n";
        exit(1);
    }
    
    return input;
}

string printBool(bool b)
{
    string out;
    
    if (b)
    {
        out = "Yes";
    }
    else
    {
        out = "No";
    }
    
    return out;
}

/*******************************************************************************
                        Animal Implementation
*******************************************************************************/

Animal::Animal() : _name(""), _color("") { }

Animal::Animal(string name, string color) : _name(name), _color(color) { }

string Animal::getName() const { return _name; }

void Animal::setName(string name) { _name = name; }

string Animal::getColor() const { return _color; }

void Animal::setColor(string color) { _color = color; }

void Animal::makeReceivedInputTrue() { receivedInput = true; }

bool Animal::getReceivedInput() const { return receivedInput; }

/*******************************************************************************
                        Dog Implementation
*******************************************************************************/

Dog::Dog() : Animal("", ""), _breed(""), _age(0), _weight(0) { }

Dog::Dog(string name, string color, string breed, int age, double weight) : Animal(name, color), _breed(breed), _age(age), _weight(weight) { }

void Dog::readInput()
{
    ifstream inputFile("Dog.csv");
    
    if (inputFile.is_open())
    {
        string name, color;
        
        getline(inputFile, name, ',');
        getline(inputFile, _breed, ',');
        _age = getInt(inputFile);
        getline(inputFile, color, ',');
        _weight = getInt(inputFile);
            
        setName(name);
        setColor(color);
        makeReceivedInputTrue();
    }
    else
    {
        cout << "No dog file! Skipping...\n\n";
    }
}

void Dog::printOutput() const
{
    if (getReceivedInput())
    {
        cout << "Dog: \n"
        << "Name: " << getName() << endl
        << "Color: " << getColor() << endl
        << "Breed: " << _breed << endl
        << "Age: " << _age << " years\n"
        << "Weight: " << _weight << " lbs.\n\n";
    }
}

string Dog::getBreed() const { return _breed; }

void Dog::setBreed(string breed) { _breed = breed; }

int Dog::getAge() const { return _age; }

void Dog::setAge(int age) { _age = age; }

int Dog::getWeight() const { return _weight; }

void Dog::setWeight(int weight) { _weight = weight; }

void Dog::subtract10() { _weight -= 10; }

// Fish Implementation

Fish::Fish() : Animal("", ""), _freshwater(true), _habitat(""), _predator(true) { }

Fish::Fish(string name, string color, bool fw, string habitat, bool pred) : Animal(name, color), _freshwater(fw), _habitat(habitat), _predator(pred) { }

void Fish::setFreshwater(bool freshwater) { _freshwater = freshwater; }

bool Fish::getFreshwater() { return _freshwater; }

void Fish::setHabitat(string habitat) { _habitat = habitat; }

string Fish::getHabitat() { return _habitat; }

void Fish::setPredator(bool predator) { _predator = predator; }

bool Fish::getPredator() { return _predator; }

void Fish::readInput()
{
    ifstream inputFile("Fish.csv");
    
    if (inputFile.is_open())
    {
        string name, color;
        
        getline(inputFile, name, ',');
        getline(inputFile, color, ',');
        _freshwater = getBool(inputFile);
        getline(inputFile, _habitat, ',');
        _predator = getBool(inputFile);
        
        setName(name);
        setColor(color);
        makeReceivedInputTrue();
    }
    else
    {
        cout << "No fish file! Skipping...\n\n";
    }
}

void Fish::printOutput() const
{
    if (getReceivedInput())
    {
        cout << "Fish: \n"
        << "Name: " << getName() << endl
        << "Color: " << getColor() << endl
        << "Freshwater fish: " << printBool(_freshwater) << endl
        << "Habitat: " << _habitat << endl
        << "Predator: " << printBool(_predator) << endl << endl;
    }
}

// Horse Implementation

void Horse::add1() { _height += 1; }

void Horse::setManeColor(string color) { _maneColor = color; }

string Horse::getManeColor() { return _maneColor; }

void Horse::setAge(int age) { _age = age; }

int Horse::getAge() { return _age; }

void Horse::setHeight(int height) { _height = height; }

int Horse::getHeight() { return _height; }

void Horse::readInput()
{
    ifstream inputFile("Horse.csv");
    
    if (inputFile.is_open())
    {
        string name, color;
        
        getline(inputFile, name, ',');
        getline(inputFile, color, ',');
        getline(inputFile, _maneColor, ',');
        _age = getInt(inputFile);
        _height = getInt(inputFile);
        
        setName(name);
        setColor(color);
        makeReceivedInputTrue();
    }
    else
    {
        cout << "No horse file! Skipping...\n\n";
    }
}

void Horse::printOutput() const
{
    if (getReceivedInput())
    {
        cout << "Horse: \n"
        << "Name: " << getName() << endl
        << "Body color: " << getColor() << endl
        << "Mane color: " << _maneColor << endl
        << "Age: " << _age << " years" << endl
        << "Height: " << _height << " hands" << endl << endl;
    }
}

// Monkey Implementation

void Monkey::changeEndangered() { _endangered = !_endangered; }

void Monkey::setAge(int age) { _age = age; }

int Monkey::getAge() { return _age; }

void Monkey::setWild(bool wild) { _wild = wild; }

bool Monkey::getWild() { return _wild; }

void Monkey::setHome(string home) { _home = home; }

string Monkey::getHome() { return _home; }

void Monkey::setEndangered(bool end) { _endangered = end; }

bool Monkey::getEndangered() { return _endangered; }

void Monkey::readInput()
{
    ifstream inputFile("Monkey.csv");
    
    if (inputFile.is_open())
    {
        string name, color;
        
        getline(inputFile, name, ',');
        getline(inputFile, color, ',');
        _age = getInt(inputFile);
        _wild = getBool(inputFile);
        getline(inputFile, _home, ',');
        _endangered = getBool(inputFile);
        
        setName(name);
        setColor(color);
        makeReceivedInputTrue();
    }
    else
    {
        cout << "No monkey file! Skipping...\n\n";
    }
}

void Monkey::printOutput() const
{
    if (getReceivedInput())
    {
    cout << "Monkey: \n"
    << "Name: " << getName() << endl
    << "Color: " << getColor() << endl
    << "Age: " << _age << " years" << endl
    << "Wild: " << printBool(_wild) << endl
    << "Home: " << _home << endl
    << "Endangered: " << printBool(_endangered) << endl << endl;
    }
}

// Lizard Implementation

void Lizard::setHabitat(string hab) { _habitat = hab; }

string Lizard::getHabitat() { return _habitat; }

void Lizard::setProtected(bool prot) { _protected = prot; }

bool Lizard::getProtected() { return _protected; }

void Lizard::setWeight(int weight) { _weight = weight; }

int Lizard::getWeight() { return _weight; }

void Lizard::readInput()
{
    ifstream inputFile("Lizard.csv");
    
    if (inputFile.is_open())
    {
        string name, color;
        
        getline(inputFile, name, ',');
        getline(inputFile, color, ',');
        getline(inputFile, _habitat, ',');
        _protected = getBool(inputFile);
        _weight = getInt(inputFile);
        
        setName(name);
        setColor(color);
        makeReceivedInputTrue();
    }
    else
    {
        cout << "No lizard file! Skipping...\n\n";
    }
}

void Lizard::printOutput() const
{
    if (getReceivedInput())
    {
        cout << "Lizard: \n"
        << "Name: " << getName() << endl
        << "Color: " << getColor() << endl
        << "Habitat: " << _habitat << endl
        << "Protected: " << printBool(_protected) << endl
        << "Weight: " << _weight << " lizard weight units" << endl << endl;
    }
}

