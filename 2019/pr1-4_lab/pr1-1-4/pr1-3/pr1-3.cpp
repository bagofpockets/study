// pr1-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class BASE
{
protected:
	int* mas = new int[10];
public:
	BASE()
	{
		std::cout << "Construct Parent_class" << std::endl;
	}

	virtual ~BASE()
	{
		std::cout << "Destruct Parent_class" << std::endl;
		delete[] mas;
	}

	virtual void init()
	{
		mas[0] = 100;
		for (int i = 1; i < 10; i++)
		{
			mas[i] = mas[i - 1] + 3;
		}
	}

	virtual void print(BASE* a[])
	{
		if (typeid(BASE) == typeid(a))
		{
			for (int i = 0; i < 10; i++)
			{
				if (mas[i] % 2 == 0)
				{
					std::cout << mas[i] << std::endl;
				}
			}
		}
	}
};

class Child_class : public BASE
{
public:
	Child_class()
	{
		std::cout << "Construct Child_class" << std::endl;
	}

	~Child_class()
	{
		std::cout << "Destruct Child_class" << std::endl;
	}

	void print(BASE* a[]) override
	{
		if (typeid(Child_class) == typeid(*a))
		{
			for (int i = 0; i < 10; i++)
			{
				if (mas[i] % 2 != 0)
				{
					std::cout << mas[i] << std::endl;
				}
			}
		}
	}
};

void create(BASE* a[])
{
	a[0] = new BASE();
	a[1] = new Child_class();

}

void del(BASE* mas)
{
	delete[] mas;
}

int main()
{
	BASE* a = new BASE[2];
	create(&a);
	a->init();
	a->print(&a);
	//del(a);

	return 0;
}