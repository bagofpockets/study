// pr13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int main()
{
	int num;
	cout << "ENTER AN INTEGER.\n";
	cin >> num;
	if (num % 2 == 0)
		cout << "IT'S EVEN!";
	else
		cout << "IT'S ODD!";
	return 0;
}