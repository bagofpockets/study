// pr1-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class Parent_class
{
public:
	Parent_class()
	{
		std::cout << "Construct Parent_class" << std::endl;
	}

	virtual ~Parent_class()
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

	virtual ~Child_class()
	{
		std::cout << "Destruct Child_class" << std::endl;
	}
};

void del(std::vector<Parent_class*> v)
{
	for (int i = 0; i < v.size(); i++) {
		delete v[i];
	}

	return;
};

int main()
{
	std::vector<Parent_class*> objs(4);
	objs[0] = new Parent_class();
	objs[1] = new Parent_class();
	objs[2] = new Child_class();
	objs[3] = new Child_class();

	del(objs);

	return 0;
}