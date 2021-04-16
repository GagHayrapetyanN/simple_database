#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "config.h"

class Group
{
private:
	char name[20];
	char dep[20];
	unsigned int student_cout;

	int name_filter(ConStruct con);
	int dep_filter(ConStruct con);
	int student_cout_filter(ConStruct con);

	static int check_key(std::string con);

public:
	Group();
	
	void set();
	void print();
	int filter(Maptype condition);

	static int check_condition(Maptype condition);
};
