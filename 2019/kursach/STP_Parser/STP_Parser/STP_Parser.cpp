// STP_Parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*----Вспомогательные классы-----*/

class Support_class //Абстракция CARTESIAN_POINT и DIRECTION
{
	friend class File_handler;

private:
	std::string* smth_str1;
	std::string* type;
	double* x;
	double* y;
	double* z;

public:
	Support_class() : smth_str1(new std::string), type(new std::string), x(new double(0)), y(new double(0)), z(new double(0)) {}
	~Support_class()
	{
		delete smth_str1;
		delete type;
		delete x;
		delete y;
		delete z;
	}
};

class AXIS2_PLACEMENT_3D
{
	friend class File_handler;

private:
	std::string* smth_str1;
	std::vector<Support_class*>* associated_ids;

public:
	AXIS2_PLACEMENT_3D() : smth_str1(new std::string), associated_ids(new std::vector<Support_class*>) {}
	~AXIS2_PLACEMENT_3D()
	{
		for (size_t i = 0; i < associated_ids->size(); i++)
		{
			delete associated_ids->at(i);
			associated_ids->at(i) = 0;
		}

		delete associated_ids;
		delete smth_str1;
	}
};

/*-----Поверхности-----*/

class CLOSED_SHELL
{
	friend class File_handler;

protected:
	std::string* smth_str1;
	std::vector<unsigned long long*>* associated_ids;

public:
	CLOSED_SHELL() : associated_ids(new std::vector<unsigned long long*>), smth_str1(new std::string) {}
	virtual ~CLOSED_SHELL()
	{
		for (size_t i = 0; i < associated_ids->size(); i++)
		{
			delete associated_ids->at(i);
			associated_ids->at(i) = 0;
		}

		delete associated_ids;
		delete smth_str1;
	}
};

class ADVANCED_FACE : public CLOSED_SHELL
{
	friend class File_handler;

private:
	unsigned long long* associated_id;
	std::string* smth_str2;

public:
	ADVANCED_FACE() : associated_id(new unsigned long long(0)), smth_str2(new std::string) {}
	virtual ~ADVANCED_FACE()
	{
		delete associated_id;
		delete smth_str2;
	}
};

class CONICAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	double* smth_d1;
	double* smth_d2;

public:
	CONICAL_SURFACE() : AXIS2_PLACEMENT_3D_data(new AXIS2_PLACEMENT_3D), smth_d1(new double(0)), smth_d2(new double(0)) {}
	~CONICAL_SURFACE()
	{
		delete AXIS2_PLACEMENT_3D_data;
		delete smth_d1;
		delete smth_d2;
	}
};

/*-----Работа с файлом-----*/

class File_handler
{
private:
	struct input_data
	{
		unsigned long long id = 0;
		std::string type, properties;
	} *data_buffer;

	std::ifstream* input_file;
	std::vector<input_data*>* data_vec;

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

	Support_class* get_support_object(unsigned long long ID)
	{
		Support_class* support_buff(new Support_class);
		std::string buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);

		for (size_t i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->id == ID)
			{
				*support_buff->type = data_vec->at(i)->type;

				buffer = data_vec->at(i)->properties;

				buffer = delete_parentheses(buffer);

				*support_buff->smth_str1 = get_smth_str_1(buffer);

				buffer = get_parentheses_content(buffer);
				buffer.erase(0, 1);

				second_buffer = buffer.find_first_of(',');
				*support_buff->x = std::stod(buffer.substr(0, second_buffer));

				buffer.erase(0, second_buffer + 1);

				second_buffer = buffer.find_first_of(',');
				*support_buff->y = std::stod(buffer.substr(0, second_buffer));

				buffer.erase(0, second_buffer + 1);

				*support_buff->z = std::stod(buffer);

				break;
			}
		}

		return support_buff;
	}

	AXIS2_PLACEMENT_3D* get_AXIS2_PLACEMENT_3D(unsigned long long ID)
	{
		AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_buff(new AXIS2_PLACEMENT_3D);
		std::string buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long N_buffer(0);
		unsigned long long Id_buffer(0);

		for (size_t i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->id == ID)
			{
				buffer = data_vec->at(i)->properties;

				buffer = delete_parentheses(buffer);

				N_buffer = count_sharps(buffer);

				*AXIS2_PLACEMENT_3D_buff->smth_str1 = get_smth_str_1(buffer);

				buffer.erase(0, buffer.find_first_of('#'));

				for (unsigned long long j = 0; j < N_buffer; j++)
				{
					buffer.erase(0, 1);
					second_buffer = buffer.find_first_of(',');

					Id_buffer = std::stoull(buffer.substr(0, second_buffer));

					for (size_t k = 0; k < data_vec->size(); k++)
					{
						if (data_vec->at(k)->id == Id_buffer)
						{
							if ((data_vec->at(k)->type == "CARTESIAN_POINT") || (data_vec->at(k)->type == "DIRECTION"))
							{
								AXIS2_PLACEMENT_3D_buff->associated_ids->push_back(get_support_object(Id_buffer));

								break;
							}
						}
					}

					if (buffer.find('#') != std::string::npos) buffer.erase(0, buffer.find_first_of('#'));
				}

				break;
			}
		}

		return AXIS2_PLACEMENT_3D_buff;
	}

	/*-----Сортировщики-----*/

	std::vector<CLOSED_SHELL*> CLOSED_SHELL_sorter()
	{
		std::vector<CLOSED_SHELL*> CLOSED_SHELL_vec;
		std::string buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long N_buffer(0);
		CLOSED_SHELL* CLOSED_SHELL_buffer;

		for (size_t i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->type == "CLOSED_SHELL")
			{
				buffer = data_vec->at(i)->properties;
				N_buffer = count_sharps(buffer);

				buffer = delete_parentheses(buffer);

				CLOSED_SHELL_buffer = new CLOSED_SHELL;

				*CLOSED_SHELL_buffer->smth_str1 = get_smth_str_1(buffer);

				first_buffer = buffer.find_first_of('\'');
				second_buffer = buffer.find_first_of('(') - first_buffer;

				buffer.erase(first_buffer, second_buffer + 1);
				buffer.pop_back();

				*CLOSED_SHELL_buffer->associated_ids = get_associated_ids(buffer, N_buffer);

				CLOSED_SHELL_vec.push_back(CLOSED_SHELL_buffer);
			}
		}

		return CLOSED_SHELL_vec;
	}

	std::vector<ADVANCED_FACE*> ADVANCED_FACE_sorter()
	{
		std::vector<CLOSED_SHELL*> input_CLOSED_SHELL = CLOSED_SHELL_sorter();

		std::vector<ADVANCED_FACE*> ADVANCED_FACE_vec;
		std::string buffer;
		std::string ids_buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long N_buffer(0);
		ADVANCED_FACE* ADVANCED_FACE_buffer;

		for (size_t i = 0; i < input_CLOSED_SHELL.size(); i++)
		{
			for (size_t j = 0; j < input_CLOSED_SHELL.at(i)->associated_ids->size(); j++)
			{
				for (size_t k = 0; k < data_vec->size(); k++)
				{
					if ((data_vec->at(k)->type == "ADVANCED_FACE") && (data_vec->at(k)->id == *input_CLOSED_SHELL.at(i)->associated_ids->at(j)))
					{
						buffer = data_vec->at(k)->properties;

						buffer = delete_parentheses(buffer);

						N_buffer = count_sharps(get_parentheses_content(buffer));

						ADVANCED_FACE_buffer = new ADVANCED_FACE;

						*ADVANCED_FACE_buffer->smth_str1 = get_smth_str_1(buffer);

						ids_buffer = get_parentheses_content(buffer);
						*ADVANCED_FACE_buffer->associated_ids = get_associated_ids(ids_buffer, N_buffer);

						first_buffer = buffer.find_first_of(')');
						buffer.erase(0, first_buffer);

						first_buffer = buffer.find_first_of('#');
						buffer.erase(0, first_buffer);

						first_buffer = buffer.find_first_of(',');
						second_buffer = buffer.find_first_of('#');

						*ADVANCED_FACE_buffer->associated_id = std::stoull(buffer.substr(1, first_buffer - second_buffer - 1));

						first_buffer = buffer.find_first_of('#');
						buffer.erase(0, first_buffer);

						first_buffer = buffer.find_first_of(',') + 1;
						buffer.erase(0, first_buffer);

						*ADVANCED_FACE_buffer->smth_str2 = buffer;

						ADVANCED_FACE_vec.push_back(ADVANCED_FACE_buffer);

						break;
					}

				}
			}
		}

		return ADVANCED_FACE_vec;
	}

public:
	File_handler(std::string input_file_name) : input_file(new std::ifstream), data_vec(new std::vector<input_data*>), data_buffer(NULL)
	{
		input_file->open(input_file_name);
	}

	~File_handler()
	{
		input_file->close();

		for (size_t i = 0; i < data_vec->size(); i++)
		{
			delete data_vec->at(i);
			data_vec->at(i) = 0;
		}

		delete data_vec;
		delete input_file;
	}

	void get_data()
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

					*pos = input_buffer->find_first_of('(') - 1;

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

			return;
		}
		else
		{
			std::cout << "Can't open file" << std::endl;
			return;
		}
	}

	std::vector<CONICAL_SURFACE*> CONICAL_SURFACE_sorter()
	{
		std::vector<ADVANCED_FACE*> input_ADVANCED_FACE = ADVANCED_FACE_sorter();

		std::vector<CONICAL_SURFACE*> CONICAL_SURFACE_vec;
		std::string buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long Id_buffer(0);
		CONICAL_SURFACE* CONICAL_SURFACE_buffer;

		for (unsigned long long i = 0; i < input_ADVANCED_FACE.size(); i++)
		{
			for (unsigned long long j = 0; j < data_vec->size(); j++)
			{
				if ((data_vec->at(j)->type == "CONICAL_SURFACE") && (data_vec->at(j)->id == *input_ADVANCED_FACE[i]->associated_id))
				{
					buffer = data_vec->at(j)->properties;

					buffer = delete_parentheses(buffer);

					CONICAL_SURFACE_buffer = new CONICAL_SURFACE;

					*CONICAL_SURFACE_buffer->smth_str1 = get_smth_str_1(buffer);

					buffer.erase(0, buffer.find_first_of(',') + 1);

					first_buffer = buffer.find_first_of('#') + 1;
					second_buffer = buffer.find_first_of(',') - first_buffer;

					Id_buffer = std::stoull(buffer.substr(first_buffer, second_buffer));
					CONICAL_SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(Id_buffer);

					buffer.erase(0, buffer.find_first_of(',') + 1);
					first_buffer = buffer.find_first_of(',');

					*CONICAL_SURFACE_buffer->smth_d1 = std::stod(buffer.substr(0, first_buffer));

					buffer.erase(0, buffer.find_first_of(',') + 1);
					first_buffer = buffer.find_first_of(',');

					*CONICAL_SURFACE_buffer->smth_d2 = std::stod(buffer.substr(0, first_buffer));

					CONICAL_SURFACE_vec.push_back(CONICAL_SURFACE_buffer);
				}
			}
		}

		return CONICAL_SURFACE_vec;
	}

	void print_data()
	{
		/*-----Здесь тестируется вывод-----*/
		get_data();

		//std::vector<CLOSED_SHELL*> va = CLOSED_SHELL_sorter();
		//std::vector<ADVANCED_FACE*> vb = ADVANCED_FACE_sorter();
		std::vector<CONICAL_SURFACE*> vc = CONICAL_SURFACE_sorter(); //#538 и #1155

		/*for (size_t i = 0; i < data_vec->size(); i++)
		{
			std::cout << "id = " << data_vec->at(i)->id << "\ntype: " << data_vec->at(i)->type << "\nproperties: " << data_vec->at(i)->properties  << std::endl;
		} //вывод всего файла*/

		/*for (size_t i = 0; i < va.size(); i++)
		{
			std::cout << "smth_str1 = " << *va.at(i)->smth_str1 << std::endl;
			for (unsigned long long j = 0; j < *va.at(i)->ids_quantity; j++)
			{
				std::cout << va.at(i)->associated_ids[j] << " ";
			}
			std::cout << std::endl;
		}*/

		/*for (size_t i = 0; i < vb.size(); i++)
		{
			std::cout << *vb.at(i)->smth_str1 << " ";
			for (size_t j = 0; j < vb.at(i)->associated_ids->size(); j++)
			{
				std::cout << *vb.at(i)->associated_ids->at(j) << " ";
			}
			std::cout << ", " << *vb.at(i)->associated_id << " " << *vb.at(i)->smth_str2 << std::endl;
		}*/

		for (size_t i = 0; i < vc.size(); i++)
		{
			std::cout << *vc.at(i)->smth_str1 << std::endl;
			for (size_t j = 0; j < vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->size(); j++)
			{
				std::cout << *vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->type << " " << *vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->smth_str1 << " " << *vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->x << " " << *vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->y << " " << *vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->z << std::endl;
			}
			std::cout << *vc.at(i)->smth_d1 << " " << *vc.at(i)->smth_d2 << std::endl;
		}

		return;
	}
};

int main()
{
	File_handler a("MBA_N.STP");

	a.print_data();

	return 0;
}