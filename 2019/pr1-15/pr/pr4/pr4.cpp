// pr4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	ofstream of; //создает объект-поток
	of.open("myfile.txt");//создает фаил
	for (int i = 0; i < 10; i++)
	{
		of << i << endl;
	}
	//откройте фаил и посмотрите внутрь
	return 0;
}