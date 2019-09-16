// pr22.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Base {
	friend string func_get(Base* b);
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
string func_get(Base* b) {
	return b->s;
}

int main()
{
	vector <Base*> v;
	for (int i = 0; i < 10; i++) {
		bool ok = i % 3;
		if (!(i % 2))
			v.push_back(new Base);
		else { v.push_back(new  Child1); }
	}

	for (int i = 0; i < v.size(); i++) {
		cout << func_get(v[i]) << endl;
	}

	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}
	return 0;
}