#pragma once
#include <string>
#include <vector>
#include "Support_class.h"
#ifndef AXIS2_PLACEMENT_3D_H
#define AXIS2_PLACEMENT_3D_H
class AXIS2_PLACEMENT_3D
{
	friend class File_handler;

private:
	std::string* smth_str1;
	std::vector<Support_class*>* associated_ids;

public:
	AXIS2_PLACEMENT_3D();
	~AXIS2_PLACEMENT_3D();
};
#endif