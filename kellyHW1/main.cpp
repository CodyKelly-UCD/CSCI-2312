// Cody Kelly
// CSCI 2312
// Assignment #1
// August 26th, 2017
// This program calculates an estimate of plant sales based on temperature and
// number of plants being sold.

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

const int COLUMNWIDTH = 30; // Width of columns in the printed table

int getInput()
{
	// Prints a prompt, then accepts and returns an input from the user.

	int input = 0;

	cout << "Please input the number of plants in inventory (input -1 to quit): ";
	cin >> input;

	return input;
}

void printSales(int input) 
{
	// Takes an integer number of plants and calculates and prints a table of estimated sales based on 
	// temperatures outside.

	cout << "\n\nPlant sales of " << input << " plants:\n\n";
	cout << setw(COLUMNWIDTH) << left << "Outdoor temp:" << "Number of plants sold:" << endl;
	cout << setw(COLUMNWIDTH) << setfill('-') << '-' << setw(COLUMNWIDTH) << '-' << endl << setfill(' ');
	cout << setw(COLUMNWIDTH) << left << "Colder than 40 degrees:";
	cout << setw(COLUMNWIDTH) << left << input * 0.1 << endl;
	cout << setw(COLUMNWIDTH) << left << "Between 40 and 60 degrees:";
	cout << setw(COLUMNWIDTH) << left << input * 0.3 << endl;
	cout << setw(COLUMNWIDTH) << left << "Between 61 and 70 degrees:";
	cout << setw(COLUMNWIDTH) << left << input * 0.5 << endl;
	cout << setw(COLUMNWIDTH) << left << "Between 71 and 80 degrees:";
	cout << setw(COLUMNWIDTH) << left << input * 0.6 << endl;
	cout << setw(COLUMNWIDTH) << left << "Hotter than 80 degrees:";
	cout << setw(COLUMNWIDTH) << left << input * .4 << endl;
	cout << endl;
	assert(input > 40);
}

int main()
{
	int input = 0;

	cout << "Welcome to the Plant Sale Estimator\n\n";

	input = getInput();

	while (input != -1)
	{
		printSales(input);
		input = getInput();
	}

	return 0;
}
