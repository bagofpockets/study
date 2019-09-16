// pr10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

void func()
{
	ifstream ifile;
	ifile.open("myfile.txt");
	int a;
	set <int>st;
	for (; ; )
	{
		ifile >> a;
		if (ifile.eof()) break;
		st.insert(a);
	}
	set <int>::iterator it = st.begin();
	for (; it != st.end(); ++it)
	{
		cout << *it << endl;
	}
}

int main()
{
	func();
	return 0;
}