// pr1-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class Parent
{
protected:
	long* x = new long;
	long i = 1, j = 0;
public:
	Parent()
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
		mas[j] = i;
		i++;
		j++;
	}
};

class Child : public Parent
{
private:
	long k = 101;
public:
	Child()
	{
		std::cout << "Construct Child_class" << std::endl;
	}

	virtual ~Child()
	{
		std::cout << "Destruct Child_class" << std::endl;
	}

	virtual void init(long mas[])
	{
		mas[j] = k;
		k++;
		j++;
	}
};

int main()
{
	Parent* a = new Parent;
	Parent* b = new Parent;
	Child* c = new Child;
	Child* d = new Child;

	long* mas = new long[4];
	a->init(&mas[0]);
	b->init(&mas[1]);
	c->init(&mas[2]);
	d->init(&mas[3]);

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