#include "REPRESENTATION_RELATIONSHIP.h"
REPRESENTATION_RELATIONSHIP::REPRESENTATION_RELATIONSHIP() : smth_str(new std::pair<std::string*, std::string*>), assosiated_ids(new std::pair<unsigned long long*, unsigned long long*>) {}
REPRESENTATION_RELATIONSHIP::~REPRESENTATION_RELATIONSHIP()
{
	delete smth_str;
	delete assosiated_ids;
}