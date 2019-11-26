#pragma once
#include "ADVANCED_FACE.h"
#include "Support_class.h"
#ifndef B_SPLINE_SURFACE_H
#define B_SPLINE_SURFACE_H
class B_SPLINE_SURFACE : public ADVANCED_FACE
{
	friend class Data_handler;
	friend class Model;

private:
	int* smth_int1;
	int* smth_int2;
	std::vector<std::vector<Support_class*>*>* associated_support_ids;
	std::string* smth_str2;
	std::string* smth_str3;
	std::string* smth_str4;
	std::string* smth_str5;

public:
	B_SPLINE_SURFACE();
	~B_SPLINE_SURFACE();
};
#endif