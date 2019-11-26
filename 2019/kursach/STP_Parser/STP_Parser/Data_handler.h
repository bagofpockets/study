#pragma once
#include "CONICAL_SURFACE.h"
#include "TOROIDAL_SURFACE.h"
#include "CYLINDRICAL_SURFACE.h"
#include "SPHERICAL_SURFACE.h"
#include "B_SPLINE_SURFACE.h"
#include "REPRESENTATION_RELATIONSHIP.h"
#include "ADVANCED_BREP_SHAPE_REPRESENTATION.h"
#include "Secondary_funcs.h"
#include "File_handler.h"
#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H
class Data_handler : public File_handler
{
protected:
	std::pair<bool, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>*>* MANIFOLD_SOLID_BREP_map;
	std::pair<bool, std::map<unsigned long long*, CLOSED_SHELL*>*>* CLOSED_SHELL_map;
	std::pair<bool, std::map<unsigned long long*, ADVANCED_FACE*>*>* ADVANCED_FACE_map;

	/*-----Вспомогательные функции-----*/

	Support_class* get_support_object(unsigned long long* ID);

	AXIS2_PLACEMENT_3D* get_AXIS2_PLACEMENT_3D(unsigned long long* ID);

	B_SPLINE_SURFACE* get_B_SPLINE_SURFACE(const std::string* buff);

	REPRESENTATION_RELATIONSHIP* get_REPRESENTATION_RELATIONSHIP(const std::string* buff);

	/*-----Сортировщики-----*/

	std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* MANIFOLD_SOLID_BREP_sorter();

	std::map<unsigned long long*, CLOSED_SHELL*>* CLOSED_SHELL_sorter(std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP = NULL);

	std::map<unsigned long long*, ADVANCED_FACE*>* ADVANCED_FACE_sorter(std::map<unsigned long long*, CLOSED_SHELL*>* input_CLOSED_SHELL = NULL, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP = NULL);

	std::vector<input_data*>* COMPLEX_sorter(const unsigned long long* ID, const std::string SURFACE);

	std::vector<REPRESENTATION_RELATIONSHIP*>* REPRESENTATION_RELATIONSHIP_sorter();

	std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* ADVANCED_BREP_SHAPE_REPRESENTATION_sorter();

public:
	Data_handler(std::string input_file_name);

	virtual ~Data_handler();
};
#endif