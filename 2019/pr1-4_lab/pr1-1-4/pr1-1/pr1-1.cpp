// pr1-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <vector>

class Parent_class
{
protected:
	int a = 0, b = 0;
public:
	Parent_class()
	{
		std::cout << "Construct Parent_class" << std::endl;
	}

	Parent_class(int input)
	{
		a = input;
		std::cout << "Construct Parent_class" << std::endl;
	}

	~Parent_class()
	{
		std::cout << "Destruct Parent_class" << std::endl;
	}
};

class Child_class : public Parent_class
{
public:
	Child_class()
	{
		std::cout << "Construct Child_class" << std::endl;
	}

	Child_class(int input)
	{
		std::cout << "Construct Child_class" << std::endl;
		b = input;
	}

	~Child_class()
	{
		std::cout << "Destruct Child_class" << std::endl;
	}
};

void del()
{

};

int main()
{
	const short int R1 = 0, R2 = 100;
	srand(time(0));

	std::vector<int> numbers;
	Parent_class a(R1 + rand() % R2);
	Parent_class b(R1 + rand() % R2);
	Child_class c(R1 + rand() % R2);
	Child_class d(R1 + rand() % R2);

	numbers.push_back(a, b, c, d);

	return 0;
}