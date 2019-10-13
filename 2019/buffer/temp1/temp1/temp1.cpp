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

class a
{
protected:
	unsigned long long* associated_ids;

public:
	a() : associated_ids(new unsigned long long[NULL]) {}
	a(unsigned long long N) : associated_ids(new unsigned long long[N]) {}
	virtual ~a()
	{
		delete[] associated_ids;
	}

	void set(unsigned long long POS, unsigned long long VAL)
	{
		associated_ids[POS] = VAL;
	}
};

class b : public a
{
public:
	b() {}
	b(unsigned long long N)
	{
		associated_ids = new unsigned long long[N];
	}
	~b() {}
};

int main()
{
	/*
	std::string buffer("\n('',(0.,-1.,0.))");
	std::string addbuffer;
	size_t first_buffer;
	size_t second_buffer;
	unsigned long long N_buffer(0);

	buffer.erase(0, 2); // удаляет
	buffer.pop_back();  // внешние скобки

	/*buffer->erase(0, buffer->find_first_of('('));

	for (size_t j = buffer->find_first_of('#'); j <= buffer->find_last_of(')'); j++)
	{
		if (buffer->at(j) == '#') ++*N_buffer;
	}

	*addbuffer = buffer->substr(buffer->find_first_of('('), buffer->find_first_of(')') - buffer->find_first_of('('));

	for (unsigned long long i = 0; i < *N_buffer; i++)
	{
		addbuffer->erase(0, addbuffer->find_first_of('#'));
		//std::cout << std::stoull(addbuffer->substr(1, addbuffer->find_first_of(','))) << '\n';
	}

	buffer->erase(0, buffer->find_first_of(')'));

	buffer->erase(0, buffer->find_first_of('#'));
	*addbuffer = buffer->substr(1, buffer->find_first_of(',') - buffer->find_first_of('#') - 1);
	//std::cout << *addbuffer << std::endl;

	buffer->erase(0, buffer->find_first_of('#'));
	buffer->erase(0, buffer->find_first_of(',') + 1);

	first_buffer = buffer.find_first_of('\'');
	second_buffer = buffer.find_last_of('\'') - buffer.find_first_of('\'');

	//buffer = buffer.substr(first_buffer, second_buffer + 1);

	buffer.erase(0, buffer.find_first_of('('));

	first_buffer = buffer.find_first_of('(') + 1;
	second_buffer = buffer.find_first_of(')') - first_buffer;
	buffer = buffer.substr(first_buffer, second_buffer);

	second_buffer = buffer.find_first_of(',');

	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');

	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	std::cout << std::stod(buffer.substr(0, second_buffer));

	std::cout << buffer << std::endl;
	*/

	a t1(1);

	b t2(2);

	t1.set(0, 1);

	t2.set(0, 3);

	t2.set(1, 3);

	return 0;
}