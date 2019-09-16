// pr9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

class Test
{
public:
	Test()
	{
		cout << "Construct" << endl;
	}
	~Test()
	{
		cout << "Construct" << endl;
	}
};

int main()
{
	vector <Test*>v(10);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = new Test();
	}

	for (int i = 0; i < v.size(); i++)
	{
		delete v[i]; v[i] = 0;
	}
	return 0;
}