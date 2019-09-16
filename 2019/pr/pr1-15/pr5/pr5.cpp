// pr5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	ifstream ifile; //создает объект-поток
	ifile.open("myfile.txt");//открывает файл
	string s0, s1;
	for (; ; )
	{
		ifile >> s0;
		if (ifile.eof()) break;
		s1 += s0 + "\n";
	} cout << s1;
	return 0;
}