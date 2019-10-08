// pr1-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class BASE
{
protected:
	int* mas;

public:
	BASE() : mas(new int[10])
	{
		std::cout << "Construct Parent_class" << std::endl;
	}

	virtual ~BASE()
	{
		std::cout << "Destruct Parent_class" << std::endl;
	}

	void init()
	{
		mas[0] = 100;
		for (int i = 1; i < 10; i++)
		{
			mas[i] = mas[i - 1] + 3;
		}
	}

	virtual void preprint()
	{
		for (int i = 0; i < 10; i++)
		{
			if (mas[i] % 2 == 0)
			{
				std::cout << mas[i] << std::endl;
			}
		}
	}

	void del()
	{
		delete[] mas;
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

	void preprint() override
	{
		for (int i = 0; i < 10; i++)
		{
			if (mas[i] % 2 != 0)
			{
				std::cout << mas[i] << std::endl;
			}
		}
	}
};

void create(BASE** v)
{
	v[0] = new BASE;
	v[1] = new Child_class;
}

void init(BASE** v)
{
	v[0]->init();
	v[1]->init();
}

void print(BASE** v)
{
	for (int i = 0; i < 2; i++)
	{
		v[i]->preprint();
		std::cout << std::endl;
	}
}

void del(BASE** v)
{
	v[0]->del();
	v[1]->del();

	delete v[0];
	delete v[1];

}

int main()
{
	BASE* arr[2];

	create(arr);
	init(arr);
	print(arr);
	del(arr);

	return 0;
}