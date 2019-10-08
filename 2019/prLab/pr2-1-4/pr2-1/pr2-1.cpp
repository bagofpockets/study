// pr2-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Parts_db
{
private:
	std::string* type;
	unsigned int* quantity;

public:

	Parts_db(std::string type, unsigned int quantity) : type(new std::string(type)), quantity(new unsigned int(quantity))
	{

	}

	~Parts_db()
	{
		delete type;
		delete quantity;
	}

	void add_to_db(unsigned int add_quantity)
	{
		*quantity += add_quantity;
	}

	void print()
	{
		std::cout << *type << " " << *quantity << std::endl;
	}
};

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");

	const unsigned short int R1(0), R2(1000);
	std::vector<Parts_db*> v;

	v.push_back(new Parts_db("втулка", R1 + rand() % R2));
	v.push_back(new Parts_db("корпус", R1 + rand() % R2));
	v.push_back(new Parts_db("кронштейн", R1 + rand() % R2));
	v.push_back(new Parts_db("манжета", R1 + rand() % R2));
	v.push_back(new Parts_db("фланец", R1 + rand() % R2));
	v.push_back(new Parts_db("панель", R1 + rand() % R2));
	v.push_back(new Parts_db("шток", R1 + rand() % R2));
	v.push_back(new Parts_db("винт", R1 + rand() % R2));
	v.push_back(new Parts_db("гайка", R1 + rand() % R2));

	std::cout << "Before adding:" << std::endl;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		v[i]->print();
	}
	
	v[R1 + rand() % v.size()]->add_to_db(R1 + rand() % R2);
	v[R1 + rand() % v.size()]->add_to_db(R1 + rand() % R2);

	std::cout << "\nAfter adding:" << std::endl;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		v[i]->print();
		delete v[i];
		v[i] = 0;
	}

	return 0;
}