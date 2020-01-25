#include "TOROIDAL_SURFACE.h"
TOROIDAL_SURFACE::TOROIDAL_SURFACE() : AXIS2_PLACEMENT_3D_data(new AXIS2_PLACEMENT_3D) {}
TOROIDAL_SURFACE::~TOROIDAL_SURFACE()
{
	delete AXIS2_PLACEMENT_3D_data;
	for (auto i = smth_d.begin(); i != smth_d.end(); ++i)
	{
		delete *i;
		*i = 0;
	}
}