#include "TOROIDAL_SURFACE.h"
TOROIDAL_SURFACE::TOROIDAL_SURFACE() : AXIS2_PLACEMENT_3D_data(new AXIS2_PLACEMENT_3D), smth_d1(new double(NULL)), smth_d2(new double(NULL)) {}
TOROIDAL_SURFACE::~TOROIDAL_SURFACE()
{
	delete AXIS2_PLACEMENT_3D_data;
	delete smth_d1;
	delete smth_d2;
}