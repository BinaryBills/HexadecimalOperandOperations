#pragma once
#include <string>
using namespace std;

/*************************************************************
					String Parsing Functions
*************************************************************/
string getOp1(string l, string op) { return l.substr(0, l.find(op)); }
string getOp2(string l, string op2, int opIndex) { op2 = l.substr(opIndex + 1); 
op2.erase(remove(op2.begin(), op2.end(), '='), op2.end()); return op2;}

int getOp(string l)
{
	for (int i = 0; i < l.size(); i++)
	{
		if (l[i] == '+' || l[i] == '-' || l[i] == '*' || l[i] == '/' || l[i] == '$')
			return i;
	}
	//Returns -1 if supported operand not found
	return -1;
}

/*************************************************************
             Decimal and Hex Conversion Functions
*************************************************************/

int hexToDec(char hex)
{
	if (hex >= '0' && hex <= '9')
		//Converts a char into an integer
		return hex - '0';

	else if (hex == 'A')
		return 10;

	else if (hex == 'B')
		return 11;

	else if (hex == 'C')
		return 12;

	else if (hex == 'D')
		return 13;

	else if (hex == 'E')
		return 14;

	else if (hex == 'F')
		return 15;

	else
		//Returns -1 if an invalid input is made
		return -1;
}

char decToHex(int decimal)
{
	if (decimal >= 0 && decimal <= 9)
		//Converts an integer into a char
		return decimal + '0';

	else if (decimal == 10)
		return 'A';

	else if (decimal == 11)
		return 'B';

	else if (decimal == 12)
		return 'C';

	else if (decimal == 13)
		return 'D';

	else if (decimal == 14)
		return 'E';

	else if (decimal == 15)
		return 'F';

	else
		//Returns 'X' if an invalid input is made
		return 'X';
}

