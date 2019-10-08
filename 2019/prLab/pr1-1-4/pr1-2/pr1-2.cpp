// pr1-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class T
{
public:
	T()
	{
		std::cout << "Construct T" << std::endl;
	}

	T(const char* c)
	{
		std::cout << "Construct T w/ char" << std::endl;
	}

	virtual ~T()
	{
		std::cout << "Destruct T" << std::endl;
	}
};

class Tc : public T
{
public:
	Tc()
	{
		std::cout << "Construct Tc" << std::endl;
	}

	Tc(const char* c)
	{
		std::cout << "Construct Tc w/ char" << std::endl;
	}

	~Tc()
	{
		std::cout << "Destruct Tc" << std::endl;
	}
};

int main()
{
	char cha = '_';
	const char* ch = &cha;

	T* a = new T(ch);
	T* b = new T(ch);
	T* c = new Tc(ch);
	T* d = new Tc(ch);

	std::vector<T*> objs;
	objs.push_back(a);
	objs.push_back(b);
	objs.push_back(c);
	objs.push_back(d);

	for (int i = 0; i < objs.size(); i++)
	{
		delete objs[i];
		objs[i] = 0;
	}

	return 0;
}