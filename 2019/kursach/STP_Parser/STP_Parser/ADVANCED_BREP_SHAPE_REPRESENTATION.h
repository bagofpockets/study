#pragma once
#include <vector>
#include <string>
#ifndef ADVANCED_BREP_SHAPE_REPRESENTATION_H
#define ADVANCED_BREP_SHAPE_REPRESENTATION_H
class ADVANCED_BREP_SHAPE_REPRESENTATION
{
	friend class File_handler;

private:
	std::string* smth_str1;
	std::vector<unsigned long long*>* associated_ids;
	unsigned long long* CONTEXT_id;

public:
	ADVANCED_BREP_SHAPE_REPRESENTATION();
	~ADVANCED_BREP_SHAPE_REPRESENTATION();
};
#endif