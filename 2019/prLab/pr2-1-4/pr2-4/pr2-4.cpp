// pr2-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

class Book
{
private:
	std::string author;
	std::string title;
	bool type_fic;

public:
	Book(std::string author, std::string title, bool type_fic) : author(author), title(title), type_fic(type_fic) {}
	~Book() {}

	std::string get_author()
	{
		return author;
	}

	std::string get_title()
	{
		return title;
	}

	bool is_fic()
	{
		return type_fic;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");

	int fic_count(0);
	int nonfic_count(0);
	std::vector<Book*> v;

	v.push_back(new Book("Пушкин А.С.", "Капитанская дочь", true));
	v.push_back(new Book("Стивен Хоккинг", "Кратчайшая история времени", false));
	v.push_back(new Book("Достоевский Ф.М.", "Идиот", true));

	for (unsigned int i = 0; i < v.size(); i++)
	{
		switch (v[i]->is_fic())
		{
		case true:
			fic_count++;
			break;
		case false:
			nonfic_count++;
			break;
		}
	}

	std::cout << "Count w/ switch\n fics:" << fic_count << "\n nonfics:" << nonfic_count << std::endl;

	fic_count = 0;
	nonfic_count = 0;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i]->is_fic())
		{
			fic_count++;
		}
		else
		{
			nonfic_count++;
		}
	}

	std::cout << "\nCount w/out switch\n fics:" << fic_count << "\n nonfics:" << nonfic_count << std::endl;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

	return 0;
}