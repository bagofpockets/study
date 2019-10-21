#include "AXIS2_PLACEMENT_3D.h"
AXIS2_PLACEMENT_3D::AXIS2_PLACEMENT_3D() : smth_str1(new std::string), associated_ids(new std::vector<Support_class*>) {}
AXIS2_PLACEMENT_3D::~AXIS2_PLACEMENT_3D()
{
	for (size_t i = 0; i < associated_ids->size(); i++)
	{
		delete associated_ids->at(i);
		associated_ids->at(i) = 0;
	}

	delete associated_ids;
	delete smth_str1;
}