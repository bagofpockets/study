// pr8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

class Reader
{
	vector <int> m_v;
public:
	Reader() {}
	void read(const char* name);
	void print();
};

void Reader::read(const char* name)
{
	ifstream ifile;
	ifile.open(name);
	int a;
	for (; ; )
	{
		ifile >> a;
		if (ifile.eof()) break;
		m_v.push_back(a);
	}
}

void Reader::print()
{
	for (int i = 0; i < m_v.size(); i++)
	{
		cout << m_v[i] << endl;
	}
}

int main()
{
	Reader r;
	r.read("myfile.txt");
	r.print();

	getchar();

	return 0;
}