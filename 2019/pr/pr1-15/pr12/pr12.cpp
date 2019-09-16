// pr12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void TheMagic8Ball()
{
	const short int R1 = 0, R2 = 3;
	string q, answers[R2 + 1] = { "YES", "NO", "MAYBE", "ASK AGAIN" };
	srand(time(0));
	cout << "WHAT'S YOUR QUESTION, FELLOW HUMAN?\n";
	cin >> q;
	cout << endl << answers[R1 + rand() % R2] << endl;
}

int main()
{
	TheMagic8Ball();
	return 0;
}