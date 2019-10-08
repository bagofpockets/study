// pr3-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>

class Cars
{
private:
	std::ifstream* file;
	struct Car { std::string type, model; };
	std::vector<Cars::Car*>* v;
	std::string* buff1;
	std::string* buff2;

public:
	Cars(std::string name) : file(new std::ifstream), v(new std::vector<Cars::Car*>)
	{
		file->open(name);
		if (file->is_open())
		{
			buff1 = new std::string;
			buff2 = new std::string;

			while (*file >> *buff1 >> *buff2)
			{
				Cars::Car* a = new Car;
				a->type = *buff1;
				a->model = *buff2;
				v->push_back(a);
			}

			delete buff1;
			delete buff2;
		}
		else std::cout << "Can't open file" << std::endl;
	}
	~Cars()
	{
		for (unsigned int i = 0; i < v->size(); i++)
		{
			std::cout << v->at(i)->type << " " << v->at(i)->model << std::endl;
			delete v->at(i);
			v->at(i) = 0;
		}
		file->close();
		delete file;
		delete v;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Cars* a = new Cars("машины.txt");
	delete a;
    return 0;
}