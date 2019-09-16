// pr14.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
	int space, rows;
	cout << "WE ARE GONNA BUILD A PYRAMID! HOW MANY ROWS WILL IT HAVE?\n";
	cin >> rows;
	cout << "Fine.\n";
	for (int i = 1, k = 0; i <= rows; ++i, k = 0)
	{
		for (space = 1; space <= rows - i; ++space)
		{
			cout << "  ";
		}
		while (k != 2 * i - 1)
		{
			cout << ". ";
			++k;
		}
		cout << endl;
	}
	return 0;
}