// pr28.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

class Kryuchkov
{
public:
	Kryuchkov() {}
	virtual ~Kryuchkov() {}

	virtual void print() = 0;
};

class Kryuchkov_child_1 : public Kryuchkov
{
private:
	std::string s1;

public:
	Kryuchkov_child_1() {}
	Kryuchkov_child_1(std::string S) : s1(S) {}
	~Kryuchkov_child_1() {}

	void print() override
	{
		std::cout << s1 << std::endl;
	}
};

class Kryuchkov_child_2 : public Kryuchkov
{
private:
	std::string s2;

public:
	Kryuchkov_child_2() {}
	Kryuchkov_child_2(std::string S) : s2(S) {}
	~Kryuchkov_child_2() {}

	void print() override
	{
		std::cout << s2 << std::endl;
	}
};

int main()
{
	Kryuchkov* a = new Kryuchkov_child_1("TEST 1");
	Kryuchkov* b = new Kryuchkov_child_2("TEST 2");
	std::vector<Kryuchkov*> v;

	v.push_back(a);
	v.push_back(b);

	for (int i = 0; i < v.size(); i++)
	{
		v[i]->print();
	}

	for (int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

	return 0;
}