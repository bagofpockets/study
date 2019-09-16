// pr20.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
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
	Base* b = new Base();
	cout << b->get() << endl;
	delete b; b = 0;
	b = new Child1();
	cout << b->get() << endl;
	delete b; b = 0;
	b = new Child2();
	cout << b->get() << endl;
	delete b; b = 0;
	return 0;

}