// pr3-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class Class1
{
public:
	Class1() {}
	~Class1() {}
};

class Class2 : public Class1
{
public:
	Class2() {}
	~Class2() {}
};

class Db
{
private:
	std::vector<Class1*>* v;

public:
	Db() : v(new std::vector<Class1*>) {}
	~Db()
	{
		for (unsigned int i = 0; i < v->size(); i++)
		{
			delete v->at(i);
			v->at(i) = 0;
		}
		delete v;
	}

	void my_copy(Class1* a)
	{
		v->push_back(a);
	}
};

int main()
{
	Db* a = new Db;
	auto* b = new Class1;
	auto* c = new Class2;

	a->my_copy(b);
	a->my_copy(c);

	delete a;

	return 0;
}