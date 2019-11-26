#include <iostream>
#include "File_handler.h"
File_handler::File_handler(std::string input_file_name) :
	input_file(new std::ifstream),
	data_vec(new std::vector<input_data*>),
	initialized(new bool(false))
{
	try
	{
		input_file->open(input_file_name);
		if (!input_file->is_open())
		{
			throw "Unable to open file";
		}
	}
	catch (char* str)
	{
		std::cout << str << std::endl;
	}
}

File_handler::~File_handler()
{
	input_file->close();

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		delete (*i);
		*i = 0;
	}
	delete initialized;
	delete data_vec;
	delete input_file;
}

void File_handler::get_data()
{
	if (!*initialized)
	{
		input_data* data_buffer(NULL);
		size_t* pos(new size_t(0));
		std::string* input_buffer(new std::string);
		bool is_empty_type(true);
		std::string type_buff;
		unsigned long long id_buff(0);

		while (getline(*input_file, *input_buffer, ';'))
		{
			if (input_buffer->length() > 1) if (input_buffer->at(1) == '#')
			{
				input_buffer->erase(1, 1);

				*pos = input_buffer->find_first_of('=');

				id_buff = std::stoull(input_buffer->substr(1, *pos));
				input_buffer->erase(1, *pos);

				*pos = input_buffer->find_first_of('(') - 1;

				if (*pos > 0)
				{
					type_buff = input_buffer->substr(1, *pos);
					input_buffer->erase(1, *pos);
				}
				else
				{
					type_buff = "COMPLEX";
				}

				is_empty_type = true;
				if (data_vec->empty())
				{
					data_buffer = new input_data;
					data_buffer->type = type_buff;
					data_vec->push_back(data_buffer);
				}
				for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
				{
					if ((*i)->type == type_buff)
					{
						(*i)->data.insert(std::pair<unsigned long long, std::string>(id_buff, *input_buffer));
						is_empty_type = false;
						break;
					}
				}
				if (is_empty_type)
				{
					data_buffer = new input_data;
					data_buffer->type = type_buff;
					data_buffer->data.insert(std::pair<unsigned long long, std::string>(id_buff, *input_buffer));
					data_vec->push_back(data_buffer);
				}
			}
		}

		delete pos;
		delete input_buffer;

		*initialized = true;
		return;
	}
}