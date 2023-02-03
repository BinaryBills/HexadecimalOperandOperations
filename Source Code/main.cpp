/*Author: Binary Bills
*Creation Date: 
*Modification Date:
*Purpose: This program performs +, -, *, / and $ on hexadecimal operands. 
The maximum length of any operand or a solution is 40 digits.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "helperfuncs.h"
using namespace std;

void executeOperation(string, string, string);
string add(string, string);
string sub(string, string);
string mult(string, string);
string pow(string op1, string op2);
string div(string, string);

/*************************************************************
Opens Test Data From An Input File & Executes Math Operations
*************************************************************/
int main()
{
	fstream testData;
	string op, op1, op2, line = "";
	int operandIndex = 0;
	testData.open("testData.txt");

	while (!testData.eof())
	{
		testData >> line;

		//Retrieves Operand Sign From File
		operandIndex = getOp(line);
		op = line[operandIndex];

		//Retrieves Operand One From File
		op1 = getOp1(line, op);

		//Retrieves Operand Two From File
		op2 = getOp2(line, op, operandIndex);

		//Program only accepts operands of 40 digits or less
		if (op1.size() < 40 && op2.size() < 40)
			executeOperation(op, op1, op2);
		else
			cerr << "One of the operands for " << line << " is over 40 digits\n";
	}
}


/*************************************************************
	Select operations based off the operand sign
*************************************************************/
void executeOperation(string op, string op1, string op2)
{
	string solution = "";
	if (op == "+")
		solution = add(op1, op2);
	else if (op == "-")
		solution = sub(op1, op2);
	else if (op == "*")
		solution = mult(op1, op2);
	else if (op == "$")
		solution = pow(op1, op2);
	else if (op == "/")
		solution = div(op1, op2);
	else { cout << "ERROR!\n"; return; }

	//Program display solutions of 40 digits or less
	if (solution.size() < 40 && solution != "")
		cout << op1 << op << op2 << " = " << solution << endl;
	else
		cerr << op1 << op << op2 << " NOT SUPPORTED! OVER 40 DIGITS!" << endl;
}

/*************************************************************
			   Adding Hex numbers digit-by-digit
*************************************************************/
string add(string op1, string op2)
{
	int currSum, carry = 0;
	int op1Pos = op1.size() - 1; //Current index of op1 being processed
	int op2Pos = op2.size() - 1; //Current index of op2 being processed
	string resultStr, tempStr = "";

	while (op1Pos > -1 || op2Pos > -1)
	{
		currSum = 0;

		//Performs the addition of EVERY digit in op1 and op2 while considering
		//the fact they might not be of equal size by checking their index 
		if (op1Pos > -1 && op2Pos > -1)
			currSum = hexToDec(op1[op1Pos]) + hexToDec(op2[op2Pos]) + carry;
		else if (op1Pos > -1 && op2Pos < 0)
			currSum = hexToDec(op1[op1Pos]) + carry;
		else
			currSum = hexToDec(op2[op2Pos]) + carry;

		//Figures out carry (if one exists) for the next iteration
		carry = currSum / 16;
		tempStr = decToHex(currSum - (16 * carry));
		resultStr.insert(0, tempStr);

		//Goes to the next index of the digits to be added
		op1Pos--;
		op2Pos--;
	}

	//Adds any leftover carry
	tempStr = decToHex(carry);
	resultStr.insert(0, tempStr);

	//Removes any zero's in the front of resultStr
	if (resultStr[0] == '0')
		resultStr.erase(0, 1);

	return resultStr;
}

/*************************************************************
			   Subtracting Hex numbers digit-by-digit
*************************************************************/
string sub(string op1, string op2)
{
	string resultStr, tempStr = "";
	int op1Val, op2Val = 0; //Holds a value associated with an index
	int op1Pos = op1.length() - 1; //Current index of op1 being processed
	int op2Pos = op2.length() - 1; //Current index of op2 being processed
	int op1NextPos = 0; //Next index of op1 to get processed


	while (op1Pos > -1 && op2Pos > -1)
	{
		op1Val = hexToDec(op1[op1Pos]); 
		op2Val = hexToDec(op2[op2Pos]); 
		op1NextPos = op1Pos - 1; 

		//Case One: No borrow needed
		if (op1Val >= op2Val)
		{
			tempStr = decToHex(op1Val - op2Val);
			resultStr.insert(0, tempStr);
		}
		
		//Case Two: We cannot borrow since there is no next number for op1.
		else if (op1NextPos <= -1)
			return "NEGATIVE";

		//Case Three: We can borrow from the next position in the sequence.
		else
		{
			//Multiple zeroes in a row case. Find first whole number.
			while (op1[op1NextPos] == '0')
				op1NextPos--;


			//Found whole number we can borrow from. 
			if (op1NextPos > -1)
			{
				op1[op1NextPos] = decToHex(hexToDec(op1[op1NextPos]) - 1);

				while (op1NextPos < op1Pos)
				{
					op1NextPos++;
					op1[op1NextPos] = 'F';
				}
			}
			tempStr = decToHex(op1Val - op2Val + 16);
			resultStr.insert(0, tempStr);
		}
		op1Pos--;
		op2Pos--;
	}

	//If op1 had more digits than op2, we add the leftover numbers. 
	if (op1Pos > -1)
	{
		while (op1Pos > -1)
		{
			tempStr = op1[op1Pos];
			resultStr.insert(0, tempStr);
			op1Pos--;
		}
	}

	//Removes any zero's in the front of the resultStr
	if (resultStr[0] == '0')
		resultStr.erase(0, 1);
	return resultStr;
}

/*************************************************************
				Multiplication Simulation
*************************************************************/
string mult(string op1, string op2)
{
	int counter;
	string currSum;
	std::stringstream stream(op2);
	stream >> std::hex >> counter;

	for (int i = 0; i < counter; i++)
		currSum = add(currSum, op1);
	return currSum;
}

/*************************************************************
				Exponentation Simulation
*************************************************************/
string pow(string op1, string op2)
{
	int exp;
	string currTotal = op1;
	std::stringstream stream(op2);
	stream >> std::hex >> exp;

	for (int i = 0; i < exp; i++)
		currTotal = mult(currTotal, op1);
	return currTotal;
}

/*************************************************************
					Division Simulation
*************************************************************/
string div(string op1, string op2)
{
	string remainder = op1;
	string quotient;
	string result;

	while (sub(remainder, op2) != "NEGATIVE")
	{
		remainder = sub(remainder, op2);
		quotient = add(quotient, "1");
	}

	result.insert(0, " Remainder:" + remainder);
	result.insert(0, "Quotient:" + quotient);
	return result;
}
