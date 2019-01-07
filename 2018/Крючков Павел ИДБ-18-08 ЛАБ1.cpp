// Calculator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int from_base_2(int N, int I, int S)
{
	while (N > 0)
	{
		S += (pow(2, I) * (N % 10));
		I++;
		N /= 10;
	}
	return S;
}

int to_base_2(int N)
{
	if (N > 1)
	{
		to_base_2(N >> 1);
	}
	cout << (N & 1);
	return 0;
}

long int fact(int N)
{
	if (N < 0)
	{
		return 0; //error
	}
	if (N == 0)
	{
		return 1; //exception
	}
	else
	{
		return N * fact(N - 1); //recursion
	}
}

long double calculus(bool N)
{
	int a, b;
	string func;

	if (N == true)
	{
		cout << "INPUT NUMBER(S) AND FUNCTION\n> ";
	}
	cin >> a >> func;
	if (func == "+")
	{
		cin >> b;
		return a + b;
	}
	if (func == "-")
	{
		cin >> b;
		return a - b;
	}
	if (func == "/")
	{
		cin >> b;
		return a / b;
	}
	if (func == "*")
	{
		cin >> b;
		return a * b;
	}
	if (func == "!") //factorial
	{
		return fact(a);
	}
	if (func == "sin") //sin
	{
		return sin(a);
	}
	if (func == "cos") //cos
	{
		return cos(a);
	}
	if (func == "tg") //tg
	{
		return tan(a);
	}
	if (func == "ctg") //ctg
	{
		return 1 / tan(a);
	}
	if (func == "pow") //rise to power
	{
		cin >> b;
		return pow(a, b);
	}
	if (func == "sqrt") //square root
	{
		return sqrt(a);
	}
	if (func == "cbrt") //cubic root
	{
		return cbrt(a);
	}
	if (func == "ln") //log
	{
		return log(a);
	}
	else
	{
		cout << "INPUT PROPER NUMBERS AND FUNCTION FELLOW HUMAN\n> "; //error
		return calculus(false);
	}
}

int in_base(bool N)
{
	int a, base, base_result;

	if (N == true)
	{
		cout << "INPUT BASE, NUMBER AND RESULT BASE\nCURRENTLY SUPPORTED BASES ARE 8, 10 AND 16\n";
	}
	cout << "BASE: ";
	cin >> base;
	cout << "NUMBER: ";
	switch (base)
	{
	case 2:
		cin >> dec >> a;
		a = from_base_2(a, 0, 0);
		break;
	case 8:
		cin >> oct >> a;
		break;
	case 16:
		cin >> hex >> a;
		break;
	default:
		cin >> dec >> a;
		break;
	}
	cout << "RESULT BASE: ";
	cin >> base_result;
	switch (base_result)
	{
	case 2:
		cout << "\nCONVERTED NUMBER: ";
		to_base_2(a);
		cout << endl;
		return 0;
	case 8:
		cout << "\nCONVERTED NUMBER: " << oct << a << endl;
		return 0;
	case 10:
		cout << "\nCONVERTED NUMBER: " << dec << a << endl;
		return 0;
	case 16:
		cout << "\nCONVERTED NUMBER: " << hex << a << endl;
		return 0;
	default:
		cout << "INPUT PROPER BASE, NUMBER AND RESULT BASE\n";
		return in_base(false);
	}
}

short int dialog(bool N)
{
	short int choice;

	system("color 2");
	if (N == true)
	{
		cout << "PRESS 1 IF YOU WANT TO CALCULATE, 2 IF YOU WANT CONVERT FROM BASE TO BASE\n> ";
	}
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << calculus(true) << endl;
		return 0;
	case 2:
		in_base(true);
		return 0;
	default:
		cout << "WRONG CHOICE\n> ";
		return dialog(false);
	}
}

int main()
{
	dialog(true);
	system("pause");
    return 0;
}

