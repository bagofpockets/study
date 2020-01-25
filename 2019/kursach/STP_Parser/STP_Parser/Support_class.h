#pragma once
#include <string>
#ifndef SUPPORT_CLASS_H
#define SUPPORT_CLASS_H
class Support_class //Абстракция CARTESIAN_POINT и DIRECTION
{
	friend class Data_handler;
	friend class Model;

private:
	std::string* smth_str1;
	std::string* type;
	double* x;
	double* y;
	double* z;

public:
	Support_class();
	~Support_class();
};
#endif