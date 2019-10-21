#include "CLOSED_SHELL.h"
CLOSED_SHELL::CLOSED_SHELL() : associated_ids(new std::vector<unsigned long long*>), smth_str1(new std::string) {}
CLOSED_SHELL::~CLOSED_SHELL()
{
	for (size_t i = 0; i < associated_ids->size(); i++)
	{
		delete associated_ids->at(i);
		associated_ids->at(i) = 0;
	}

	delete associated_ids;
	delete smth_str1;
}