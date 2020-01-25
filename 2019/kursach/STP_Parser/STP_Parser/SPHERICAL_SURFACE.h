#pragma once
#include "ADVANCED_FACE.h"
#include "AXIS2_PLACEMENT_3D.h"
#ifndef SPHERICAL_SURFACE_H
#define SPHERICAL_SURFACE_H
class SPHERICAL_SURFACE : public ADVANCED_FACE
{
	friend class Data_handler;
	friend class Model;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	std::vector<double*> smth_d;

public:
	SPHERICAL_SURFACE();
	~SPHERICAL_SURFACE();
};
#endif