// pr1-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

class T
{
private:
	const char* c;
public:
	T()
	{
		std::cout << "Construct T" << std::endl;
	}

	T(const char* c)
	{
		this->c = c;
		std::cout << "Construct T w/ char" << std::endl;
	}

	virtual ~T()
	{
		std::cout << "Destruct T" << std::endl;
		delete c;
	}
};

class Tc : public T
{
private:
	const char* c;
public:
	Tc()
	{
		std::cout << "Construct Tc" << std::endl;
	}

	Tc(const char* c)
	{
		this->c = c;
		std::cout << "Construct Tc w/ char" << std::endl;
	}

	virtual ~Tc()
	{
		std::cout << "Destruct Tc" << std::endl;
		delete c;
	}
};

int main()
{
	char cha = ' ';
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
	return 0;
}