#include "ADVANCED_FACE.h"
ADVANCED_FACE::ADVANCED_FACE() : smth_str2(new std::string) {}
ADVANCED_FACE::~ADVANCED_FACE()
{
	delete smth_str2;
}