#include <iostream>
#include <map>
#include "Model.h"
bool Model::has_B_SPLINE_SURFACE(unsigned long long* ID)
{
	std::map<unsigned long long*, B_SPLINE_SURFACE*> B_SPLINE_SURFACE_map;
	B_SPLINE_SURFACE_map = *B_SPLINE_SURFACE_sorter();
	bool has_SURFACE_buff(false);
	if (B_SPLINE_SURFACE_map.find(ID) != B_SPLINE_SURFACE_map.end()) has_SURFACE_buff = true;
	return has_SURFACE_buff;
}

std::map<unsigned long long, bool>* Model::has_SURFACE(std::string SURFACE, std::vector<std::string> SUPPORTED)
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
std::vector<SURFACE*>* Model::additional_SURFACEs(unsigned long long* self_id, SURFACE* SURFACE_buffer)
{
	std::vector<SURFACE*>* SURFACE_vec(new std::vector<SURFACE*>);
	std::string SURFACE_name(typeid(SURFACE).name());
	SURFACE_name = SURFACE_name.erase(0, 6);

	std::map<unsigned long long, bool>* has_SURFACE_map(has_SURFACE(SURFACE_name));

	for (auto i = REPRESENTATION_RELATIONSHIP_vec->begin(); i != REPRESENTATION_RELATIONSHIP_vec->end(); ++i)
	{
		if (!(*i)->is_used())
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
					if (has_SURFACE_with_id((*j), self_id))
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
									assosiated_id = *(*k);

									SURFACE* SURFACE_buffer(new SURFACE(*SURFACE_buffer));
									SURFACE_buffer->AXIS2_PLACEMENT_3D_data = get_AXIS2_PLACEMENT_3D(&assosiated_id);
									SURFACE_vec->push_back(SURFACE_buffer);
								}
								(*i)->is_used(true);
							}
						}
					}
				}
			}
		}
	}

	return SURFACE_vec;
}

template <class SURFACE>
std::map<unsigned long long*, std::vector<SURFACE*>*>* Model::SURFACE_sorter()
{
	std::map<unsigned long long*, ADVANCED_FACE*>* input_ADVANCED_FACE;
	if (ADVANCED_FACE_map->first) input_ADVANCED_FACE = ADVANCED_FACE_map->second;
	else input_ADVANCED_FACE = ADVANCED_FACE_sorter();

	std::map<unsigned long long*, std::vector<SURFACE*>*>* SURFACE_map(new std::map<unsigned long long*, std::vector<SURFACE*>*>);
	std::string buffer;
	size_t first_buffer(0);
	size_t second_buffer(0);
	double* smth_d_buff;
	unsigned long long Id_buffer(0);
	SURFACE* SURFACE_buffer(NULL);
	std::vector<SURFACE*>* SURFACE_vec_buffer(new std::vector<SURFACE*>);
	unsigned long long* self_id;

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

						self_id = new unsigned long long((*k).first);

						SURFACE_vec_buffer->push_back(SURFACE_buffer);
						
						std::vector<SURFACE*> add_vec = *additional_SURFACEs<SURFACE>(self_id, SURFACE_buffer);
						for (auto p = add_vec.begin(); p != add_vec.end(); ++p)
						{
							SURFACE_vec_buffer->push_back(*p);
						}

						SURFACE_map->insert(std::make_pair(self_id, SURFACE_vec_buffer));
					}
				}
			}
		}
	}

	return SURFACE_map;
}

std::map<unsigned long long*, B_SPLINE_SURFACE*>* Model::B_SPLINE_SURFACE_sorter()
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
void Model::print_SURFACE(std::map<unsigned long long*, std::vector<SURFACE*>*>* V)
{
	for (auto i = V->begin(); i != V->end(); ++i)
	{
		std::cout << "id = " << *(*i).first << std::endl;
		for (auto p = (*i).second->begin(); p != (*i).second->end(); ++p)
		{
			std::cout << *(*p)->smth_str1 << std::endl;
			for (auto j = (*p)->AXIS2_PLACEMENT_3D_data->associated_ids->begin(); j < (*p)->AXIS2_PLACEMENT_3D_data->associated_ids->end(); ++j)
			{
				std::cout << *(*j)->type << " " << *(*j)->smth_str1 << " " << *(*j)->x << " " << *(*j)->y << " " << *(*j)->z << std::endl;
			}
			for (auto j = (*p)->smth_d.begin(); j != (*p)->smth_d.end(); ++j)
			{
				std::cout << **j << " ";
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
	return;
}

void Model::print_data(std::string CLASS)
{
	//24
	if (CLASS == "CONICAL_SURFACE")
	{
		std::cout << "\tConical surfaces:" << std::endl;
		print_SURFACE(CONICAL_SURFACE_map);
	}

	//45
	if (CLASS == "TOROIDAL_SURFACE")
	{
		std::cout << "\tToroidal surfaces:" << std::endl;
		print_SURFACE(TOROIDAL_SURFACE_map);
	}

	//204
	if (CLASS == "CYLINDRICAL_SURFACE")
	{
		std::cout << "\tCylindrical surfaces:" << std::endl;
		print_SURFACE(CYLINDRICAL_SURFACE_map);
	}

	//4
	if (CLASS == "SPHERICAL_SURFACE")
	{
		std::cout << "\tSpherical surfaces:" << std::endl;
		print_SURFACE(SPHERICAL_SURFACE_map);
	}

	//4
	if (CLASS == "B_SPLINE_SURFACE")
	{
		//#975, #1001, #1191 è #2056
		std::cout << "\n\tB-spline surfaces:" << std::endl;
		for (auto i = B_SPLINE_SURFACE_map->begin(); i != B_SPLINE_SURFACE_map->end(); ++i)
		{
			std::cout << "id = " << *(*i).first << std::endl;
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

Model::Model(std::string input_file_name) :
	Data_handler(input_file_name),
	CONICAL_SURFACE_map(new std::map<unsigned long long*, std::vector<CONICAL_SURFACE*>*>),
	SPHERICAL_SURFACE_map(new std::map<unsigned long long*, std::vector<SPHERICAL_SURFACE*>*>),
	CYLINDRICAL_SURFACE_map(new std::map<unsigned long long*, std::vector<CYLINDRICAL_SURFACE*>*>),
	TOROIDAL_SURFACE_map(new std::map<unsigned long long*, std::vector<TOROIDAL_SURFACE*>*>),
	B_SPLINE_SURFACE_map(new std::map<unsigned long long*, B_SPLINE_SURFACE*>)
{
	REPRESENTATION_RELATIONSHIP_vec = REPRESENTATION_RELATIONSHIP_sorter();
	ADVANCED_BREP_SHAPE_REPRESENTATION_map = ADVANCED_BREP_SHAPE_REPRESENTATION_sorter();
}

Model::~Model()
{
	delete B_SPLINE_SURFACE_map;
	delete TOROIDAL_SURFACE_map;
	delete CYLINDRICAL_SURFACE_map;
	delete SPHERICAL_SURFACE_map;
	delete CONICAL_SURFACE_map;
}

void Model::construct()
{
	CONICAL_SURFACE_map = SURFACE_sorter<CONICAL_SURFACE>();
	SPHERICAL_SURFACE_map = SURFACE_sorter<SPHERICAL_SURFACE>();
	CYLINDRICAL_SURFACE_map = SURFACE_sorter<CYLINDRICAL_SURFACE>();
	TOROIDAL_SURFACE_map = SURFACE_sorter<TOROIDAL_SURFACE>();
	B_SPLINE_SURFACE_map = B_SPLINE_SURFACE_sorter();

	return;
}