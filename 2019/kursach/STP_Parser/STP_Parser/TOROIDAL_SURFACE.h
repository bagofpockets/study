#pragma once
#include "ADVANCED_FACE.h"
#include "AXIS2_PLACEMENT_3D.h"
#ifndef TOROIDAL_SURFACE_H
#define TOROIDAL_SURFACE_H
class TOROIDAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	double* smth_d1;
	double* smth_d2;

public:
	TOROIDAL_SURFACE();
	~TOROIDAL_SURFACE();
};
#endif