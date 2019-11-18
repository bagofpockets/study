#include <iostream>
#include <fstream>
#include <iterator>
#include "Secondary_funcs.h"
#include "File_handler.h"

struct input_data
{
	std::map<unsigned long long, std::string> data;
	std::string type;
};

/*-----Вспомогательные функции-----*/

Support_class* File_handler::get_support_object(unsigned long long* ID)
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

AXIS2_PLACEMENT_3D* File_handler::get_AXIS2_PLACEMENT_3D(unsigned long long* ID)
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

B_SPLINE_SURFACE* File_handler::get_B_SPLINE_SURFACE(const std::string* buff)
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

REPRESENTATION_RELATIONSHIP* File_handler::get_REPRESENTATION_RELATIONSHIP(const std::string* buff)
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

bool File_handler::has_B_SPLINE_SURFACE(unsigned long long* ID)
{
	std::map<unsigned long long*, B_SPLINE_SURFACE*> B_SPLINE_SURFACE_map;
	B_SPLINE_SURFACE_map = *B_SPLINE_SURFACE_sorter();
	bool has_SURFACE_buff(false);
	if (B_SPLINE_SURFACE_map.find(ID) != B_SPLINE_SURFACE_map.end()) has_SURFACE_buff = true;
	return has_SURFACE_buff;
}

std::map<unsigned long long, bool>* File_handler::has_SURFACE(std::string SURFACE, std::vector<std::string> SUPPORTED)
{
	std::map<unsigned long long, bool>* has_SURFACE_vec(new std::map<unsigned long long, bool>);
	unsigned long long ID_buff;
	bool has_SURFACE_buff;
	for (auto i = MANIFOLD_SOLID_BREP_map->second->begin(); i != MANIFOLD_SOLID_BREP_map->second->end(); ++i)
	{
		ID_buff = *(*i).first;
		has_SURFACE_buff = false;
		for (auto j = CLOSED_SHELL_map->second->begin(); j != CLOSED_SHELL_map->second->end(); ++j)
		{
			if (*(*j).first == *(*i).second->associated_id)
			{
				for (auto k = (*j).second->associated_ids->begin(); k != (*j).second->associated_ids->end(); ++k)
				{
					for (auto l = ADVANCED_FACE_map->second->begin(); l != ADVANCED_FACE_map->second->end(); ++l)
					{
						if (*(*l).first == *(*k))
						{
							for (auto m = data_vec->begin(); m != data_vec->end(); ++m)
							{
								if (SURFACE == "NONE")
								{
									for (auto n = SUPPORTED.begin(); n != SUPPORTED.end(); ++n)
									{
										if (((*n) == "B_SPLINE_SURFACE") && ((*m)->type == "COMPLEX"))
										{
											has_SURFACE_buff = has_B_SPLINE_SURFACE((*l).second->associated_id);
											if (has_SURFACE_buff) break;
										}
										else if ((*m)->type == (*n))
										{
											for (auto p = (*m)->data.begin(); p != (*m)->data.end(); ++p)
											{
												if ((*p).first == *(*l).second->associated_id)
												{
													has_SURFACE_buff = true;
													break;
												}
											}
											if (has_SURFACE_buff) break;
										}
									}
								}
								else
								{
									if ((SURFACE == "B_SPLINE_SURFACE") && ((*m)->type == "COMPLEX"))
									{
										has_SURFACE_buff = has_B_SPLINE_SURFACE((*l).second->associated_id);
										if (has_SURFACE_buff) break;
									}
									else if ((*m)->type == SURFACE)
									{
										for (auto p = (*m)->data.begin(); p != (*m)->data.end(); ++p)
										{
											if ((*p).first == *(*l).second->associated_id)
											{
												has_SURFACE_buff = true;
												break;
											}
										}
										if (has_SURFACE_buff) break;
									}
								}
								if (has_SURFACE_buff) break;
							}
						}
					}
					if (has_SURFACE_buff) break;
				}
				break;
			}
		}
		has_SURFACE_vec->insert(std::make_pair(ID_buff, has_SURFACE_buff));
	}
	
	return has_SURFACE_vec;
}

template <class SURFACE>
std::vector<SURFACE*>* File_handler::SURFACE_addition(SURFACE* SURFACE_buffer)
{
	std::vector<SURFACE*>* SURFACE_vec(new std::vector<SURFACE*>);
	std::string SURFACE_name(typeid(SURFACE).name());
	SURFACE_name = SURFACE_name.erase(0, 6);

	std::vector<REPRESENTATION_RELATIONSHIP*>* REPRESENTATION_RELATIONSHIP_vec(REPRESENTATION_RELATIONSHIP_sorter());
	std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* ADVANCED_BREP_SHAPE_REPRESENTATION_map(ADVANCED_BREP_SHAPE_REPRESENTATION_sorter());
	std::map<unsigned long long, bool>* has_SURFACE_map(has_SURFACE(SURFACE_name));

	for (auto i = REPRESENTATION_RELATIONSHIP_vec->begin(); i != REPRESENTATION_RELATIONSHIP_vec->end(); ++i)
	{
		unsigned long long assosiated_id = *(*i)->assosiated_ids->second;
		auto id = ADVANCED_BREP_SHAPE_REPRESENTATION_map->end();
		
		for (auto k = ADVANCED_BREP_SHAPE_REPRESENTATION_map->begin(); k != ADVANCED_BREP_SHAPE_REPRESENTATION_map->end(); ++k)
		{
			if (*(*k).first == assosiated_id)
			{
				id = k;
				break;
			}
		}

		if (id != ADVANCED_BREP_SHAPE_REPRESENTATION_map->end())
		{
			for (auto j = (*id).second->associated_ids->begin(); j != (*id).second->associated_ids->end(); ++j)
			{
				auto has_SURFACE(has_SURFACE_map->find(*(*j)));
				if (has_SURFACE != has_SURFACE_map->end())
				{
					if ((*has_SURFACE).second)
					{
						assosiated_id = *(*i)->assosiated_ids->first;
						auto tmp = ADVANCED_BREP_SHAPE_REPRESENTATION_map->end();
						for (auto k = ADVANCED_BREP_SHAPE_REPRESENTATION_map->begin(); k != ADVANCED_BREP_SHAPE_REPRESENTATION_map->end(); ++k)
						{
							if (*(*k).first == assosiated_id)
							{
								tmp = k;
								break;
							}
						}
						for (auto k = (*tmp).second->associated_ids->begin(); k != (*tmp).second->associated_ids->end(); ++k)
						{
							SURFACE* SURFACE_buffer(new SURFACE(*SURFACE_buffer));
							assosiated_id = *(*k);
							SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(&assosiated_id);
							SURFACE_vec->push_back(SURFACE_buffer);
						}
					}
				}
			}
		}
	}

	return SURFACE_vec;
}

/*-----Сортировщики-----*/

std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* File_handler::MANIFOLD_SOLID_BREP_sorter()
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

std::map<unsigned long long*, CLOSED_SHELL*>* File_handler::CLOSED_SHELL_sorter(std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP)
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

std::map<unsigned long long*, ADVANCED_FACE*>* File_handler::ADVANCED_FACE_sorter(std::map<unsigned long long*, CLOSED_SHELL*>* input_CLOSED_SHELL, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP)
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

std::vector<input_data*>* File_handler::COMPLEX_sorter(const unsigned long long* ID, const std::string SURFACE)
{
	std::vector<input_data*>* COMPLEX_vec(new std::vector<input_data*>);
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

std::vector<REPRESENTATION_RELATIONSHIP*>* File_handler::REPRESENTATION_RELATIONSHIP_sorter()
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

std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* File_handler::ADVANCED_BREP_SHAPE_REPRESENTATION_sorter()
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

template <class SURFACE>
std::vector<SURFACE*>* File_handler::SURFACE_sorter()
{
	std::map<unsigned long long*, ADVANCED_FACE*>* input_ADVANCED_FACE;
	if (ADVANCED_FACE_map->first) input_ADVANCED_FACE = ADVANCED_FACE_map->second;
	else input_ADVANCED_FACE = ADVANCED_FACE_sorter();

	std::vector<SURFACE*>* SURFACE_vec(new std::vector<SURFACE*>);
	std::string buffer;
	size_t first_buffer(0);
	size_t second_buffer(0);
	double* smth_d_buff;
	unsigned long long Id_buffer(0);
	SURFACE* SURFACE_buffer(NULL);

	for (auto i = input_ADVANCED_FACE->begin(); i != input_ADVANCED_FACE->end(); ++i)
	{
		for (auto j = data_vec->begin(); j != data_vec->end(); ++j)
		{
			if ("class " + (*j)->type == typeid(SURFACE).name())
			{
				for (auto k = (*j)->data.begin(); k != (*j)->data.end(); ++k)
				{
					if ((*k).first == *(*i).second->associated_id)
					{
						buffer = (*k).second;

						buffer = *delete_parentheses(&buffer);

						SURFACE_buffer = new SURFACE;

						*SURFACE_buffer->smth_str1 = get_smth_str_1(&buffer);

						buffer.erase(0, buffer.find_first_of(',') + 1);

						first_buffer = buffer.find_first_of('#') + 1;
						second_buffer = buffer.find_first_of(',') - first_buffer;

						Id_buffer = std::stoull(buffer.substr(first_buffer, second_buffer));
						SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(&Id_buffer);

						buffer.erase(0, buffer.find_first_of(',') + 1);
						first_buffer = buffer.find_first_of(',');

						smth_d_buff = new double(std::stod(buffer.substr(0, first_buffer)));
						SURFACE_buffer->smth_d.push_back(smth_d_buff);

						buffer.erase(0, buffer.find_first_of(',') + 1);
						first_buffer = buffer.find_first_of(',');

						if (((*j)->type == "CONICAL_SURFACE") || ((*j)->type == "TOROIDAL_SURFACE"))
						{
							smth_d_buff = new double(std::stod(buffer.substr(0, first_buffer)));
							SURFACE_buffer->smth_d.push_back(smth_d_buff);
						}

						SURFACE_vec->push_back(SURFACE_buffer);

						std::vector<SURFACE*>* tmp_vec = SURFACE_addition<SURFACE>(SURFACE_buffer);
						for (auto p = tmp_vec->begin(); p != tmp_vec->end(); ++p)
						{
							SURFACE_vec->push_back(*p);
						}
						delete tmp_vec;
					}
				}
			}
		}
	}

	return SURFACE_vec;
}

std::map<unsigned long long*, B_SPLINE_SURFACE*>* File_handler::B_SPLINE_SURFACE_sorter()
{
	std::map<unsigned long long*, ADVANCED_FACE*>* input_ADVANCED_FACE;
	if (ADVANCED_FACE_map->first) input_ADVANCED_FACE = ADVANCED_FACE_map->second;
	else input_ADVANCED_FACE = ADVANCED_FACE_sorter();
	std::vector<input_data*> input_COMPLEX;

	std::map<unsigned long long*, B_SPLINE_SURFACE*>* B_SPLINE_SURFACE_map(new std::map<unsigned long long*, B_SPLINE_SURFACE*>);
	B_SPLINE_SURFACE* B_SPLINE_SURFACE_buff;
	unsigned long long* self_id;
	std::string buffer;

	for (auto i = input_ADVANCED_FACE->begin(); i != input_ADVANCED_FACE->end(); ++i)
	{
		for (auto j = data_vec->begin(); j != data_vec->end(); ++j)
		{
			if ((*j)->type == "COMPLEX")
			{
				for (auto k = (*j)->data.begin(); k != (*j)->data.end(); ++k)
				{
					if ((*k).first == *(*i).second->associated_id)
					{
						input_COMPLEX = *COMPLEX_sorter(&(*k).first, "B_SPLINE_SURFACE");

						for (auto l = input_COMPLEX.begin(); l != input_COMPLEX.end(); ++l)
						{
							if ((*l)->type == "B_SPLINE_SURFACE")
							{
								for (auto m = (*l)->data.begin(); m != (*l)->data.end(); ++m)
								{
									buffer = (*m).second;

									B_SPLINE_SURFACE_buff = get_B_SPLINE_SURFACE(&buffer);
									self_id = new unsigned long long((*m).first);

									B_SPLINE_SURFACE_map->insert(std::make_pair(self_id, B_SPLINE_SURFACE_buff));
								}
							}
						}

						break;
					}
				}
				break;
			}
		}
	}

	return B_SPLINE_SURFACE_map;
}

template <class SURFACE>
void File_handler::print_SURFACE(std::vector<SURFACE*> V)
{
	for (auto i = V.begin(); i != V.end(); ++i)
	{
		std::cout << *(*i)->smth_str1 << std::endl;
		for (auto j = (*i)->AXIS2_PLACEMENT_3D_data->associated_ids->begin(); j < (*i)->AXIS2_PLACEMENT_3D_data->associated_ids->end(); ++j)
		{
			std::cout << *(*j)->type << " " << *(*j)->smth_str1 << " " << *(*j)->x << " " << *(*j)->y << " " << *(*j)->z << std::endl;
		}
		for (auto j = (*i)->smth_d.begin(); j != (*i)->smth_d.end(); ++j)
		{
			std::cout << **j << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	return;
}

File_handler::File_handler(std::string input_file_name) : 
	input_file(new std::ifstream),
	data_vec(new std::vector<input_data*>),
	data_buffer(NULL),
	MANIFOLD_SOLID_BREP_map(new std::pair<bool, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>*>(false, new std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>)),
	CLOSED_SHELL_map(new std::pair<bool, std::map<unsigned long long*, CLOSED_SHELL*>*>(false, new std::map<unsigned long long*, CLOSED_SHELL*>)),
	ADVANCED_FACE_map(new std::pair<bool, std::map<unsigned long long*, ADVANCED_FACE*>*>(false, new std::map<unsigned long long*, ADVANCED_FACE*>))
	{
		input_file->open(input_file_name);
	}

File_handler::~File_handler()
	{
		input_file->close();

		for (auto i = data_vec->begin(); i != data_vec->end(); ++i)
		{
			delete (*i);
			*i = 0;
		}
		delete data_vec;

		delete MANIFOLD_SOLID_BREP_map;
		delete CLOSED_SHELL_map;
		delete ADVANCED_FACE_map;

		delete input_file;
	}

void File_handler::get_data()
{
	if (!initialized)
	{
		if (input_file->is_open())
		{
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

			initialized = true;
			return;
		}
		else
		{
			std::cout << "Can't open file" << std::endl;
			return;
		}
	}
	else return;
}

void File_handler::print_data(std::string CLASS)
	{
		/*-----Здесь тестируется вывод-----*/
		get_data();
		
		//24
		if (CLASS == "CONICAL_SURFACE")
		{
			std::vector<CONICAL_SURFACE*> v0 = *SURFACE_sorter<CONICAL_SURFACE>(); //#538 и #1155
			std::cout << "\tConical surfaces:" << std::endl;
			print_SURFACE(v0);
		}

		//45
		if (CLASS == "TOROIDAL_SURFACE")
		{
			std::vector<TOROIDAL_SURFACE*> v1 = *SURFACE_sorter<TOROIDAL_SURFACE>();
			std::cout << "\tToroidal surfaces:" << std::endl;
			print_SURFACE(v1);
		}

		//204
		if (CLASS == "CYLINDRICAL_SURFACE")
		{
			std::vector<CYLINDRICAL_SURFACE*> v2 = *SURFACE_sorter<CYLINDRICAL_SURFACE>();
			std::cout << "\tCylindrical surfaces:" << std::endl;
			print_SURFACE(v2);
		}

		//4
		if (CLASS == "SPHERICAL_SURFACE")
		{
			std::vector<SPHERICAL_SURFACE*> v3 = *SURFACE_sorter<SPHERICAL_SURFACE>();
			std::cout << "\tSpherical surfaces:" << std::endl;
			print_SURFACE(v3);
		}
		
		//4
		if (CLASS == "B_SPLINE_SURFACE")
		{
			std::map<unsigned long long*, B_SPLINE_SURFACE*> v4 = *B_SPLINE_SURFACE_sorter(); //#975, #1001, #1191 и #2056
			std::cout << "\n\tB-spline surfaces:" << std::endl;
			for (auto i = v4.begin(); i != v4.end(); ++i)
			{
				std::cout << *(*i).second->smth_int1 << " " << *(*i).second->smth_int2 << std::endl;

				for (auto j = (*i).second->associated_support_ids->begin(); j != (*i).second->associated_support_ids->end(); ++j)
				{
					for (auto k = (*j)->begin(); k != (*j)->end(); ++k)
					{
						std::cout << *(*k)->type << " " << *(*k)->smth_str1 << " " << *(*k)->x << " " << *(*k)->y << " " << *(*k)->z << std::endl;
					}
				}

				std::cout << *(*i).second->smth_str2 << " " << *(*i).second->smth_str3 << " " << *(*i).second->smth_str4 << " " << *(*i).second->smth_str5 << std::endl;
				std::cout << std::endl;
			}
		}

		return;
	}