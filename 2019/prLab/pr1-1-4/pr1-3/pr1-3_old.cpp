// pr1-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

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

	void init()
	{
		mas[0] = 100;
		for (int i = 1; i < 10; i++)
		{
			mas[i] = mas[i - 1] + 3;
		}
	}

	virtual void print(BASE* a)
	{
		for (int i = 0; i < 10; i++)
		{
			if (mas[i] % 2 == 0)
			{
				std::cout << mas[i] << std::endl;
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

	void print(BASE* a) override
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

void create(BASE* v)
{
	BASE* a = new BASE;
	Child_class* b = new Child_class;

	v[0] = *a;
	v[1] = *b;
}

void del(BASE* mas)
{
	//for (int i = 0; i < 2; i++)
	//{
	delete[] mas;// [i] ;
	//	mas[i] = 0;
	//}
}

int main()
{
	BASE* arr = new BASE;
	create(arr);
	arr->init();
	arr->print(arr);
	std::cout << std::endl;

	del(arr);

	return 0;
}