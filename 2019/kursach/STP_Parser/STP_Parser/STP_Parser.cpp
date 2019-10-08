// STP_Parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CLOSED_SHELL
{
	friend class File_handler;

private:
	std::string smth;
	unsigned long long* ids_quantity;
	unsigned long long* associated_ids;

	void set_associated_id(unsigned long long POS, unsigned long long ID)
	{
		associated_ids[POS] = ID;
		return;
	}

public:
	CLOSED_SHELL() {}
	CLOSED_SHELL(unsigned long long N) : associated_ids(new unsigned long long[N]), ids_quantity(new unsigned long long(N))
	{
		
	}
	~CLOSED_SHELL()
	{
		delete[] associated_ids;
		delete ids_quantity;
	}

	unsigned long long get_ids_quantity()
	{
		return *ids_quantity;
	}
};

class ADVANCED_FACE : public CLOSED_SHELL
{
	friend class File_handler;

private:

public:
	ADVANCED_FACE() {}
	~ADVANCED_FACE() {}
};

class B_SPLINE_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	struct CARTESIAN_POINT
	{
		std::string smth;
		double x, y, z;
	} *CARTESIAN_POINT_buffer;

	std::vector<CARTESIAN_POINT*>* CARTESIAN_POINT_vec;

public:
	B_SPLINE_SURFACE() : CARTESIAN_POINT_vec(new std::vector<CARTESIAN_POINT*>)
	{
		CARTESIAN_POINT_buffer = new CARTESIAN_POINT;
		CARTESIAN_POINT_vec->push_back(CARTESIAN_POINT_buffer);
	}

	~B_SPLINE_SURFACE()
	{
		for (unsigned long long i = 0; i < CARTESIAN_POINT_vec->size(); i++)
		{
			delete CARTESIAN_POINT_vec->at(i);
			CARTESIAN_POINT_vec->at(i) = 0;
		}
		delete CARTESIAN_POINT_vec;
	}
};

class CONICAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:

public:
	CONICAL_SURFACE() {}
	~CONICAL_SURFACE() {}
};

class File_handler
{
private:
	struct input_data
	{
		unsigned long long id;
		std::string type, properties;
	} *data_buffer;

	std::ifstream* input_file;
	std::vector<input_data*>* data_vec;

	std::vector<input_data*>* get_data()
	{
		if (input_file->is_open())
		{
			size_t* pos(new size_t(0));
			std::string* input_buffer(new std::string);

			while (getline(*input_file, *input_buffer, ';'))
			{
				if (input_buffer->length() > 1) if (input_buffer->at(1) == '#')
				{
					data_buffer = new input_data;
					
					input_buffer->erase(1, 1);

					*pos = input_buffer->find_first_of('=');

					data_buffer->id = std::stoull(input_buffer->substr(1, *pos));
					input_buffer->erase(1, *pos);

					*pos = input_buffer->find_first_of('(') - 1; // \n :angry:

					if (*pos > 0)
					{
						data_buffer->type = input_buffer->substr(1, *pos);
						input_buffer->erase(1, *pos);
					}
					else
					{
						data_buffer->type = "COMPLEX";
					}

					data_buffer->properties = *input_buffer;

					data_vec->push_back(data_buffer);
				}
			}

			delete pos;
			delete input_buffer;

			return data_vec;
		}
		else
		{
			std::cout << "Can't open file" << std::endl;
			return data_vec;
		}
	}

public:
	File_handler(std::string input_file_name) : input_file(new std::ifstream), data_vec(new std::vector<input_data*>)
	{
		input_file->open(input_file_name);
	}

	~File_handler()
	{
		input_file->close();

		for (unsigned long long i = 0; i < data_vec->size(); i++)
		{
			delete data_vec->at(i);
			data_vec->at(i) = 0;
		}

		delete data_vec;
		delete input_file;
	}

	void print_data()
	{
		std::vector<input_data*>* vd(new std::vector<input_data*>(*get_data()));
		std::vector<CLOSED_SHELL*> v = CLOSED_SHELL_sorter();
		/*for (unsigned long long i = 0; i < vd->size(); i++)
		{
			std::cout << "id = " << vd->at(i)->id << "\ntype:" << vd->at(i)->type << "\nproperties: " << vd->at(i)->properties  << std::endl;
		}*/

		for (unsigned long long i = 0; i < v.size(); i++)
		{
			for (unsigned long long j = 0; j < v.at(i)->get_ids_quantity(); j++)
			{
				std::cout << v.at(i)->associated_ids[j] << ' ';
			}
			std::cout << std::endl;
		}

		delete vd;
		return;
	}

	std::vector<CLOSED_SHELL*> CLOSED_SHELL_sorter()
	{
		std::vector<CLOSED_SHELL*> CLOSED_SHELL_vec;
		std::string* buffer(new std::string);
		size_t* first_buffer(new size_t);
		size_t* second_buffer(new size_t);
		unsigned long long* N_buffer(new unsigned long long);
		unsigned long long* Id_buffer(new unsigned long long);
		CLOSED_SHELL* CLOSED_SHELL_buffer;

		for (unsigned long long i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->type == "CLOSED_SHELL")
			{
				*buffer = data_vec->at(i)->properties;
				*N_buffer = 0;

				buffer->erase(0, 2); // удаляет
				buffer->pop_back();  // внешние скобки

				for (size_t j = buffer->find_first_of('#'); j <= buffer->find_last_of('#'); j++)
				{
					if (buffer->at(j) == '#') ++*N_buffer;
				}

				CLOSED_SHELL_buffer = new CLOSED_SHELL(*N_buffer);

				*first_buffer = buffer->find_first_of('\'');
				*second_buffer = buffer->find_last_of('\'') - buffer->find_first_of('\'');

				CLOSED_SHELL_buffer->smth = buffer->substr(*first_buffer, *second_buffer + 1);

				*second_buffer = buffer->find_first_of('(') - buffer->find_first_of('\'');

				buffer->erase(*first_buffer, *second_buffer + 1);
				buffer->pop_back();

				for (unsigned long long j = 0; j < *N_buffer; j++)
				{
					buffer->erase(0, 1);
					*second_buffer = buffer->find_first_of(',');
					*Id_buffer = std::stoull(buffer->substr(0, *second_buffer));

					CLOSED_SHELL_buffer->set_associated_id(j, *Id_buffer);

					buffer->erase(0, buffer->find_first_of('#'));
				}

				CLOSED_SHELL_vec.push_back(CLOSED_SHELL_buffer);
			}
		}

		delete buffer;
		delete first_buffer;
		delete second_buffer;
		delete N_buffer;
		delete Id_buffer;

		return CLOSED_SHELL_vec;
	}
};

int main()
{
	File_handler* a(new File_handler("MBA_N.STP"));

	a->print_data();

	delete a;

    return 0;
}