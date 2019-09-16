// pr15.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <string>
#include <ctime>

void animation()
{
	std::ifstream infile;
	infile.open("animation.txt");
	
	const short int R1 = 1, R2 = 15;
	short int clr = 0;
	char line;

	if (infile.is_open())
	{
		std::cout << "FINAL PROJECT!\n";
		while (infile.get(line))
		{
			if (line == '.')
			{
				Sleep(100);
				std::system("cls");
				srand(time(0));
				clr = R1 + rand() % R2;
				switch (clr)
				{
				case 1:
					std::system("color 1");
					break;
				case 2:
					std::system("color 2");
					break;
				case 3:
					std::system("color 3");
					break;
				case 4:
					std::system("color 4");
					break;
				case 5:
					std::system("color 5");
					break;
				case 6:
					std::system("color 6");
					break;
				case 7:
					std::system("color 7");
					break;
				case 8:
					std::system("color 8");
					break;
				case 9:
					std::system("color 9");
					break;
				case 10:
					std::system("color A");
					break;
				case 11:
					std::system("color B");
					break;
				case 12:
					std::system("color C");
					break;
				case 13:
					std::system("color D");
					break;
				case 14:
					std::system("color E");
					break;
				case 15:
					std::system("color F");
					break;
				default:
					std::system("color 0");
					break;
				};
				std::cout << "FINAL PROJECT!\n";
				continue;
			} 
			else if (line == ',')
			{
				std::cout << std::endl;
				continue;
			}
			else std::cout << line;	 
		};
	}
	else
	{
		std::cout << "CAN'T READ\n";
	};
	infile.close();
}

int main()
{
	animation();
	return 0;
}