#pragma once
#include "ADVANCED_FACE.h"
#include "AXIS2_PLACEMENT_3D.h"
#ifndef CONICAL_SURFACE_H
#define CONICAL_SURFACE_H
class CONICAL_SURFACE : public ADVANCED_FACE
{
	friend class File_handler;

private:
	AXIS2_PLACEMENT_3D* AXIS2_PLACEMENT_3D_data;
	double* smth_d1;
	double* smth_d2;

public:
	CONICAL_SURFACE();
	~CONICAL_SURFACE();
};
#endif
