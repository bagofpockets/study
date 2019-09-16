// pr19.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

	// операции доступа извне

	void set(int a) { *i = a; }
	void set(double a) { d = a; }

	double getd() { return d; }
};

int main()
{
	Base b;
	const Base bc;
	cout << b.get() << endl;
	cout << bc.get() << endl;

	b.set(12);
	// bc.set(8.78);  // ошибка
	b.set(8.78);
	cout << b.get() << endl;
	cout << b.getd() << endl;
	return 0;
}