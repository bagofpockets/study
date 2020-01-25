#pragma once
#include <string>
#ifndef REPRESENTATION_RELATIONSHIP_H
#define REPRESENTATION_RELATIONSHIP_H
class REPRESENTATION_RELATIONSHIP
{
	friend class Data_handler;
	friend class Model;

private:
	std::pair<std::string*, std::string*>* smth_str;
	std::pair<unsigned long long*, unsigned long long*>* assosiated_ids;
	bool* _is_used;

public:
	REPRESENTATION_RELATIONSHIP();
	~REPRESENTATION_RELATIONSHIP();

	bool is_used(bool is_used = false);
};
#endif