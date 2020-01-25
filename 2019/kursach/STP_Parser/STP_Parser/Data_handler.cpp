#include "Data_handler.h"

/*-----Вспомогательные функции-----*/

Support_class* Data_handler::get_support_object(unsigned long long* ID)
{
	Support_class* support_buff(new Support_class);
	std::string buffer;
	size_t first_buffer(0);
	size_t second_buffer(0);

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		if ((((*i)->type == "CARTESIAN_POINT") || ((*i)->type == "DIRECTION")) && ((*i)->data.find(*ID) != (*i)->data.end()))
		{
			support_buff->type = &(*i)->type;

			buffer = (*i)->data[*ID];

			buffer = *delete_parentheses(&buffer);

			*support_buff->smth_str1 = get_smth_str_1(&buffer);

			buffer = get_parentheses_content(&buffer);
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

AXIS2_PLACEMENT_3D* Data_handler::get_AXIS2_PLACEMENT_3D(unsigned long long* ID)
{
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_buff(new AXIS2_PLACEMENT_3D);
	std::string buffer;
	size_t first_buffer(0);
	size_t second_buffer(0);
	unsigned long long N_buffer(0);
	unsigned long long Id_buffer(0);

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		if ((*i)->type == "AXIS2_PLACEMENT_3D")
		{
			buffer = (*i)->data[*ID];

			buffer = *delete_parentheses(&buffer);

			N_buffer = count_sharps(&buffer);

			*AXIS2_PLACEMENT_3D_buff->smth_str1 = get_smth_str_1(&buffer);

			buffer.erase(0, buffer.find_first_of('#'));

			for (unsigned long long k = 0; k < N_buffer; k++)
			{
				buffer.erase(0, 1);
				second_buffer = buffer.find_first_of(',');

				Id_buffer = std::stoull(buffer.substr(0, second_buffer));

				for (auto l = data_vec->begin(); l != data_vec->end(); ++l)
				{
					if (((*l)->type == "CARTESIAN_POINT") || ((*l)->type == "DIRECTION"))
					{
						for (auto m = (*l)->data.begin(); m != (*l)->data.end(); ++m)
						{
							if ((*m).first == Id_buffer)
							{
								AXIS2_PLACEMENT_3D_buff->associated_ids->push_back(get_support_object(&Id_buffer));

								break;
							}
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

B_SPLINE_SURFACE* Data_handler::get_B_SPLINE_SURFACE(const std::string* buff)
{
	B_SPLINE_SURFACE* B_SPLINE_SURFACE_buff(new B_SPLINE_SURFACE);
	std::string buffer(*buff), sub_buff, ids_buff;
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
		N_buffer = count_sharps(&ids_buff);
		sub_buff.erase(0, third_buffer + 1);

		associated_ids_buff = *get_associated_ids(&ids_buff, &N_buffer);

		support_class_vec_buff = new std::vector<Support_class*>;

		for (auto i = associated_ids_buff.begin(); i != associated_ids_buff.end(); ++i)
		{
			support_class_vec_buff->push_back(get_support_object(*i));
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

REPRESENTATION_RELATIONSHIP* Data_handler::get_REPRESENTATION_RELATIONSHIP(const std::string* buff)
{
	REPRESENTATION_RELATIONSHIP* REPRESENTATION_RELATIONSHIP_buff(new REPRESENTATION_RELATIONSHIP);
	std::string buffer(*buff), sub_buff_first, sub_buff_second;
	unsigned long long id_buff_first, id_buff_second;
	size_t second_buffer(0);

	buffer = *delete_parentheses(&buffer);

	second_buffer = buffer.find_first_of(',');
	sub_buff_first = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	sub_buff_second = buffer.substr(0, second_buffer);
	buffer.erase(0, second_buffer + 1);

	*REPRESENTATION_RELATIONSHIP_buff->smth_str = std::make_pair(new std::string(sub_buff_first), new std::string(sub_buff_second));

	second_buffer = buffer.find_first_of(',');
	id_buff_first = std::stoull(buffer.substr(1, second_buffer));
	buffer.erase(0, second_buffer + 1);

	second_buffer = buffer.find_first_of(',');
	id_buff_second = std::stoull(buffer.substr(1, second_buffer));
	buffer.erase(0, second_buffer + 1);

	*REPRESENTATION_RELATIONSHIP_buff->assosiated_ids = std::make_pair(new unsigned long long(id_buff_first), new unsigned long long(id_buff_second));

	return REPRESENTATION_RELATIONSHIP_buff;
}

bool Data_handler::has_SURFACE_with_id(unsigned long long *MANIFOLD_ID, unsigned long long* ID)
{
	bool has_SURFACE_with_id(false);

	for (auto i = MANIFOLD_SOLID_BREP_map->second->begin(); i != MANIFOLD_SOLID_BREP_map->second->end(); ++i)
	{
		if (*(*i).first == *MANIFOLD_ID)
		{
			for (auto j = CLOSED_SHELL_map->second->begin(); j != CLOSED_SHELL_map->second->end(); ++j)
			{
				if (*(*j).first == *(*i).second->associated_id)
				{
					for (auto q = (*j).second->associated_ids->begin(); q != (*j).second->associated_ids->end(); ++q)
					{
						for (auto k = ADVANCED_FACE_map->second->begin(); k != ADVANCED_FACE_map->second->end(); ++k)
						{
							if ((*(*k).first == *(*q)) && (*(*k).second->associated_id == *ID))
							{
								has_SURFACE_with_id = true;
								return has_SURFACE_with_id;
							}
						}
					}
				}
			}
		}
	}
	return has_SURFACE_with_id;
}

/*-----Сортировщики-----*/

std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* Data_handler::MANIFOLD_SOLID_BREP_sorter()
{
	if (this->MANIFOLD_SOLID_BREP_map->first) return this->MANIFOLD_SOLID_BREP_map->second;
	else
	{
		std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* MANIFOLD_SOLID_BREP_map(this->MANIFOLD_SOLID_BREP_map->second);
		std::string buffer;
		size_t first_buffer(0);
		unsigned long long* self_id;
		MANIFOLD_SOLID_BREP* MANIFOLD_SOLID_BREP_buffer;

		for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
		{
			if ((*i)->type == "MANIFOLD_SOLID_BREP")
			{
				for (auto j = (*i)->data.begin(); j != (*i)->data.end(); ++j)
				{
					buffer = (*j).second;

					buffer = *delete_parentheses(&buffer);

					MANIFOLD_SOLID_BREP_buffer = new MANIFOLD_SOLID_BREP;

					self_id = new unsigned long long((*j).first);
					*MANIFOLD_SOLID_BREP_buffer->smth_str1 = get_smth_str_1(&buffer);

					first_buffer = buffer.find_first_of('#');
					buffer.erase(0, first_buffer + 1);

					*MANIFOLD_SOLID_BREP_buffer->associated_id = std::stoull(buffer);

					MANIFOLD_SOLID_BREP_map->insert(std::make_pair(self_id, MANIFOLD_SOLID_BREP_buffer));
				}
				break;
			}
		}

		this->MANIFOLD_SOLID_BREP_map->first = true;
		this->MANIFOLD_SOLID_BREP_map->second = MANIFOLD_SOLID_BREP_map;
		return MANIFOLD_SOLID_BREP_map;
	}
}

std::map<unsigned long long*, CLOSED_SHELL*>* Data_handler::CLOSED_SHELL_sorter(std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP)
{
	if (this->CLOSED_SHELL_map->first) return this->CLOSED_SHELL_map->second;
	else
	{
		if (input_MANIFOLD_SOLID_BREP == NULL) input_MANIFOLD_SOLID_BREP = MANIFOLD_SOLID_BREP_sorter();

		std::map<unsigned long long*, CLOSED_SHELL*>* CLOSED_SHELL_map(this->CLOSED_SHELL_map->second);
		std::string buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long N_buffer(0);
		unsigned long long* self_id;
		CLOSED_SHELL* CLOSED_SHELL_buffer;

		for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
		{
			if ((*i)->type == "CLOSED_SHELL")
			{
				for (auto j = input_MANIFOLD_SOLID_BREP->begin(); j != input_MANIFOLD_SOLID_BREP->end(); ++j)
				{
					buffer = (*i)->data[*(*j).second->associated_id];
					N_buffer = count_sharps(&buffer);

					buffer = *delete_parentheses(&buffer);

					CLOSED_SHELL_buffer = new CLOSED_SHELL;

					self_id = new unsigned long long(*(*j).second->associated_id);
					*CLOSED_SHELL_buffer->smth_str1 = get_smth_str_1(&buffer);

					first_buffer = buffer.find_first_of('\'');
					second_buffer = buffer.find_first_of('(') - first_buffer;

					buffer.erase(first_buffer, second_buffer + 1);
					buffer.pop_back();

					CLOSED_SHELL_buffer->associated_ids = get_associated_ids(&buffer, &N_buffer);

					CLOSED_SHELL_map->insert(std::make_pair(self_id, CLOSED_SHELL_buffer));

				}
				break;
			}
		}

		this->CLOSED_SHELL_map->first = true;
		this->CLOSED_SHELL_map->second = CLOSED_SHELL_map;
		return CLOSED_SHELL_map;
	}
}

std::map<unsigned long long*, ADVANCED_FACE*>* Data_handler::ADVANCED_FACE_sorter(std::map<unsigned long long*, CLOSED_SHELL*>* input_CLOSED_SHELL, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP)
{
	if (this->ADVANCED_FACE_map->first) return this->ADVANCED_FACE_map->second;
	else
	{
		if (input_MANIFOLD_SOLID_BREP == NULL) input_CLOSED_SHELL = CLOSED_SHELL_sorter();
		else if (input_CLOSED_SHELL == NULL) input_CLOSED_SHELL = CLOSED_SHELL_sorter(input_MANIFOLD_SOLID_BREP);

		std::map<unsigned long long*, ADVANCED_FACE*>* ADVANCED_FACE_map(this->ADVANCED_FACE_map->second);
		std::string buffer;
		std::string ids_buffer;
		size_t first_buffer(0);
		size_t second_buffer(0);
		unsigned long long N_buffer(0);
		unsigned long long* self_id;
		ADVANCED_FACE* ADVANCED_FACE_buffer;


		for (auto k = data_vec->begin(); k != data_vec->end(); ++k)
		{
			if ((*k)->type == "ADVANCED_FACE")
			{
				for (auto i = input_CLOSED_SHELL->begin(); i != input_CLOSED_SHELL->end(); ++i)
				{
					for (auto j = (*i).second->associated_ids->begin(); j != (*i).second->associated_ids->end(); ++j)
					{
						buffer = (*k)->data[*(*j)];

						buffer = *delete_parentheses(&buffer);

						N_buffer = count_sharps(&get_parentheses_content(&buffer));

						ADVANCED_FACE_buffer = new ADVANCED_FACE;

						self_id = new unsigned long long(*(*j));
						*ADVANCED_FACE_buffer->smth_str1 = get_smth_str_1(&buffer);

						ids_buffer = get_parentheses_content(&buffer);
						*ADVANCED_FACE_buffer->associated_ids = *get_associated_ids(&ids_buffer, &N_buffer);

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

						ADVANCED_FACE_map->insert(std::make_pair(self_id, ADVANCED_FACE_buffer));

					}
				}
				break;
			}
		}

		this->ADVANCED_FACE_map->first = true;
		this->ADVANCED_FACE_map->second = ADVANCED_FACE_map;
		return ADVANCED_FACE_map;
	}
}

std::vector<File_handler::input_data*>* Data_handler::COMPLEX_sorter(const unsigned long long* ID, const std::string SURFACE)
{
	std::vector<input_data*>* COMPLEX_vec(new std::vector<input_data*>);
	input_data* data_buffer(NULL);
	std::string buffer, sub_buff, properties;
	size_t first_buffer(0);
	size_t second_buffer(0);

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		if ((*i)->type == "COMPLEX")
		{
			buffer = (*i)->data[*ID];

			buffer = *delete_parentheses(&buffer);
			buffer.erase(0, 1);

			if (buffer.find(SURFACE) != std::string::npos) while (buffer.find_first_of('\n') != std::string::npos)
			{
				if (buffer.find_first_of('\n') == 0) buffer.erase(0, 1);
				sub_buff = buffer.substr(0, buffer.find_first_of('\n'));

				first_buffer = sub_buff.find_first_of('(');
				second_buffer = sub_buff.find_last_of(')');

				if (first_buffer != std::string::npos)
				{
					if ((first_buffer > sub_buff.find_first_of(')')) || ((sub_buff[first_buffer + 1] == '#') && (first_buffer != sub_buff.find_last_of('('))))
					{
						if ((sub_buff[second_buffer + 1] == ',')) properties += sub_buff;
						else data_buffer->data[*ID] += sub_buff.substr(0, second_buffer + 1);
					}
					else
					{
						data_buffer = new input_data;

						if (sub_buff[sub_buff.length()] != ')') data_buffer->type = sub_buff.substr(0, first_buffer);

						if (second_buffer != std::string::npos)
						{
							if (second_buffer != sub_buff.length()) properties = sub_buff.substr(first_buffer, sub_buff.length() - first_buffer + 1);
							else properties = sub_buff.substr(first_buffer, second_buffer - first_buffer + 1);
						}
						else properties = sub_buff;

						data_buffer->data.insert(std::pair<unsigned long long, std::string>(*ID, properties));

						COMPLEX_vec->push_back(data_buffer);
					}
				}
				else data_buffer->data[*ID] += sub_buff.substr(0, second_buffer + 1);

				buffer.erase(0, sub_buff.length());
			}

			break;
		}
	}
	return COMPLEX_vec;
}

std::vector<REPRESENTATION_RELATIONSHIP*>* Data_handler::REPRESENTATION_RELATIONSHIP_sorter()
{
	std::vector<REPRESENTATION_RELATIONSHIP*>* REPRESENTATION_RELATIONSHIP_vec(new std::vector<REPRESENTATION_RELATIONSHIP*>);
	std::vector<input_data*> input_COMPLEX;

	std::string buffer;
	REPRESENTATION_RELATIONSHIP* REPRESENTATION_RELATIONSHIP_buffer;

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		if ((*i)->type == "COMPLEX")
		{
			for (auto j = (*i)->data.begin(); j != (*i)->data.end(); ++j)
			{
				if ((*j).second.find("REPRESENTATION_RELATIONSHIP") != std::string::npos)
				{
					input_COMPLEX = *COMPLEX_sorter(&(*j).first, "REPRESENTATION_RELATIONSHIP");

					for (auto l = input_COMPLEX.begin(); l != input_COMPLEX.end(); ++l)
					{
						if ((*l)->type == "REPRESENTATION_RELATIONSHIP")
						{
							for (auto m = (*l)->data.begin(); m != (*l)->data.end(); ++m)
							{
								buffer = (*m).second;

								REPRESENTATION_RELATIONSHIP_buffer = get_REPRESENTATION_RELATIONSHIP(&buffer);

								REPRESENTATION_RELATIONSHIP_vec->push_back(REPRESENTATION_RELATIONSHIP_buffer);
							}
						}
					}
				}
			}
			break;
		}
	}

	return REPRESENTATION_RELATIONSHIP_vec;
}

std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* Data_handler::ADVANCED_BREP_SHAPE_REPRESENTATION_sorter()
{
	std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* ADVANCED_BREP_SHAPE_REPRESENTATION_map(new std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>);
	std::string buffer, sub_buff;
	size_t first_buffer(0);
	size_t second_buffer(0);
	unsigned long long N_buffer(0);
	unsigned long long* self_id;
	ADVANCED_BREP_SHAPE_REPRESENTATION* ADVANCED_BREP_SHAPE_REPRESENTATION_buffer;

	for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
	{
		if ((*i)->type == "ADVANCED_BREP_SHAPE_REPRESENTATION")
		{
			for (auto j = (*i)->data.begin(); j != (*i)->data.end(); ++j)
			{
				buffer = (*j).second;

				buffer = *delete_parentheses(&buffer);

				ADVANCED_BREP_SHAPE_REPRESENTATION_buffer = new ADVANCED_BREP_SHAPE_REPRESENTATION;

				self_id = new unsigned long long((*j).first);
				*ADVANCED_BREP_SHAPE_REPRESENTATION_buffer->smth_str1 = get_smth_str_1(&buffer);

				first_buffer = buffer.find_first_of('(') + 1;
				second_buffer = buffer.find_last_of(')') - first_buffer;

				sub_buff = buffer.substr(first_buffer, second_buffer);
				N_buffer = count_sharps(&sub_buff);

				ADVANCED_BREP_SHAPE_REPRESENTATION_buffer->associated_ids = get_associated_ids(&sub_buff, &N_buffer);

				buffer.erase(0, buffer.find_last_of('#') + 1);

				*ADVANCED_BREP_SHAPE_REPRESENTATION_buffer->CONTEXT_id = std::stoull(buffer);

				ADVANCED_BREP_SHAPE_REPRESENTATION_map->insert(std::make_pair(self_id, ADVANCED_BREP_SHAPE_REPRESENTATION_buffer));
			}
			break;
		}
	}

	return ADVANCED_BREP_SHAPE_REPRESENTATION_map;
};

Data_handler::Data_handler(std::string input_file_name) :
	File_handler(input_file_name),
	added_IDs(new std::map<unsigned long long*, bool>),
	REPRESENTATION_RELATIONSHIP_vec(new std::vector<REPRESENTATION_RELATIONSHIP*>),
	ADVANCED_BREP_SHAPE_REPRESENTATION_map(new std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>),
	MANIFOLD_SOLID_BREP_map(new std::pair<bool, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>*>(false, new std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>)),
	CLOSED_SHELL_map(new std::pair<bool, std::map<unsigned long long*, CLOSED_SHELL*>*>(false, new std::map<unsigned long long*, CLOSED_SHELL*>)),
	ADVANCED_FACE_map(new std::pair<bool, std::map<unsigned long long*, ADVANCED_FACE*>*>(false, new std::map<unsigned long long*, ADVANCED_FACE*>))
{
	get_data();
}

Data_handler::~Data_handler()
{
	delete added_IDs;
	delete REPRESENTATION_RELATIONSHIP_vec;
	delete ADVANCED_BREP_SHAPE_REPRESENTATION_map;
	delete MANIFOLD_SOLID_BREP_map;
	delete CLOSED_SHELL_map;
	delete ADVANCED_FACE_map;
}