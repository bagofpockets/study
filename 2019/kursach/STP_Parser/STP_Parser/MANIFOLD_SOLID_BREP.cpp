#include "MANIFOLD_SOLID_BREP.h"
MANIFOLD_SOLID_BREP::MANIFOLD_SOLID_BREP() : smth_str1(new std::string), associated_id(new unsigned long long(NULL)) {}
MANIFOLD_SOLID_BREP::~MANIFOLD_SOLID_BREP()
{
	delete smth_str1;
	delete associated_id;
}