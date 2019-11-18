#pragma once
#include <string>
#include <vector>
#ifndef MANIFOLD_SOLID_BREP_H
#define MANIFOLD_SOLID_BREP_H
class MANIFOLD_SOLID_BREP
{
	friend class File_handler;

protected:
	std::string* smth_str1;
	unsigned long long* associated_id;

public:
	MANIFOLD_SOLID_BREP();
	virtual ~MANIFOLD_SOLID_BREP();
};
#endif