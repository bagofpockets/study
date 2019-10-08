// pr29.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class Kryuchkov
{
public:
	Kryuchkov() {}
	virtual ~Kryuchkov() {}
	virtual void print() = 0;
};

class Kryuchkov_child_1 : public Kryuchkov
{
private:
	double* d;

public:
	Kryuchkov_child_1(double d) : d(new double(d)) { std::cout << "Construct1 " << typeid(d).name() << std::endl; }
	~Kryuchkov_child_1()
	{
		std::cout << "Destruct1 " << typeid(*d).name() << std::endl;
		delete d;
	}

	void print() override
	{
		std::cout << *d << std::endl;
	}
};

class Kryuchkov_child_2 : public Kryuchkov
{
private:
	double* d;

public:
	Kryuchkov_child_2(double d) : d(new double(d)) { std::cout << "Construct2 " << typeid(d).name() << std::endl; }
	~Kryuchkov_child_2()
	{
		std::cout << "Destruct2 " << typeid(*d).name() << std::endl;
		delete d;
	}

	void print() override
	{
		std::cout << *d << std::endl;
	}
};

class Db
{
private:
	std::vector<Kryuchkov*>* v;

public:
	Db() : v(new std::vector<Kryuchkov*>) {}
	~Db()
	{
		for (unsigned int i = 0; i < v->size(); i++)
		{
			delete v->at(i);
			v->at(i) = 0;
		}
	}

	void add_to_Db(Kryuchkov* a)
	{
		v->insert(v->end(), a); 
	}

	void print()
	{
		for (unsigned int i = 0; i < v->size(); i++)
		{
			v->at(i)->print();
		}
	}
};

int main()
{
	Db* a = new Db;
	Kryuchkov* b = new Kryuchkov_child_1(1.11);
	Kryuchkov* c = new Kryuchkov_child_2(2.22);

	a->add_to_Db(b);
	a->add_to_Db(c);
	a->print();

	delete a;
	return 0;
}