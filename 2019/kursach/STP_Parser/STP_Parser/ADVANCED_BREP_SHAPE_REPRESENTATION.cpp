#include "ADVANCED_BREP_SHAPE_REPRESENTATION.h"
ADVANCED_BREP_SHAPE_REPRESENTATION::ADVANCED_BREP_SHAPE_REPRESENTATION() : smth_str1(new std::string), associated_ids(new std::vector<unsigned long long*>), CONTEXT_id(new unsigned long long(NULL)) {}
ADVANCED_BREP_SHAPE_REPRESENTATION::~ADVANCED_BREP_SHAPE_REPRESENTATION()
{
	for (size_t i = 0; i < associated_ids->size(); i++)
	{
		delete associated_ids->at(i);
		associated_ids->at(i) = 0;
	}

	delete associated_ids;
	delete smth_str1;
	delete CONTEXT_id;
}