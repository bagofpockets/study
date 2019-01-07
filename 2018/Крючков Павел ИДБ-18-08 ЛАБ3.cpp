// Крючков Павел ИДБ-18-08 ЛАБ3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

namespace
{
	ofstream outfile("log.txt");
	ifstream infile("log.txt");
	const short int R1 = 0, R2 = 50, N = 100;
	short int i, j, a[N];
}

void read_log()
{
	char line;

	if (infile.is_open())
	{
		while (infile.get(line))
		{
			cout << line;
		};
	}
	else
	{
		cout << "CAN'T READ LOG\n";
	};
}

void generator()
{
	srand(time(0));

	for (i = 0; i < N; i++)
	{
		a[i] = R1 + rand() % R2; //Заполняем и выводим начальный массив
		outfile << a[i] << " ";
		cout << a[i] << " ";
	};
}

void first()
{
	short int duplicate;

	outfile << "\nFIRST INITIAL ARRAY:\n";
	cout << "\nFIRST INITIAL ARRAY:\n"; //Первое задание
	generator();
	outfile << "\nWITHOUT DUPLICATES:\n";
	cout << "\nWITHOUT DUPLICATES:\n";
	for (i = 0; i < N; i++)
	{
		duplicate = a[i];
		for (j = N - 1; j > i; j--)
		{
			if (a[j] == duplicate)
			{
				a[i] = -1;
				a[j] = -1;
			};
		};
		if (a[i] != -1)
		{
			outfile << a[i] << " ";
			cout << a[i] << " ";
		};
	};
}

void second()
{
	short int zeros_count = 0, zero_1, zero_2;

	outfile << "\nSECOND INITIAL ARRAY:\n";
	cout << "\nSECOND INITIAL ARRAY:\n"; //Второе задание
	generator();
	for (i = 0; i < N; i++)
	{
		if (a[i] == 0)
		{
			zeros_count++;
			(zeros_count == 1) ? zero_1 = i : zero_2 = i;
		};
	};
	outfile << "\nSUM BETWEEN ZEROS:\n";
	cout << "\nSUM BETWEEN ZEROS:\n";
	if (zeros_count != 2)
	{
		outfile << "0";
		cout << "0";
	}
	else
	{
		for (i = zero_1 + 1; i < zero_2; i++)
		{
			a[zero_1] += a[i];
		};
		outfile << a[zero_1];
		cout << a[zero_1];
	};
}

void third()
{
	outfile << "\nTHIRD INITIAL ARRAY:\n";
	cout << "\nTHIRD INITIAL ARRAY:\n"; //Третье задание
	generator();
	outfile << "\nSHIFTED TO LEFT 3 TIMES:\n";
	cout << "\nSHIFTED TO LEFT 3 TIMES:\n";
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < N - 1; j++)
		{
			a[j] = a[j] ^ a[j + 1];
			a[j + 1] = a[j] ^ a[j + 1];
			a[j] = a[j] ^ a[j + 1];
		};
	};
	for (i = 0; i < N; i++)
	{
		outfile << a[i] << " ";
		cout << a[i] << " ";
	};
}

void fourth()
{
	short int max_uneven = -1;

	outfile << "\nFOURTH INITIAL ARRAY:\n";
	cout << "\nFOURTH INITIAL ARRAY:\n"; //Четвёртое задание
	generator();
	for (i = 0; i < N; i++)
	{
		if (((a[i] % 2) == 1) && (a[i] >= max_uneven)) max_uneven = i; //Если есть несколько одинаковых максимумов, то выбирается самый правый
	};
	outfile << "\nSHIFTED TO LEFT 3 TIMES AFTER MAX UNEVEN ELEMENT:\n";
	cout << "\nSHIFTED TO LEFT 3 TIMES AFTER MAX UNEVEN ELEMENT:\n";
	for (i = 0; i < 3; i++)
	{
		for (j = max_uneven + 1; j < N - 1; j++) //Если все числа чётные, то сместятся все
		{
			a[j] = a[j] ^ a[j + 1];
			a[j + 1] = a[j] ^ a[j + 1];
			a[j] = a[j] ^ a[j + 1];
		};
	};
	for (i = 0; i < N; i++)
	{
		outfile << a[i] << " ";
		cout << a[i] << " ";
	};
}

void fifth()
{
	outfile << "\nFIFTH INITIAL ARRAY:\n";
	cout << "\nFIFTH INITIAL ARRAY:\n"; //Пятое задание
	generator();

	short int *dynamic_a = new short int[N];
	j = 0;

	outfile << "\nDYNAMIC ARRAY WITHOUT ZEROS:\n";
	cout << "\nDYNAMIC ARRAY WITHOUT ZEROS:\n";
	for (int i = 0; i < N; i++)
	{
		if (a[i] == 0)
		{
			j++;
			continue;
		}
		else
		{
			dynamic_a[i - j] = a[i];
		};
	};
	for (i = 0; i < N - j; i++)
	{
		outfile << dynamic_a[i] << " ";
		cout << dynamic_a[i] << " ";
	};
	delete[] dynamic_a;
}

void dialog(bool error)
{
	string choice;
	infile.close();
	outfile.close();
	infile.open("log.txt", ios::in | ios::app);
	outfile.open("log.txt", ios::out | ios::app);
	if (error == false)
	{
		cout << "TYPE:\n   1     FOR FIRST TASK\n   2     FOR SECOND TASK\n   3     FOR THIRD TASK\n   4     FOR FOURTH TASK\n   5     FOR FIFTH TASK\n   HELP  FOR THIS MESSAGE\n   R     TO READ LOG\n   0     TO EXIT\n";
	}
	cout << "\n> ";
	cin >> choice;
	outfile << "\n> " << choice << "\n";
	if (choice.length() == 1)
	{
		if (choice[0] == '0')
		{
			outfile << "\n";
			cout << "\n";
			return;
		}
		if (choice[0] == '1')
		{
			first();
			outfile << "\n";
			cout << "\n";
			return dialog(true);
		}
		if (choice[0] == '2')
		{
			second();
			outfile << "\n";
			cout << "\n";
			return dialog(true);
		}
		if (choice[0] == '3')
		{
			third();
			outfile << "\n";
			cout << "\n";
			return dialog(true);
		}
		if (choice[0] == '4')
		{
			fourth();
			outfile << "\n";
			cout << "\n";
			return dialog(true);
		}
		if (choice[0] == '5')
		{
			fifth();
			outfile << "\n";
			cout << "\n";
			return dialog(true);
		}
		if (choice[0] == 'R')
		{
			outfile << "\n";
			cout << "\n";
			read_log();
			return dialog(true);
		}
		else
		{
			outfile << "\nERROR, TRY AGAIN FELLOW HUMAN\n";
			cout << "\nERROR, TRY AGAIN FELLOW HUMAN\n";
			return dialog(true);
		};
	}
	if ((choice.length() == 4) && (choice == "HELP"))
	{
		outfile << "\n";
		cout << "\n";
		return dialog(false);
	}
	else
	{
		outfile << "\nERROR, TRY AGAIN FELLOW HUMAN\n";
		cout << "\nERROR, TRY AGAIN FELLOW HUMAN\n";
		return dialog(true);
	};
}

int main()
{
	dialog(false);
	return 0;
};
