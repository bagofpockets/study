#pragma once
#include <string>
#ifndef REPRESENTATION_RELATIONSHIP_H
#define REPRESENTATION_RELATIONSHIP_H
class REPRESENTATION_RELATIONSHIP
{
	friend class File_handler;
private:
	std::pair<std::string*, std::string*>* smth_str;
	std::pair<unsigned long long*, unsigned long long*>* assosiated_ids;

public:
	REPRESENTATION_RELATIONSHIP();
	~REPRESENTATION_RELATIONSHIP();
};
#endif