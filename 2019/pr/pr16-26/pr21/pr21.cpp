// pr21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Base {
protected:
	string s;
public:
	Base() { s = "Base"; }
	virtual ~Base() { }
	string get() { return s; }
};

class Child1 : public Base {
public:
	Child1() { s = "child1"; }
};

class Child2 : public Base {
public:
	Child2() { s = "child2"; }
};

int main()
{
	vector <Base*> v;
	for (int i = 0; i < 10; i++) {
		if (!(i % 3))
			v.push_back(new Base);
		else
			if (!((i % 3) - 1))
			{
				v.push_back(new Child1);
			}
			else
			{
				v.push_back(new Child2);
			}
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i]->get() << endl;
	}

	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}
	return 0;

}