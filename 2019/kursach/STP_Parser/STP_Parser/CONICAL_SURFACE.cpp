#include "CONICAL_SURFACE.h"
CONICAL_SURFACE::CONICAL_SURFACE() : AXIS2_PLACEMENT_3D_data(new AXIS2_PLACEMENT_3D), smth_d1(new double(NULL)), smth_d2(new double(NULL)) {}
CONICAL_SURFACE::~CONICAL_SURFACE()
{
	delete AXIS2_PLACEMENT_3D_data;
	delete smth_d1;
	delete smth_d2;
}