#ifndef animal_hpp
#define animal_hpp

#include <string>

using namespace std;

class Animal
{
private:
    string _name;
    string _color;
    bool receivedInput = false;

protected:
    void makeReceivedInputTrue();
    
public:
    Animal();
    Animal(string, string);
    virtual void readInput() = 0;
    virtual void printOutput() const = 0;
    string getName() const;
    void setName(string);
    string getColor() const;
    void setColor(string);
    bool getReceivedInput() const;
};

class Dog : public Animal
{
private:
    string _breed;
    int _age, _weight;
    
public:
    Dog();
    Dog(string, string, string, int, double);
    virtual void readInput() override;
    virtual void printOutput() const override;
    string getBreed() const;
    void setBreed(string);
    int getAge() const;
    void setAge(int);
    int getWeight() const;
    void setWeight(int);
    void subtract10();
};

class Fish : public Animal
{
    bool _freshwater;
    string _habitat;
    bool _predator;
    
public:
    Fish();
    Fish(string, string, bool, string, bool);
    virtual void readInput() override;
    virtual void printOutput() const override;
    void setFreshwater(bool);
    bool getFreshwater();
    void setHabitat(string);
    string getHabitat();
    void setPredator(bool);
    bool getPredator();
};

class Horse : public Animal
{
    string _maneColor;
    int _age;
    int _height;
    
public:
    virtual void readInput() override;
    virtual void printOutput() const override;
    void add1();
    void setManeColor(string);
    string getManeColor();
    void setAge(int);
    int getAge();
    void setHeight(int);
    int getHeight();
};

class Monkey : public Animal
{
    int _age;
    bool _wild;
    string _home;
    bool _endangered;
    
public:
    virtual void readInput() override;
    virtual void printOutput() const override;
    void changeEndangered();
    void setAge(int);
    int getAge();
    void setWild(bool);
    bool getWild();
    void setHome(string);
    string getHome();
    void setEndangered(bool);
    bool getEndangered();
};

class Lizard : public Animal
{
    string _habitat;
    bool _protected;
    int _weight;
    
public:
    virtual void readInput() override;
    virtual void printOutput() const override;
    void setHabitat(string);
    string getHabitat();
    void setProtected(bool);
    bool getProtected();
    void setWeight(int);
    int getWeight();
};

#endif /* animal_hpp */
