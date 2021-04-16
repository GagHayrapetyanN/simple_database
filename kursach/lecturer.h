#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "config.h"


class Lecturer
{
private:
	char first_name[20];
	char last_name[20];
	char dep[20];

	static int check_key(std::string con);

	int first_name_filter(ConStruct con);
	int last_name_filter(ConStruct con);
	int dep_filter(ConStruct con);

public:
	Lecturer();

	void set();
	void print();
	int filter(Maptype condition);

	static int check_condition(Maptype condition);
};

