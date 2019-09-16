// pr18.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<fstream>
#include<string>
#include<vector> 
#include<set>  
#include<map>  
#include<algorithm>
#include<cmath>
using namespace std;

class Base {
	int* i;
	double d;
public:
	Base() :i(new int), d(22.33) { *i = 0; }
	virtual ~Base() { delete i; i = 0; }

	int get() { return *i; }
	double  get()const { return d; }
};

int main()
{
	Base b;
	const Base bc;
	cout << b.get() << endl;
	cout << bc.get() << endl;

	return 0;
}