#include "Support_class.h"
Support_class::Support_class() : smth_str1(new std::string), type(new std::string), x(new double(NULL)), y(new double(NULL)), z(new double(NULL)) {}
Support_class::~Support_class()
{
	delete smth_str1;
	delete type;
	delete x;
	delete y;
	delete z;
}