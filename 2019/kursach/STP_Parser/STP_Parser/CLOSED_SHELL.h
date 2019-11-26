#pragma once
#include "MANIFOLD_SOLID_BREP.h"
#ifndef CLOSED_SHELL_H
#define CLOSED_SHELL_H
class CLOSED_SHELL : public MANIFOLD_SOLID_BREP
{
	friend class Data_handler;
	friend class Model;

protected:
	std::vector<unsigned long long*>* associated_ids;

public:
	CLOSED_SHELL();
	virtual ~CLOSED_SHELL();
};
#endif