// pr11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
using namespace std;

int main()
{
	const short int N = 100, R1 = 0, R2 = 50;
	short int i, j, a[N];
	srand(time(0));

	cout << "HERE IS SOME ARRAY:\n";
	for (i = 0; i < N; i++)
	{
		a[i] = R1 + rand() % R2;
		cout << a[i] << " ";
	};
	cout << "\nAND HERE IT'S SHIFTED TO LEFT 3 TIMES:\n";
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
	cout << "\nVOI LA!\n";
    return 0;
}