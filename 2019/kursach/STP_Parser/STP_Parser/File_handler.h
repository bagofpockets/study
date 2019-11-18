#pragma once
#include <map>
#include "CONICAL_SURFACE.h"
#include "TOROIDAL_SURFACE.h"
#include "CYLINDRICAL_SURFACE.h"
#include "SPHERICAL_SURFACE.h"
#include "B_SPLINE_SURFACE.h"
#include "REPRESENTATION_RELATIONSHIP.h"
#include "ADVANCED_BREP_SHAPE_REPRESENTATION.h"
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
class File_handler
{
private:
	struct input_data *data_buffer;

	std::pair<bool, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>*>* MANIFOLD_SOLID_BREP_map;
	std::pair<bool, std::map<unsigned long long*, CLOSED_SHELL*>*>* CLOSED_SHELL_map;
	std::pair<bool, std::map<unsigned long long*, ADVANCED_FACE*>*>* ADVANCED_FACE_map;

	std::ifstream* input_file;
	std::vector<input_data*>* data_vec;
	bool initialized = false;

	/*-----Вспомогательные функции-----*/

	Support_class* get_support_object(unsigned long long* ID);

	AXIS2_PLACEMENT_3D* get_AXIS2_PLACEMENT_3D(unsigned long long* ID);

	B_SPLINE_SURFACE* get_B_SPLINE_SURFACE(const std::string* buff);

	REPRESENTATION_RELATIONSHIP* get_REPRESENTATION_RELATIONSHIP(const std::string* buff);

	bool has_B_SPLINE_SURFACE(unsigned long long* ID);

	std::map<unsigned long long, bool>* has_SURFACE(std::string SURFACE = "NONE", std::vector<std::string> SUPPORTED =
		{ "CONICAL_SURFACE",
		"TOROIDAL_SURFACE",
		"CYLINDRICAL_SURFACE",
		"SPHERICAL_SURFACE",
		"B_SPLINE_SURFACE" });

	template <class SURFACE>
	void print_SURFACE(std::vector<SURFACE*> V);

	template <class SURFACE>
	std::vector<SURFACE*>* SURFACE_addition(SURFACE* SURFACE_buffer);

	/*-----Сортировщики-----*/

	std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* MANIFOLD_SOLID_BREP_sorter();

	std::map<unsigned long long*, CLOSED_SHELL*>* CLOSED_SHELL_sorter(std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP = NULL);

	std::map<unsigned long long*, ADVANCED_FACE*>* ADVANCED_FACE_sorter(std::map<unsigned long long*, CLOSED_SHELL*>* input_CLOSED_SHELL = NULL, std::map<unsigned long long*, MANIFOLD_SOLID_BREP*>* input_MANIFOLD_SOLID_BREP = NULL);

	std::vector<input_data*>* COMPLEX_sorter(const unsigned long long* ID, const std::string SURFACE);

	std::vector<REPRESENTATION_RELATIONSHIP*>* REPRESENTATION_RELATIONSHIP_sorter();

	std::map<unsigned long long*, ADVANCED_BREP_SHAPE_REPRESENTATION*>* ADVANCED_BREP_SHAPE_REPRESENTATION_sorter();

public:
	File_handler(std::string input_file_name);

	~File_handler();

	void get_data();

	template <class SURFACE>
	std::vector<SURFACE*>* SURFACE_sorter();

	std::map<unsigned long long*, B_SPLINE_SURFACE*>* B_SPLINE_SURFACE_sorter();

	void print_data(std::string CLASS);
};
#endif