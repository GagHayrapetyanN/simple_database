#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "config.h"
#include "file_manager.h"
#include "group.h"
#include "lecturer.h"


class QueryParser
{
private:
	std::vector<std::string> query;
	FileManager file;

	std::string upper(const std::string &str);

	void write_query();
	void print_vector();
	int parse_query();

	int add();
	int select();
	int del();

	int get_table_name(std::string & table_name, int &index);
	int check_table_name(const std::string &table_name);
	int get_condition(int index, Maptype &condition);
	int parse_condition(std::string condition,std::string &key, ConStruct &con);

public:
	QueryParser();

	void run();
};



