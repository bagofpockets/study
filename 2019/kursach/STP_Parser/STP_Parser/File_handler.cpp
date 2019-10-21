#include <iostream>
#include <fstream>
#include <iterator>
#include "File_handler.h"
struct input_data
{
	unsigned long long id = 0;
	std::string type, properties;
};

/*-----Вспомогательные функции-----*/

std::string File_handler::delete_parentheses(std::string buff)
{
	buff.erase(0, 2); // удаляет
	buff.pop_back();  // внешние скобки

	return buff;
}

unsigned long long File_handler::count_sharps(std::string buff)
{
	unsigned long long N(0);

	for (size_t i = buff.find_first_of('#'); i <= buff.find_last_of('#'); i++)
	{
		if (buff[i] == '#') N++;
	}

	return N;
}

std::string File_handler::get_smth_str_1(std::string buff)
{
	size_t first_buffer(buff.find_first_of('\''));
	size_t second_buffer(buff.find_last_of('\'') - first_buffer);

	return buff.substr(first_buffer, second_buffer + 1);
}

std::vector<unsigned long long*> File_handler::get_associated_ids(std::string buff, unsigned long long N)
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

std::string File_handler::get_parentheses_content(std::string buff)
{
	size_t first_buffer = buff.find_first_of('(');
	size_t second_buffer = buff.find_first_of(')') - first_buffer;
	std::string ids_buffer = buff.substr(first_buffer, second_buffer);

	return ids_buffer;
}

Support_class* File_handler::get_support_object(unsigned long long ID)
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

AXIS2_PLACEMENT_3D* File_handler::get_AXIS2_PLACEMENT_3D(unsigned long long ID)
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

B_SPLINE_SURFACE* File_handler::get_B_SPLINE_SURFACE(std::string buff)
{
	B_SPLINE_SURFACE* B_SPLINE_SURFACE_buff(new B_SPLINE_SURFACE);
	std::string buffer(buff), sub_buff, ids_buff;
	size_t first_buffer(0);
	size_t second_buffer(0);
	size_t third_buffer(0);
	unsigned long long N_buffer(0);
	unsigned long long Id_buffer(0);
	std::vector<unsigned long long*> associated_ids_buff;
	std::vector<Support_class*>* support_class_vec_buff;

	buffer.erase(0, 1);
	buffer.pop_back();

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_int1 = std::stoi(buffer.substr(0, second_buffer));

	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_int2 = std::stoi(buffer.substr(0, second_buffer));

	buffer.erase(0, second_buffer + 1);

	first_buffer = buffer.find_first_of('(') + 1;
	second_buffer = buffer.find_last_of(')');

	sub_buff = buffer.substr(first_buffer, second_buffer - first_buffer);

	first_buffer = sub_buff.find_first_of('(') + 1;
	third_buffer = sub_buff.find_first_of(')');

	while (third_buffer != std::string::npos)
	{
		ids_buff = sub_buff.substr(first_buffer, third_buffer - first_buffer);
		N_buffer = count_sharps(ids_buff);
		sub_buff.erase(0, third_buffer + 1);

		associated_ids_buff = get_associated_ids(ids_buff, N_buffer);

		support_class_vec_buff = new std::vector<Support_class*>;

		for (size_t i = 0; i < associated_ids_buff.size(); i++)
		{
			support_class_vec_buff->push_back(get_support_object(*associated_ids_buff[i]));
		}

		B_SPLINE_SURFACE_buff->associated_support_ids->push_back(support_class_vec_buff);

		first_buffer = sub_buff.find_first_of('(') + 1;
		third_buffer = sub_buff.find_first_of(')');
	}

	buffer.erase(0, second_buffer + 2);

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_str2 = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_str3 = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_str4 = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	*B_SPLINE_SURFACE_buff->smth_str5 = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	return B_SPLINE_SURFACE_buff;
}

/*-----Сортировщики-----*/

std::vector<CLOSED_SHELL*> File_handler::CLOSED_SHELL_sorter()
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

std::vector<ADVANCED_FACE*> File_handler::ADVANCED_FACE_sorter()
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

std::vector<input_data*> File_handler::COMPLEX_sorter(unsigned long long ID)
{
	std::vector<input_data*> COMPLEX_vec;
	std::string buffer, sub_buff;
	size_t first_buffer(0);
	size_t second_buffer(0);
	input_data* COMPLEX_buff(NULL);

	for (size_t i = 0; i < data_vec->size(); i++)
	{
		if (data_vec->at(i)->id == ID)
		{
			buffer = data_vec->at(i)->properties;

			buffer = delete_parentheses(buffer);
			buffer.erase(0, 1);

			if (buffer.find("B_SPLINE_SURFACE") != std::string::npos) while (buffer.find_first_of('\n') != std::string::npos)
			{
				if (buffer.find_first_of('\n') == 0) buffer.erase(0, 1);
				sub_buff = buffer.substr(0, buffer.find_first_of('\n'));

				first_buffer = sub_buff.find_first_of('(');
				second_buffer = sub_buff.find_last_of(')');

				if (first_buffer != std::string::npos)
				{
					if (((first_buffer > sub_buff.find_first_of(')')) || (sub_buff[first_buffer + 1] == '#')) && (COMPLEX_buff != NULL))
					{
						if ((sub_buff[second_buffer + 1] == ',')) COMPLEX_buff->properties += sub_buff;
						else COMPLEX_buff->properties += sub_buff.substr(0, second_buffer + 1);
					}
					else
					{
						COMPLEX_buff = new input_data;

						if (sub_buff[sub_buff.length()] != ')') COMPLEX_buff->type = sub_buff.substr(0, first_buffer);

						if (second_buffer != std::string::npos)
						{
							if (second_buffer != sub_buff.length()) COMPLEX_buff->properties = sub_buff.substr(first_buffer, sub_buff.length() - first_buffer + 1);
							else COMPLEX_buff->properties = sub_buff.substr(first_buffer, second_buffer - first_buffer + 1);
						}
						else COMPLEX_buff->properties = sub_buff;

						COMPLEX_buff->id = ID;

						COMPLEX_vec.push_back(COMPLEX_buff);
					}
				}
				else if (COMPLEX_buff != NULL) COMPLEX_buff->properties += sub_buff.substr(0, second_buffer + 1);

				buffer.erase(0, sub_buff.length());
			}

			break;

		}
	}
	return COMPLEX_vec;
}

template <class SURFACE>
std::vector<SURFACE*> File_handler::SURFACE_sorter()
{
	std::vector<ADVANCED_FACE*> input_ADVANCED_FACE = ADVANCED_FACE_sorter();

	std::vector<SURFACE*> SURFACE_vec;
	std::string buffer;
	size_t first_buffer(0);
	size_t second_buffer(0);
	unsigned long long Id_buffer(0);
	SURFACE* SURFACE_buffer;

	for (unsigned long long i = 0; i < input_ADVANCED_FACE.size(); i++)
	{
		for (unsigned long long j = 0; j < data_vec->size(); j++)
		{
			if (("class " + data_vec->at(j)->type == typeid(SURFACE).name()) && (data_vec->at(j)->id == *input_ADVANCED_FACE[i]->associated_id))
			{
				buffer = data_vec->at(j)->properties;

				buffer = delete_parentheses(buffer);

				SURFACE_buffer = new SURFACE;

				*SURFACE_buffer->smth_str1 = get_smth_str_1(buffer);

				buffer.erase(0, buffer.find_first_of(',') + 1);

				first_buffer = buffer.find_first_of('#') + 1;
				second_buffer = buffer.find_first_of(',') - first_buffer;

				Id_buffer = std::stoull(buffer.substr(first_buffer, second_buffer));
				SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(Id_buffer);

				buffer.erase(0, buffer.find_first_of(',') + 1);
				first_buffer = buffer.find_first_of(',');

				*SURFACE_buffer->smth_d1 = std::stod(buffer.substr(0, first_buffer));

				buffer.erase(0, buffer.find_first_of(',') + 1);
				first_buffer = buffer.find_first_of(',');

				if ((data_vec->at(j)->type == "CONICAL_SURFACE") || (data_vec->at(j)->type == "TOROIDAL_SURFACE"))
				{
					*SURFACE_buffer->smth_d2 = std::stod(buffer.substr(0, first_buffer));
				}

				SURFACE_vec.push_back(SURFACE_buffer);
			}
		}
	}

	return SURFACE_vec;
}

std::vector<B_SPLINE_SURFACE*> File_handler::B_SPLINE_SURFACE_sorter()
{
	std::vector<ADVANCED_FACE*> input_ADVANCED_FACE = ADVANCED_FACE_sorter();
	std::vector<input_data*> input_COMPLEX;

	std::vector<B_SPLINE_SURFACE*> B_SPLINE_SURFACE_vec;
	std::string buffer;

	for (size_t i = 0; i < input_ADVANCED_FACE.size(); i++)
	{
		for (size_t j = 0; j < data_vec->size(); j++)
		{
			if ((data_vec->at(j)->type == "COMPLEX") && (data_vec->at(j)->id == *input_ADVANCED_FACE[i]->associated_id))
			{
				input_COMPLEX = COMPLEX_sorter(data_vec->at(j)->id);

				for (size_t k = 0; k < input_COMPLEX.size(); k++)
				{
					if (input_COMPLEX[k]->type == "B_SPLINE_SURFACE")
					{
						buffer = input_COMPLEX.at(k)->properties;

						B_SPLINE_SURFACE_vec.push_back(get_B_SPLINE_SURFACE(buffer));
					}
				}

				break;

			}
		}
	}

	return B_SPLINE_SURFACE_vec;
}

File_handler::File_handler(std::string input_file_name) : input_file(new std::ifstream), data_vec(new std::vector<input_data*>), data_buffer(NULL)
	{
		input_file->open(input_file_name);
	}

File_handler::~File_handler()
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

void File_handler::get_data()
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

void File_handler::print_data()
	{
		/*-----Здесь тестируется вывод-----*/
		get_data();

		/*for (size_t i = 0; i < data_vec->size(); i++)
		{
			//std::cout << "id = " << data_vec->at(i)->id << "\ntype: " << data_vec->at(i)->type << "\nproperties: " << data_vec->at(i)->properties  << std::endl;
		} //вывод всего файла*/

		/*std::vector<CLOSED_SHELL*> va = CLOSED_SHELL_sorter();
		for (size_t i = 0; i < va.size(); i++)
		{
			std::cout << "smth_str1 = " << *va.at(i)->smth_str1 << std::endl;
			for (unsigned long long j = 0; j < *va.at(i)->ids_quantity; j++)
			{
				std::cout << va.at(i)->associated_ids[j] << " ";
			}
			std::cout << std::endl;
		}*/

		/*std::vector<ADVANCED_FACE*> vb = ADVANCED_FACE_sorter();
		for (size_t i = 0; i < vb.size(); i++)
		{
			std::cout << *vb.at(i)->smth_str1 << " ";
			for (size_t j = 0; j < vb.at(i)->associated_ids->size(); j++)
			{
				std::cout << *vb.at(i)->associated_ids->at(j) << " ";
			}
			std::cout << ", " << *vb.at(i)->associated_id << " " << *vb.at(i)->smth_str2 << std::endl;
		}*/

		/*for (size_t i = 0; i < data_vec->size(); i++)
		{
			if (data_vec->at(i)->type == "COMPLEX")
			{
				std::vector<input_data*> vd = COMPLEX_sorter(data_vec->at(i)->id);

				for (size_t j = 0; j < vd.size(); j++)
				{
					std::cout << "type = " << vd.at(j)->type << "\nproperties = " << vd.at(j)->properties << std::endl;
				}
			}
		}*/

		std::vector<CONICAL_SURFACE*> vc = SURFACE_sorter<CONICAL_SURFACE>(); //#538 и #1155
		std::cout << "Conical surfaces:" << std::endl;
		for (size_t i = 0; i < vc.size(); i++)
		{
			std::cout << *vc[i]->smth_str1 << std::endl;
			for (size_t j = 0; j < vc.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->size(); j++)
			{
				std::cout << *vc[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->type << " " << *vc[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->smth_str1 << " " << *vc[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->x << " " << *vc[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->y << " " << *vc[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->z << std::endl;
			}
			std::cout << *vc[i]->smth_d1 << " " << *vc[i]->smth_d2 << std::endl;
			std::cout << std::endl;
		}

		std::vector<TOROIDAL_SURFACE*> ve = SURFACE_sorter<TOROIDAL_SURFACE>();
		std::cout << "Toroidal surfaces:" << std::endl;
		for (size_t i = 0; i < ve.size(); i++)
		{
			std::cout << *ve[i]->smth_str1 << std::endl;
			for (size_t j = 0; j < ve.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->size(); j++)
			{
				std::cout << *ve[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->type << " " << *ve[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->smth_str1 << " " << *ve[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->x << " " << *ve[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->y << " " << *ve[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->z << std::endl;
			}
			std::cout << *ve[i]->smth_d1 << " " << *ve[i]->smth_d2 << std::endl;
			std::cout << std::endl;
		}

		std::vector<CYLINDRICAL_SURFACE*> vf = SURFACE_sorter<CYLINDRICAL_SURFACE>();
		std::cout << "Cylindrical surfaces:" << std::endl;
		for (size_t i = 0; i < vf.size(); i++)
		{
			std::cout << *vf[i]->smth_str1 << std::endl;
			for (size_t j = 0; j < vf.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->size(); j++)
			{
				std::cout << *vf[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->type << " " << *vf[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->smth_str1 << " " << *vf[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->x << " " << *vf[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->y << " " << *vf[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->z << std::endl;
			}
			std::cout << *vf[i]->smth_d1 << std::endl;
			std::cout << std::endl;
		}

		std::vector<SPHERICAL_SURFACE*> vg = SURFACE_sorter<SPHERICAL_SURFACE>();
		std::cout << "Spherical surfaces:" << std::endl;
		for (size_t i = 0; i < vg.size(); i++)
		{
			std::cout << *vg[i]->smth_str1 << std::endl;
			for (size_t j = 0; j < vg.at(i)->AXIS2_PLACEMENT_3D_data->associated_ids->size(); j++)
			{
				std::cout << *vg[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->type << " " << *vg[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->smth_str1 << " " << *vg[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->x << " " << *vg[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->y << " " << *vg[i]->AXIS2_PLACEMENT_3D_data->associated_ids->at(j)->z << std::endl;
			}
			std::cout << *vg[i]->smth_d1 << std::endl;
			std::cout << std::endl;
		}

		std::vector<B_SPLINE_SURFACE*> vh = B_SPLINE_SURFACE_sorter(); //#975, #1001, #1191 и #2056
		std::cout << "\nB-spline surfaces:" << std::endl;
		for (size_t i = 0; i < vh.size(); i++)
		{
			std::cout << *vh[i]->smth_int1 << " " << *vh[i]->smth_int2 << std::endl;

			for (size_t j = 0; j < vh[i]->associated_support_ids->size(); j++)
			{
				for (size_t k = 0; k < vh[i]->associated_support_ids->at(j)->size(); k++)
				{
					std::cout << *vh[i]->associated_support_ids->at(j)->at(k)->type << " " << *vh[i]->associated_support_ids->at(j)->at(k)->smth_str1 << " " << *vh[i]->associated_support_ids->at(j)->at(k)->x << " " << *vh[i]->associated_support_ids->at(j)->at(k)->y << " " << *vh[i]->associated_support_ids->at(j)->at(k)->z << std::endl;
				}
			}

			std::cout << *vh[i]->smth_str2 << " " << *vh[i]->smth_str3 << " " << *vh[i]->smth_str4 << " " << *vh[i]->smth_str5 << std::endl;
			std::cout << std::endl;
		}

		return;
	}