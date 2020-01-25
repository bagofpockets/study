#pragma once
#include "ADVANCED_FACE.h"
#include "AXIS2_PLACEMENT_3D.h"
#ifndef CYLINDRICAL_SURFACE_H
#define CYLINDRICAL_SURFACE_H
class CYLINDRICAL_SURFACE : public ADVANCED_FACE
{
	friend class Data_handler;
	friend class Model;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	std::vector<double*> smth_d;

public:
	CYLINDRICAL_SURFACE();
	~CYLINDRICAL_SURFACE();
};
#endif