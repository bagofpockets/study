#include "ADVANCED_FACE.h"
ADVANCED_FACE::ADVANCED_FACE() : associated_id(new unsigned long long(NULL)), smth_str2(new std::string) {}
ADVANCED_FACE::~ADVANCED_FACE()
{
	delete associated_id;
	delete smth_str2;
}