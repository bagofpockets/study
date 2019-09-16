// pr25.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <ctime>

class Shape
{
public:
	Shape()
	{
		
	}
	
	~Shape()
	{

	}

	virtual double Perimeter()
	{
		return 0;
	}

	virtual double get_r()
	{
		return 0;
	}
};

class Square : public Shape
{
private:
	double r, per = 0;

public:
	Square(double r) : Shape()
	{
		this->r = r;
	}

	~Square()
	{

	}

	double Perimeter() override
	{

		per = r * 4;
		return per;
	}

	double get_r() override
	{
		return r;
	}
};

class Circle : public Shape
{
private:
	double r, per = 0;
	const double pi = 3.14;

public:
	Circle(double r) : Shape()
	{
		this->r = r;
	}

	~Circle()
	{

	}

	double Perimeter() override
	{
		per = r * 2 * pi;
		return per;
	}

	double get_r() override
	{
		return r;
	}
};

int main()
{
	const short int R1 = 0, R2 = 100, N = 4;
	srand(time(0));
	std::vector<Shape*> v;
	Shape* buffer;

	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
		{
			buffer = new Circle(R1 + rand() % R2);
		}
		else
		{
			buffer = new Square(R1 + rand() % R2);
		}
		
		v.push_back(buffer);
	}

	for (int i = 0; i < N; i++)
	{	
		std::cout << "Perimeter" << i << " = " << v[i]->Perimeter() << std::endl;  //"\n  With a radius/side of " << v[i]->get_r() << std::endl;
	}

	delete buffer;
	return 0;
}