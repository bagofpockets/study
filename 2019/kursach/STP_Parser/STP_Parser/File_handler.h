#pragma once
#include "CONICAL_SURFACE.h"
#include "TOROIDAL_SURFACE.h"
#include "CYLINDRICAL_SURFACE.h"
#include "SPHERICAL_SURFACE.h"
#include "B_SPLINE_SURFACE.h"
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
class File_handler
{
private:
	struct input_data *data_buffer;

	std::ifstream* input_file;
	std::vector<input_data*>* data_vec;

	/*-----Вспомогательные функции-----*/

	std::string delete_parentheses(std::string buff);

	unsigned long long count_sharps(std::string buff);

	std::string get_smth_str_1(std::string buff);

	std::vector<unsigned long long*> get_associated_ids(std::string buff, unsigned long long N);

	std::string get_parentheses_content(std::string buff);

	Support_class* get_support_object(unsigned long long ID);

	AXIS2_PLACEMENT_3D* get_AXIS2_PLACEMENT_3D(unsigned long long ID);

	B_SPLINE_SURFACE* get_B_SPLINE_SURFACE(std::string buff);

	/*-----Сортировщики-----*/

	std::vector<CLOSED_SHELL*> CLOSED_SHELL_sorter();

	std::vector<ADVANCED_FACE*> ADVANCED_FACE_sorter();

	std::vector<input_data*> COMPLEX_sorter(unsigned long long ID);

public:
	File_handler(std::string input_file_name);

	~File_handler();

	void get_data();

	template <class SURFACE>
	std::vector<SURFACE*> SURFACE_sorter();

	std::vector<B_SPLINE_SURFACE*> B_SPLINE_SURFACE_sorter();

	void print_data();
};
#endif