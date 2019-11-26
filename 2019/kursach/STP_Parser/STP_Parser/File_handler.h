#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <map>
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
class File_handler
{
protected:
	struct input_data
	{
		std::map<unsigned long long, std::string> data;
		std::string type;
	};
	std::ifstream* input_file;
	std::vector<input_data*>* data_vec;
	bool* initialized;

public:
	File_handler(std::string input_file_name);

	virtual ~File_handler();

	void get_data();
};
#endif