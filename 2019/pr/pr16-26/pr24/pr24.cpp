// pr24.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

template< class T>
class Base {
public:
	Base(T a) { p = a; }
	void print() { cout << p << endl; }
private:
	T p;
};

int main()
{
	// Base b // Ошибка:нужно указать тип шаблона
	Base <int> bi(22);  // ok
	Base <double> bd(22.84);  // ok     
	Base <string> bs("test");  // ok   
	bi.print();
	bd.print();
	bs.print();
	return 0;
}