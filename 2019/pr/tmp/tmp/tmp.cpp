// tmp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

struct input_data
{
	std::map<unsigned long long, std::string> data;
	std::string type;
};

template <class OBJ>
std::map<unsigned long long, OBJ> data;

int main()
{
	data<std::string>;
	data<int>;
	return 0;
}