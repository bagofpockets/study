#pragma once
#include "ADVANCED_FACE.h"
#include "AXIS2_PLACEMENT_3D.h"
#ifndef SPHERICAL_SURFACE_H
#define SPHERICAL_SURFACE_H
class SPHERICAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	double* smth_d1;
	double* smth_d2;

public:
	SPHERICAL_SURFACE();
	~SPHERICAL_SURFACE();
};
#endif