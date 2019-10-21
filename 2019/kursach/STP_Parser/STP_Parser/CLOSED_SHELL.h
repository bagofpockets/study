#pragma once
#include <string>
#include <vector>
#ifndef CLOSED_SHELL_H
#define CLOSED_SHELL_H
class CLOSED_SHELL
{
	friend class File_handler;

protected:
	std::string* smth_str1;
	std::vector<unsigned long long*>* associated_ids;

public:
	CLOSED_SHELL();
	virtual ~CLOSED_SHELL();
};
#endif