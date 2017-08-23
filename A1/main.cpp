#include <iostream>
#include <iomanip>

using namespace std;

const int TABLEWIDTH = 30;

int GetInput()
{
	int input = 0;

	cout << "Please input the number of plants in inventory (input -1 to quit): ";
	cin >> input;

	return input;
}

void FormatOutput(string msg, int plants)
{
	cout << setw(TABLEWIDTH) << left << msg;
	cout << setw(TABLEWIDTH) << left << plants << endl;
}

void CalculatePlants(int input) 
{
	cout << "\n\nPlant sales of " << input << " plants:\n\n";
	cout << setw(TABLEWIDTH) << left << "Outdoor temp:" << "Number of plants sold:" << endl;
	cout << setw(TABLEWIDTH) << setfill('-') << '-' << setw(TABLEWIDTH) << '-' << endl << setfill(' ');
	FormatOutput("Colder than 40 degrees:", input * 0.1);
	FormatOutput("Between 40 and 60 degrees:", input * 0.3);
	FormatOutput("Between 61 and 70 degrees:", input * 0.5);
	FormatOutput("Between 71 and 80 degrees:", input * 0.6);
	FormatOutput("Hotter than 80 degrees:", input * .4);
	cout << endl;
}

int main()
{
	int input = 0;

	cout << "Welcome to the Plant Sale Estimator\n\n";

	input = GetInput();

	while (input != -1)
	{
		CalculatePlants(input);
		input = GetInput();
	}

	return 0;
}