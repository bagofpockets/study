#include "Secondary_funcs.h"
std::string* delete_parentheses(std::string* buff)
{
	buff->erase(0, buff->find_first_of('(') + 1); // удаляет
	buff->pop_back();  // внешние скобки

	return buff;
}

unsigned long long count_sharps(std::string* buff)
{
	unsigned long long N(0);

	for (size_t i = buff->find_first_of('#'); i <= buff->find_last_of('#'); i++)
	{
		if (buff->operator[](i) == '#') N++;
	}

	return N;
}

std::string get_smth_str_1(const std::string* buff)
{
	size_t first_buffer(buff->find_first_of('\''));
	size_t second_buffer(buff->find_last_of('\'') - first_buffer);

	return buff->substr(first_buffer, second_buffer + 1);
}

std::vector<unsigned long long*>* get_associated_ids(std::string* buff, unsigned long long* N)
{
	std::vector<unsigned long long*>* associated_ids_buff(new std::vector<unsigned long long*>);

	for (unsigned long long i = 0; i < *N; i++)
	{
		buff->erase(0, 1);
		if ((buff->find_first_of('#') == 0) || (buff->find_first_of(',') == 0)) buff->erase(0, 1);

		if (buff->find_first_of(',') != std::string::npos)
		{
			size_t first_buffer = buff->find_first_of(',');
			associated_ids_buff->push_back(new unsigned long long(std::stoull(buff->substr(0, first_buffer))));
		}
		else associated_ids_buff->push_back(new unsigned long long(std::stoull(*buff)));

		if (buff->find_first_of('#') != std::string::npos) buff->erase(0, buff->find_first_of('#'));
	}

	return associated_ids_buff;
}

std::string get_parentheses_content(const std::string* buff)
{
	size_t first_buffer = buff->find_first_of('(');
	size_t second_buffer = buff->find_first_of(')') - first_buffer;
	std::string ids_buffer = buff->substr(first_buffer, second_buffer);

	return ids_buffer;
}