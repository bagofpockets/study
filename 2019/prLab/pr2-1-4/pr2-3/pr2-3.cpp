// pr2-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Token
{
public:
	Token() {}
	virtual ~Token() {}
	virtual std::string get_value() = 0;
};

class Token_str : public Token
{
private:
	std::string* value_s;

public:
	Token_str(std::string value) : value_s(new std::string(value)) {}
	~Token_str()
	{
		delete value_s;
	}

	std::string get_value() override
	{
		return *value_s;
	}
};

class Token_int : public Token
{
private:
	int* value_i;

public:
	Token_int(int value) : value_i(new int(value)) {}
	~Token_int()
	{
		delete value_i;
	}

	std::string get_value() override
	{
		return std::to_string(*value_i);
	}
};

bool is_int(std::string S)
{
	std::string::const_iterator it = S.begin();
	while (it != S.end() && std::isdigit(*it)) ++it;
	return !S.empty() && it == S.end();
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::string origstring("инструкция 2544 не допускает исключений, либо это не инструкция, а совет 129");
	std::stringstream check(origstring);
	std::vector<Token*> v;
	std::string buff_str;

	while (getline(check, buff_str, ' '))
	{
		if (buff_str[buff_str.length() - 1] == ',') buff_str.pop_back();
		if (is_int(buff_str))
		{
			v.push_back(new Token_int(std::stoi(buff_str)));
		}
		else
		{
			v.push_back(new Token_str(buff_str));
		}	
	}

	for (unsigned int i = 0; i < v.size(); i++)
	{
		std::cout << v[i]->get_value() << std::endl;
	}

	for (unsigned int i = 0; i < v.size(); i++)
	{
		delete v[i];
		v[i] = 0;
	}

	return 0;
}