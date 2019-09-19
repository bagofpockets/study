// pr27.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Kryuchkov
{
public:
	Kryuchkov() 
	{
		srand(time(0));
		std::cout << "UWAH!" << std::endl;
	}
	virtual ~Kryuchkov() {}
	virtual void born(std::string S) {}
};

class Kryuchkov_child_1 : public Kryuchkov
{
public:
	Kryuchkov_child_1() {}
	~Kryuchkov_child_1() {}

	void born(std::string S) override
	{
		std::cout << "\tHERE IS MY FIRST CHILD:\n" << S << std::endl;
	}
};

class Kryuchkov_child_2 : public Kryuchkov
{
private:
	const std::string S = "YEET";
	std::string buff;

public:
	Kryuchkov_child_2() {}
	~Kryuchkov_child_2() {}

	void born(std::string S) override
	{
		this->buff = S;
		const short int* R1 = new short int(0);
		int* R2 = new int(buff.size());

		for (std::string::iterator i = S.begin(); i != S.end(); ++i)
		{
			buff.insert(*R1 + rand() % *R2, this->S);
			*R2 = buff.size();
		};
		std::cout << "\tHERE IS MY SECOND CHILD:\n" << buff << std::endl;

		delete R1, R2;
	}
};

class Kryuchkov_child_3 : public Kryuchkov
{
public:
	Kryuchkov_child_3() {}
	~Kryuchkov_child_3() {}

	void born(std::string S) override
	{
		const short int* R1 = new short int(0);
		int* R2 = new int(S.size());

		S.replace(*R1 + rand() % *R2, S.size() - *R1 + rand() % *R2, S);
		std::cout << "\tHERE IS MY THIRD CHILD:\n" << S << "\n\tTHEY ARE QUITE DEFECTIVE" << std::endl;
		
		delete R1, R2;
	}
};

int main()
{
	std::vector<Kryuchkov*> v(3);

	Kryuchkov* a = new Kryuchkov_child_1;
	Kryuchkov* b = new Kryuchkov_child_2;
	Kryuchkov* c = new Kryuchkov_child_3;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	a->born("- Never gonna give you up");
	b->born("- Never gonna let you down");
	c->born("- Never gonna run around and desert you");

	for (int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

	return 0;
}