#pragma once
#include <vector>
#include <string>
#ifndef SECONDARY_FUNCS_H
#define SECONDARY_FUNCS_H
std::string* delete_parentheses(std::string* buff);

unsigned long long count_sharps(std::string* buff);

std::string get_smth_str_1(const std::string* buff);

std::vector<unsigned long long*>* get_associated_ids(std::string* buff, unsigned long long* N);

std::string get_parentheses_content(const std::string* buff);
#endif