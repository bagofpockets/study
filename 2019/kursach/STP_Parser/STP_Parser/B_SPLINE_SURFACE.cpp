#include "B_SPLINE_SURFACE.h"
B_SPLINE_SURFACE::B_SPLINE_SURFACE() : smth_int1(new int(NULL)), smth_int2(new int(NULL)), associated_support_ids(new std::vector<std::vector<Support_class*>*>), smth_str2(new std::string), smth_str3(new std::string), smth_str4(new std::string), smth_str5(new std::string) {}
B_SPLINE_SURFACE::~B_SPLINE_SURFACE()
{
	delete smth_int1;
	delete smth_int2;
	for (size_t i = 0; i < associated_support_ids->size(); i++)
	{
		for (size_t j = 0; j < associated_support_ids->at(i)->size(); j++)
		{
			delete associated_ids->at(j);
			associated_ids->at(j) = 0;
		}
		delete associated_ids->at(i);
		associated_ids->at(i) = 0;
	}
	delete associated_support_ids;
	delete smth_str2;
	delete smth_str3;
	delete smth_str4;
	delete smth_str5;
}