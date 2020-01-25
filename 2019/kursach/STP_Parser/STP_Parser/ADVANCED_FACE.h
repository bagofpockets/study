#pragma once
#include "CLOSED_SHELL.h"
#ifndef ADVANCED_FACE_H
#define ADVANCED_FACE_H
class ADVANCED_FACE : public CLOSED_SHELL
{
	friend class Data_handler;

private:
	std::string* smth_str2;

public:
	ADVANCED_FACE();
	virtual ~ADVANCED_FACE();
};
#endif