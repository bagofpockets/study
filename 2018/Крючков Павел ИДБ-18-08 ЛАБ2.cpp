// Array.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
using namespace std;


int main()
{
	const short int N = 100;
	short int i, j, duplicate, zeros_count = 0, zero_1, zero_2, max_uneven = -1, a[N];
	srand(time(0));

	cout << "FIRST INITIAL ARRAY:\n"; //Первое задание
	for (i = 0; i < N; i++)
	{
		a[i] = 0 + rand() % 50; //Заполняем и выводим начальный массив
		cout << a[i] << " ";
	};
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
		if (a[i] != -1) cout << a[i] << " ";
	};

	cout << "\n\nSECOND INITIAL ARRAY:\n"; //Второе задание
	for (i = 0; i < N; i++)
	{
		a[i] = 0 + rand() % 50; //Заполняем и выводим начальный массив
		cout << a[i] << " ";
		if (a[i] == 0)
		{
			zeros_count++;
			(zeros_count == 1) ? zero_1 = i : zero_2 = i;
		};
	};
	cout << "\nSUM BETWEEN ZEROS:\n";
	if (zeros_count != 2)
	{
		cout << "0\n";
	}
	else
	{
		for (i = zero_1 + 1; i < zero_2; i++)
		{
			a[zero_1] += a[i];
		};
		cout << a[zero_1] << "\n";
	};

	cout << "\nTHIRD INITIAL ARRAY:\n"; //Третье задание
	for (i = 0; i < N; i++)
	{
		a[i] = 0 + rand() % 50; //Заполняем и выводим начальный массив
		cout << a[i] << " ";
	};
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
		cout << a[i] << " ";
	};

	cout << "\n\nFOURTH INITIAL ARRAY:\n"; //Четвёртое задание
	for (i = 0; i < N; i++)
	{
		cout << a[i] << " ";  //Выводим массив из 3 задания
		if (((a[i] % 2) == 1) && (a[i] >= max_uneven)) max_uneven = i; //Если есть несколько одинаковых максимумов, то выбирается самый правый
	};
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
		cout << a[i] << " ";
	};

	cout << "\n\nFIFTH INITIAL ARRAY:\n"; //Пятое задание
	for (i = 0; i < N; i++)
	{
		cout << a[i] << " ";  //Выводим массив из 4 задания
	};

	short int *dynamic_a = new short int[N];
	j = 0;

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
		cout << dynamic_a[i] << " ";
	};
	delete[] dynamic_a;
	cout << "\n";
	system("pause");
	return 0;
};
