// pr2-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

class Shape
{
public:
	Shape() {}
	virtual ~Shape() {}
	virtual int get_id() { return 0; }
	virtual int get_x1() { return 0; }
	virtual int get_x2() { return 0; }
	virtual int get_y1() { return 0; }
	virtual int get_y2() { return 0; }
	virtual int get_r() { return 0; }
	virtual int get_side() { return 0; }
};

class Circle : public Shape
{
private:
	int* x1;
	int* y1;
	int* r;

public:
	Circle(int x1, int y1, int r) : x1(new int(x1)), y1(new int(y1)), r(new int(r)) {}
	~Circle() {}

	int get_id() override
	{
		return 0;
	}

	int get_x1() override
	{
		return *x1;
	}

	int get_y1() override
	{
		return *y1;
	}

	int get_r() override
	{
		return *r;
	}
};

class Square : public Shape
{
private:
	int* side;

public:
	Square(int side) : side(new int(side)) {}
	~Square() {}

	int get_id() override
	{
		return 1;
	}

	int get_side() override
	{
		return *side;
	}
};

class Line : public Shape
{
private:
	int* x1;
	int* x2;
	int* y1;
	int* y2;

public:
	Line(int x1, int x2, int y1, int y2) : x1(new int(x1)), x2(new int(x2)), y1(new int(y1)), y2(new int(y2)) {}
	~Line() {}

	int get_id() override
	{
		return 2;
	}

	int get_x1() override
	{
		return *x1;
	}

	int get_x2() override
	{
		return *x2;
	}

	int get_y1() override
	{
		return *y1;
	}

	int get_y2() override
	{
		return *y2;
	}
};

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");

	const short int R1(-50), R2(100), N(4);
	std::vector<Shape*> v;
	std::ofstream* file = new std::ofstream;
	file->open("идб.txt", std::fstream::out);

	for (int i = 0; i < N; i++)
	{
		switch (0 + rand() % 3)
		{
		case 0:
			v.push_back(new Circle(R1 + rand() % R2, R1 + rand() % R2, 1 + rand() % R2));
			break;
		case 1:
			v.push_back(new Square(1 + rand() % R2));
			break;
		case 2:
			v.push_back(new Line(R1 + rand() % R2, R1 + rand() % R2, R1 + rand() % R2, R1 + rand() % R2));
			break;
		default:
			break;
		}
	}


	if (file->is_open())
	{
		for (unsigned int i = 0; i < v.size(); i++)
		{
			switch (v[i]->get_id())
			{
			case 0:
				*file << "Circle " << v[i]->get_x1() << ' ' << v[i]->get_y1() << ' ' << v[i]->get_r() << '\n';
				break;
			case 1:
				*file << "Square " << v[i]->get_side() << '\n';
				break;
			case 2:
				*file << "Line " << v[i]->get_x1() << ' ' << v[i]->get_y1() << ' ' << v[i]->get_x2() << ' ' << v[i]->get_y2() << '\n';
				break;
			default:
				break;
			}
		}
		std::cout << "Done" << std::endl;
	}
	else
	{
		std::cout << "Can't open file" << std::endl;
	}

	for (unsigned int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

	file->close();
	delete file;
	return 0;
}