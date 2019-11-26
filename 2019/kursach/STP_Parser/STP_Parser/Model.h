#pragma once
#include "Data_handler.h"
#ifndef MODEL_H
#define MODEL_H
class Model : public Data_handler
{
private:
	std::map<unsigned long long*, CONICAL_SURFACE*>* CONICAL_SURFACE_map;
	std::map<unsigned long long*, SPHERICAL_SURFACE*>* SPHERICAL_SURFACE_map;
	std::map<unsigned long long*, CYLINDRICAL_SURFACE*>* CYLINDRICAL_SURFACE_map;
	std::map<unsigned long long*, TOROIDAL_SURFACE*>* TOROIDAL_SURFACE_map;
	std::map<unsigned long long*, B_SPLINE_SURFACE*>* B_SPLINE_SURFACE_map;

	bool has_B_SPLINE_SURFACE(unsigned long long* ID);

	std::map<unsigned long long, bool>* has_SURFACE(std::string SURFACE = "NONE", std::vector<std::string> SUPPORTED =
		{ "CONICAL_SURFACE",
		"TOROIDAL_SURFACE",
		"CYLINDRICAL_SURFACE",
		"SPHERICAL_SURFACE",
		"B_SPLINE_SURFACE" });

	template <class SURFACE>
	std::map<unsigned long long*, SURFACE*>* additional_SURFACEs(unsigned long long* self_id, SURFACE* SURFACE_buffer);

	template <class SURFACE>
	std::map<unsigned long long*, SURFACE*>* SURFACE_sorter();

	std::map<unsigned long long*, B_SPLINE_SURFACE*>* B_SPLINE_SURFACE_sorter();

	template <class SURFACE>
	void print_SURFACE(std::map<unsigned long long*, SURFACE*> V);

public:
	Model(std::string input_file_name);

	~Model();

	void construct();

	void print_data(std::string CLASS);
};
#endif