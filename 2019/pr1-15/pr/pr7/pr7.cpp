// pr7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
	int a;
	vector <int> v;
	for (; ; )
	{
		ifile >> a;
		if (ifile.eof()) break;
		v.push_back(a);//добавляем в вектор
	}

	sort(v.begin(), v.end());
	//sort(v.rbegin(),v.rend()); //раскоммент

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	return 0;
}