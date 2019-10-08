// temp1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>

/*class Krychkov
{
private:
	float* f;

public:
	Krychkov() : f(new float[2]) { f[0] = 1.0; f[1] = 2.0; }
	Krychkov(bool a) : f(new float[2]) { f[0] = 3.0; f[1] = 4.0; }
	virtual ~Krychkov() { delete[] f; }
};

class Pavel : public Krychkov
{
public:
	Pavel() {}
	~Pavel() {}
};

int main()
{
	std::vector<Krychkov*> v;
	Krychkov* a = new Krychkov;
	Krychkov* b = new Krychkov(true);
	Krychkov* c = new Pavel;

	v.push_back(a);
	v.push_back(b);
	v.push_back(c);

	for (int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

    return 0;
}*/

int main()
{

	std::string* buffer(new std::string("\n('',(#697,#709,#721,#733))"));
	unsigned long long* N_buffer(new unsigned long long(0));

	buffer->erase(0, 2); // удаляет
	buffer->pop_back();  // внешние скобки

	for (size_t j = buffer->find_first_of('#'); j <= buffer->find_last_of('#'); j++)
	{
		if (buffer->at(j) == '#')++* N_buffer;
	}

	buffer->erase(buffer->find_first_of('\''), buffer->find_first_of('(') - buffer->find_first_of('\'') + 1);
	buffer->pop_back();

	for (int i = 0; i < 4; i++)
	{
		buffer->erase(0, 1);
		std::cout << std::stoull(buffer->substr(0, buffer->find_first_of(','))) << '\n'<< *N_buffer << std::endl;
		buffer->erase(0, buffer->find_first_of('#'));
	}
	delete buffer;
	delete N_buffer;

	return 0;
}