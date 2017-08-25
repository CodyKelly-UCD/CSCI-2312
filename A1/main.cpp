#include <iostream>
#include <iomanip>

using namespace std;

const int TABLEWIDTH = 30;

int GetInput()
{

}

void CalculatePlants(int input) 
{
	// Header
	cout << "\n\nPlant sales of " << input << " plants:\n\n";

	// Column names
	cout << setw(TABLEWIDTH) << left << "Outdoor temp:" << "Number of plants sold:" << endl;

	// Divider
	cout << setw(TABLEWIDTH) << setfill('-') << '-' << setw(TABLEWIDTH) << '-' << endl << setfill(' ');

	// Data
	cout << setw(TABLEWIDTH) << left << "Colder than 40 degrees:";
	cout << setw(TABLEWIDTH) << left << (int)(input * 0.1);
	cout << setw(TABLEWIDTH) << left << "Between 40 and 60 degrees:";
	cout << setw(TABLEWIDTH) << left << (int)(input * 0.3);
	cout << setw(TABLEWIDTH) << left << "Between 61 and 70 degrees:";
	cout << setw(TABLEWIDTH) << left << (int)(input * 0.5);
	cout << setw(TABLEWIDTH) << left << "Between 71 and 80 degrees:";
	cout << setw(TABLEWIDTH) << left << (int)(input * 0.6);
	cout << setw(TABLEWIDTH) << left << "Hotter than 80 degrees:";
	cout << setw(TABLEWIDTH) << left << (int)(input * .4);

	cout << endl;
}

int main()
{
	int input = 0;

	cout << "Welcome to the Plant Sale Estimator\n\n";

	cout << "Please input the number of plants in inventory (input -1 to quit): ";
	cin >> input;

	while (input != -1)
	{
		CalculatePlants(input);

		cout << "Please input the number of plants in inventory (input -1 to quit): ";
		cin >> input;
	}

	return 0;
}