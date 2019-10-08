// prSem1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>

class Array
{
private:
	int** mas = new int* [10];

	long long fact(int N)
	{
		if (N < 0) return 0;
		if (N == 0) return 1;
		else return N * fact(N - 1);
	}



public:
	Array()
	{
		for (int i = 0; i < 10; i++)
		{
			mas[i] = new int[10];
		}
	}

	~Array() {}

	void init()
	{
		srand(time(0));

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mas[i][j] = 0 + rand() % 100;
				std::cout << mas[i][j] << " ";
			}
		}

		std::cout  << std::endl << std::endl;
	}

	void masfact()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mas[i][j] = fact(mas[i][j]);
				std::cout << mas[i][j] << " ";
			}
			std::cout << "\t" << std::endl;
		}
	}
};

int main()
{
	Array a;
	a.init();
	a.masfact();
    return 0;
}