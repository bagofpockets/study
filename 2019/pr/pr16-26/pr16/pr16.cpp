// pr16.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;

class Base {
public:
	Base() {
		cout << "Construct Base" << endl;
	}
	~Base() {
		cout << "Destruct Base" << endl;
	}
};

class Child :public Base {
public:
	Child() {
		cout << "Construct Child" << endl;
	}
	~Child() {
		cout << "Destruct Child" << endl;
	}
};

int main()
{
	vector <Base*>v(2);
	v[0] = new Base();
	v[1] = new Child();

	for (int i = 0; i < v.size(); i++) {
		delete v[i]; v[i] = 0;
	}
	return 0;
}