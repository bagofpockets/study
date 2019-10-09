// STP_Parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*-----Абстракция структур-----*/

class Support_struct
{
	friend class File_handler;

protected:
	unsigned long long id;
	std::string smth;
	double x, y, z;

public:
	Support_struct() : x(0), y(0), z(0), id(0) {}
	virtual ~Support_struct() {}

	virtual std::string get_type() = 0;
};

class CARTESIAN_POINT : public Support_struct
{
public:
	CARTESIAN_POINT() {}
	~CARTESIAN_POINT() {}

	std::string get_type() override { return "CARTESIAN_POINT"; }
};

class DIRECTION : public Support_struct
{
public:
	DIRECTION() {}
	~DIRECTION() {}

	std::string get_type() override { return "DIRECTION"; }
};

/*-----Поверхности и нужное для них-----*/

class CLOSED_SHELL
{
	friend class File_handler;

private:
	std::string* smth;
	unsigned long long* ids_quantity;
	unsigned long long* associated_ids;

public:
	CLOSED_SHELL() : associated_ids(new unsigned long long[0]), ids_quantity(new unsigned long long(0)), smth(new std::string) {}
	CLOSED_SHELL(unsigned long long N) : associated_ids(new unsigned long long[N]), ids_quantity(new unsigned long long(N)), smth(new std::string) {}
	virtual ~CLOSED_SHELL()
	{
		delete[] associated_ids;
		delete ids_quantity;
	}

	virtual unsigned long long get_ids_quantity()
	{
		return *ids_quantity;
	}

	unsigned long long get_associated_id(unsigned long long POS)
	{
		return associated_ids[POS];
	}
};

class ADVANCED_FACE : public CLOSED_SHELL
{
	friend class File_handler;

private:
	std::string* smth_str1;
	std::string* smth_str2;
	unsigned long long* ids_quantity;
	unsigned long long* FACE_BOUND_ids;
	unsigned long long* associated_id;

public:
	ADVANCED_FACE() : FACE_BOUND_ids(new unsigned long long[0]), ids_quantity(new unsigned long long(0)), associated_id(new unsigned long long), smth_str1(new std::string), smth_str2(new std::string) {}
	ADVANCED_FACE(unsigned long long N) : FACE_BOUND_ids(new unsigned long long[N]), ids_quantity(new unsigned long long(N)), associated_id(new unsigned long long), smth_str1(new std::string), smth_str2(new std::string) {}
	virtual ~ADVANCED_FACE()
	{
		delete[] FACE_BOUND_ids;
		delete ids_quantity;
		delete associated_id;
		delete smth_str1;
		delete smth_str2;
	}

	unsigned long long get_ids_quantity() override
	{
		return *ids_quantity;
	}

	unsigned long long get_associated_id()
	{
		return *associated_id;
	}
};

class AXIS2_PLACEMENT_3D
{
	friend class File_handler;

private:
	std::string* smth_str;
	unsigned long long* id;
	std::vector<Support_struct*> associated_ids;

public:
	AXIS2_PLACEMENT_3D() : smth_str(new std::string), id(new unsigned long long) {}
	~AXIS2_PLACEMENT_3D()
	{
		delete smth_str;
		delete id;
	}
};

class CONICAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	std::string* smth_str;
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	double* smth1;
	double* smth2;

public:
	CONICAL_SURFACE() : AXIS2_PLACEMENT_3D_data(new AXIS2_PLACEMENT_3D), smth1(new double), smth2(new double), smth_str(new std::string) {}
	~CONICAL_SURFACE()
	{
		delete AXIS2_PLACEMENT_3D_data;
		delete smth1;
		delete smth2;
		delete smth_str;
	}
};

/*class B_SPLINE_SURFACE : public ADVANCED_FACE, public Support_struct
{
	friend class File_handler;

private:
	CARTESIAN_POINT* CARTESIAN_POINT_buffer;

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
};*/

/*-----Работа с файлом-----*/

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

	std::vector<CLOSED_SHELL*> CLOSED_SHELL_sorter()
	{
		std::vector<CLOSED_SHELL*> CLOSED_SHELL_vec;
		std::string buffer;
		size_t first_buffer;
		size_t second_buffer;
		unsigned long long N_buffer;
		unsigned long long Id_buffer;
		CLOSED_SHELL* CLOSED_SHELL_buffer;

		for (unsigned long long i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->type == "CLOSED_SHELL")
			{
				buffer = data_vec->at(i)->properties;
				N_buffer = 0;

				buffer.erase(0, 2); // удаляет
				buffer.pop_back();  // внешние скобки

				for (size_t j = buffer.find_first_of('#'); j <= buffer.find_last_of('#'); j++)
				{
					if (buffer[j] == '#') N_buffer++;
				}

				CLOSED_SHELL_buffer = new CLOSED_SHELL(N_buffer);

				first_buffer = buffer.find_first_of('\'');
				second_buffer = buffer.find_last_of('\'') - first_buffer;

				*CLOSED_SHELL_buffer->smth = buffer.substr(first_buffer, second_buffer + 1);

				second_buffer = buffer.find_first_of('(') - first_buffer;

				buffer.erase(first_buffer, second_buffer + 1);
				buffer.pop_back();

				for (unsigned long long j = 0; j < N_buffer; j++)
				{
					buffer.erase(0, 1);
					second_buffer = buffer.find_first_of(',');
					Id_buffer = std::stoull(buffer.substr(0, second_buffer));

					CLOSED_SHELL_buffer->associated_ids[j] = Id_buffer;

					buffer.erase(0, buffer.find_first_of('#'));
				}

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
		size_t first_buffer;
		size_t second_buffer;
		unsigned long long N_buffer;
		unsigned long long Id_buffer;
		ADVANCED_FACE* ADVANCED_FACE_buffer;

		for (unsigned long long i = 0; i < input_CLOSED_SHELL.size(); i++)
		{
			for (unsigned long long j = 0; j < input_CLOSED_SHELL.at(i)->get_ids_quantity(); j++)
			{
				for (unsigned long long k = 0; k < data_vec->size(); k++)
				{
					if ((data_vec->at(k)->type == "ADVANCED_FACE") && (data_vec->at(k)->id == input_CLOSED_SHELL.at(i)->associated_ids[j]))
					{
						buffer = data_vec->at(k)->properties;
						N_buffer = 0;

						buffer.erase(0, 2); // удаляет
						buffer.pop_back();  // внешние скобки

						for (size_t j = buffer.find_first_of('#'); j <= buffer.find_last_of(')'); j++)
						{
							if (buffer[j] == '#') N_buffer++;
						}

						ADVANCED_FACE_buffer = new ADVANCED_FACE(N_buffer);

						first_buffer = buffer.find_first_of('\'');
						second_buffer = buffer.find_last_of('\'') - first_buffer;

						*ADVANCED_FACE_buffer->smth_str1 = buffer.substr(first_buffer, second_buffer + 1);

						first_buffer = buffer.find_first_of('(');
						second_buffer = buffer.find_first_of(')') - first_buffer;
						ids_buffer = buffer.substr(first_buffer, second_buffer);

						for (unsigned long long i = 0; i < N_buffer; i++)
						{
							ids_buffer.erase(0, ids_buffer.find_first_of('#'));

							Id_buffer = std::stoull(ids_buffer.substr(1, ids_buffer.find_first_of(',')));

							ADVANCED_FACE_buffer->FACE_BOUND_ids[i] = Id_buffer;
						}

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
					}
				}
			}
		}

		return ADVANCED_FACE_vec;
	}

	Support_struct* struct_sorter(unsigned long long ID)
	{
		Support_struct* support_buff(new CARTESIAN_POINT);
		std::string buffer;
		size_t first_buffer;
		size_t second_buffer;
		unsigned long long i(0);

		for (i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->id == ID)
			{
				buffer = data_vec->at(i)->properties;
				break;
			}
		}

		if (data_vec->at(i)->type == "CARTESIAN_POINT")
		{
			delete support_buff;
			support_buff = new CARTESIAN_POINT;
		}
		else if (data_vec->at(i)->type == "DIRECTION")
		{
			delete support_buff;
			support_buff = new DIRECTION;
		}

		buffer.erase(0, 2); // удаляет
		buffer.pop_back();  // внешние скобки

		first_buffer = buffer.find_first_of('\'');
		second_buffer = buffer.find_last_of('\'') - buffer.find_first_of('\'');

		support_buff->smth = buffer.substr(first_buffer, second_buffer + 1);

		buffer.erase(0, buffer.find_first_of('('));

		first_buffer = buffer.find_first_of('(') + 1;
		second_buffer = buffer.find_first_of(')') - first_buffer;
		buffer = buffer.substr(first_buffer, second_buffer);

		second_buffer = buffer.find_first_of(',');
		support_buff->x = std::stod(buffer.substr(0, second_buffer));

		buffer.erase(0, second_buffer + 1);

		second_buffer = buffer.find_first_of(',');
		support_buff->y = std::stod(buffer.substr(0, second_buffer));

		buffer.erase(0, second_buffer + 1);

		second_buffer = buffer.find_first_of(',');
		support_buff->z = std::stod(buffer.substr(0, second_buffer)); // какая-то хрень с E-16 в 536

		return support_buff;
	}

	AXIS2_PLACEMENT_3D get_AXIS2_PLACEMENT_3D(unsigned long long ID)
	{
		AXIS2_PLACEMENT_3D AXIS2_PLACEMENT_3D_buff;
		std::string buffer;
		size_t first_buffer;
		size_t second_buffer;
		unsigned long long N_buffer(0);
		unsigned long long Id_buffer(0);

		for (unsigned long long i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->id == ID)
			{
				buffer = data_vec->at(i)->properties;

				buffer.erase(0, 2); // удаляет
				buffer.pop_back();  // внешние скобки

				for (size_t j = buffer.find_first_of('#'); j <= buffer.find_last_of('#'); j++)
				{
					if (buffer[j] == '#') N_buffer++;
				}

				first_buffer = buffer.find_first_of('\'');
				second_buffer = buffer.find_last_of('\'') - first_buffer;

				*AXIS2_PLACEMENT_3D_buff.smth_str = buffer.substr(first_buffer, second_buffer + 1);

				buffer.erase(0, buffer.find_first_of('#'));

				for (unsigned long long i = 0; i < N_buffer; i++)
				{
					buffer.erase(0, 1);
					second_buffer = buffer.find_first_of(',');

					Id_buffer = std::stoull(buffer.substr(0, second_buffer));

					if ((data_vec->at(Id_buffer)->type == "CARTESIAN_POINT") || (data_vec->at(Id_buffer)->type == "DIRECTION"))
					{
						AXIS2_PLACEMENT_3D_buff.associated_ids.push_back(struct_sorter(Id_buffer));
					}

					buffer.erase(0, buffer.find_first_of('#'));
				}

				break;
			}
		}

		return AXIS2_PLACEMENT_3D_buff;
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
		size_t first_buffer;
		size_t second_buffer;
		unsigned long long Id_buffer(0);
		CONICAL_SURFACE* CONICAL_SURFACE_buffer;

		for (unsigned long long i = 0; i < input_ADVANCED_FACE.size(); i++)
		{
			for (unsigned long long j = 0; j < data_vec->size(); j++)
			{
				if ((data_vec->at(j)->type == "CONICAL_SURFACE") && (data_vec->at(j)->id == input_ADVANCED_FACE[i]->get_associated_id()))
				{
					buffer = data_vec->at(j)->properties;

					buffer.erase(0, 2); // удаляет
					buffer.pop_back();  // внешние скобки

					CONICAL_SURFACE_buffer = new CONICAL_SURFACE;

					first_buffer = buffer.find_first_of('\'');
					second_buffer = buffer.find_last_of('\'') - first_buffer;

					*CONICAL_SURFACE_buffer->smth_str = buffer.substr(first_buffer, second_buffer + 1);

					buffer.erase(0, buffer.find_first_of(',') + 1);

					first_buffer = buffer.find_first_of('#') + 1;
					second_buffer = buffer.find_first_of(',') - first_buffer;

					Id_buffer = std::stoull(buffer.substr(first_buffer, second_buffer));
					*CONICAL_SURFACE_buffer->AXIS2_PLACEMENT_3D_data->id = Id_buffer;
					*CONICAL_SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(Id_buffer);

					buffer.erase(0, buffer.find_first_of(',') + 1);
					first_buffer = buffer.find_first_of(',');

					*CONICAL_SURFACE_buffer->smth1 = std::stod(buffer.substr(0, first_buffer));

					buffer.erase(0, buffer.find_first_of(',') + 1);
					first_buffer = buffer.find_first_of(',');

					*CONICAL_SURFACE_buffer->smth2 = std::stod(buffer.substr(0, first_buffer));

					CONICAL_SURFACE_vec.push_back(CONICAL_SURFACE_buffer);
				}
			}
		}

		return CONICAL_SURFACE_vec;
	}

	void print_data()
	{
		get_data();
		std::vector<CONICAL_SURFACE*> vb = CONICAL_SURFACE_sorter();

		/*for (unsigned long long i = 0; i < data_vec->size(); i++)
		{
			std::cout << "id = " << data_vec->at(i)->id << "\ntype: " << data_vec->at(i)->type << "\nproperties: " << data_vec->at(i)->properties  << std::endl;
		} //вывод всего файла*/

		/*for (unsigned long long i = 0; i < vb.size(); i++)
		{
			std::cout << *vb.at(i)->smth_str << ' ' << *vb.at(i)->smth1 << ' ' << *vb.at(i)->smth2 << '\n';
			for (unsigned long long j = 0; j < vb.at(j)->AXIS2_PLACEMENT_3D_data->associated_ids.size(); j++)
			{
				std::cout << vb.at(0)->AXIS2_PLACEMENT_3D_data->associated_ids[0]->x << ' ' << vb.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids[0]->y << ' ' << vb.at(0)->AXIS2_PLACEMENT_3D_data->associated_ids[0]->z << '\n';
			}
		}*/

		return;
	}
};

int main()
{
	File_handler a("MBA_N.STP");

	a.print_data();

    return 0;
}