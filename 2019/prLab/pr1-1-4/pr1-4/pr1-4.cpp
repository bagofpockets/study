// pr1-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

namespace N { long N1(0), N2(0); }

class Parent
{
protected:
	long* x;

public:
	Parent() : x(new long(0))
	{
		std::cout << "Construct Parent_class" << std::endl;
	}

	virtual ~Parent()
	{
		std::cout << "Destruct Parent_class" << std::endl;
		delete x;
	}

	virtual void init(long mas[])
	{
		*x = 1 + N::N1;
		mas[N::N1 + N::N2] = *x;
		N::N1++;
	}
};

class Child : public Parent
{
public:
	Child()
	{
		std::cout << "Construct Child_class" << std::endl;
	}

	~Child()
	{
		std::cout << "Destruct Child_class" << std::endl;
	}

	void init(long mas[]) override
	{
		*x = 101 + N::N2;
		mas[N::N1 + N::N2] = *x;
		N::N2++;
	}
};

int main()
{
	Parent* a = new Parent;
	Parent* b = new Parent;
	Parent* c = new Child;
	Parent* d = new Child;

	long* mas = new long[4];
	a->init(mas);
	b->init(mas);
	c->init(mas);
	d->init(mas);

	for (int i = 0; i < 4; i++)
	{
		std::cout << mas[i] << std::endl;
	}

	delete[] mas;
	delete a;
	delete b;
	delete c;
	delete d;

	return 0;
}