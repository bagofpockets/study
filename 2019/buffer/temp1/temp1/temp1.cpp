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

struct COMPLEX_substruct
{
	std::string type, properties;
};

/*-----Вспомогательные функции-----*/

std::string delete_parentheses(std::string buff)
{
	buff.erase(0, 2); // удаляет
	buff.pop_back();  // внешние скобки

	return buff;
}

unsigned long long count_sharps(std::string buff)
{
	unsigned long long N(0);

	for (size_t i = buff.find_first_of('#'); i <= buff.find_last_of('#'); i++)
	{
		if (buff[i] == '#') N++;
	}

	return N;
}

std::string get_smth_str_1(std::string buff)
{
	size_t first_buffer(buff.find_first_of('\''));
	size_t second_buffer(buff.find_last_of('\'') - first_buffer);

	return buff.substr(first_buffer, second_buffer + 1);
}

std::vector<unsigned long long*> get_associated_ids(std::string buff, unsigned long long N)
{
	std::vector<unsigned long long*> associated_ids_buff;

	for (unsigned long long i = 0; i < N; i++)
	{
		buff.erase(0, 1);
		if ((buff.find_first_of('#') == 0) || (buff.find_first_of(',') == 0)) buff.erase(0, 1);

		if (buff.find_first_of(',') != std::string::npos)
		{
			size_t first_buffer = buff.find_first_of(',');
			associated_ids_buff.push_back(new unsigned long long(std::stoull(buff.substr(0, first_buffer))));
		}
		else associated_ids_buff.push_back(new unsigned long long(std::stoull(buff)));

		if (buff.find_first_of('#') != std::string::npos) buff.erase(0, buff.find_first_of('#'));
	}

	return associated_ids_buff;
}

std::string get_parentheses_content(std::string buff)
{
	size_t first_buffer = buff.find_first_of('(');
	size_t second_buffer = buff.find_first_of(')') - first_buffer;
	std::string ids_buffer = buff.substr(first_buffer, second_buffer);

	return ids_buffer;
}

std::vector<COMPLEX_substruct*> COMPLEX_sorter()
{
	std::vector<COMPLEX_substruct*> COMPLEX_vec;
	std::string buffer("(\nBOUNDED_SURFACE()\nB_SPLINE_SURFACE(3,3,((#1175,#1176,#1177,#1178),(#1179,#1180,#1181,#1182),\n(#1183,#1184,#1185,#1186),(#1187,#1188,#1189,#1190)),.UNSPECIFIED.,.F.,.F.,\n.F.)\nB_SPLINE_SURFACE_WITH_KNOTS((4,4),(4,4),(0.,1.),(0.,1.),.UNSPECIFIED.)\nGEOMETRIC_REPRESENTATION_ITEM()\nRATIONAL_B_SPLINE_SURFACE(((1.,0.959795080523939,0.959795080523939,1.),(0.991494080475098,\n0.951631140808605,0.951631140808605,0.991494080475098),(0.991494080475098,\n0.951631140808605,0.951631140808605,0.991494080475098),(1.,0.959795080523939,\n0.959795080523939,1.)))\nREPRESENTATION_ITEM('')\nSURFACE()\n)");
	std::string sub_buff;
	size_t first_buffer(0);
	size_t second_buffer(0);
	COMPLEX_substruct* COMPLEX_buff(NULL);

	buffer = delete_parentheses(buffer);
	buffer.erase(0, 1);

	while (buffer.find_first_of('\n') != std::string::npos)
	{
		if (buffer.find_first_of('\n') == 0) buffer.erase(0, 1);
		sub_buff = buffer.substr(0, buffer.find_first_of('\n'));

		first_buffer = sub_buff.find_first_of('(');
		second_buffer = sub_buff.find_last_of(')');

		if (first_buffer != std::string::npos)
		{
			if ((first_buffer > sub_buff.find_first_of(')')) || (sub_buff[first_buffer + 1] == '#')) COMPLEX_buff->properties += sub_buff.substr(0, second_buffer + 1);
			else
			{
				COMPLEX_buff = new COMPLEX_substruct;

				if (sub_buff[sub_buff.length()] != ')') COMPLEX_buff->type = sub_buff.substr(0, first_buffer);

				if (second_buffer != std::string::npos)
				{
					if (second_buffer != sub_buff.length()) COMPLEX_buff->properties = sub_buff.substr(first_buffer, sub_buff.length() - first_buffer + 1);
					else COMPLEX_buff->properties = sub_buff.substr(first_buffer, second_buffer - first_buffer + 1);
				}
				else COMPLEX_buff->properties = sub_buff;

				COMPLEX_vec.push_back(COMPLEX_buff);
			}
		}
		else COMPLEX_buff->properties += sub_buff.substr(0, second_buffer + 1);

		buffer.erase(0, sub_buff.length());
	}

	//std::cout << buffer << " " << buffer.find_first_of('\n') << std::endl;
	return COMPLEX_vec;
}

int main()
{
	//std::string buffer("\n(\nBOUNDED_SURFACE()\nB_SPLINE_SURFACE(2,1,((#969,#970),(#971,#972),(#973,#974)),.UNSPECIFIED.,\n.F.,.F.,.F.)\nB_SPLINE_SURFACE_WITH_KNOTS((3,3),(2,2),(0.,1.),(0.,1.),.UNSPECIFIED.)\nGEOMETRIC_REPRESENTATION_ITEM()\nRATIONAL_B_SPLINE_SURFACE(((0.400039406982928,0.400039406982928),(0.599960593017072,\n0.599960593017072),(0.400039406982928,0.400039406982928)))\nREPRESENTATION_ITEM('')\nSURFACE()\n)");
	
	std::vector<COMPLEX_substruct*> a = COMPLEX_sorter();

	return 0;
}