#include "REPRESENTATION_RELATIONSHIP.h"
REPRESENTATION_RELATIONSHIP::REPRESENTATION_RELATIONSHIP() : smth_str(new std::pair<std::string*, std::string*>), assosiated_ids(new std::pair<unsigned long long*, unsigned long long*>), _is_used(new bool(false)) {}
REPRESENTATION_RELATIONSHIP::~REPRESENTATION_RELATIONSHIP()
{
	delete smth_str;
	delete assosiated_ids;
	delete _is_used;
}
bool REPRESENTATION_RELATIONSHIP::is_used(bool is_used)
{
	if (!is_used)
	{
		return *_is_used;
	}
	else
	{
		*_is_used = true;
		return *_is_used;
	}
}