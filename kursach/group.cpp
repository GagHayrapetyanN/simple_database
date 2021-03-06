#include "group.h"


Group::Group()
{
}

int Group::check_key(std::string con)
{
	int error = 0;
	std::string members[3] = { "name", "dep", "student_cout" };

	for (int i = 0; i < 3; i++)
	{
		error |= (members[i] == con);
	}

	return !(error);
}

int Group::check_condition(Maptype condition)
{
	std::string key;
	int error = 0;

	for (Maptype::iterator it = condition.begin(); it != condition.end(); ++it) {
		key = it->first;

		if (check_key(key))
		{
			error++;
			std::cout << "There is no " << key << " column in the table\n";
		}
	}

	return error;
}

void Group::set()
{
	std::cout << "Enter name: ";
	std::cin >> this->name;
	std::cout << "Enter departament: ";
	std::cin >> this->dep;
	std::cout << "Enter student count: ";
	std::cin >> this->student_cout;
}

void Group::print()
{
	std::cout << this->name << " " << this->dep << " " << this->student_cout<<"\n";
}

int Group::filter(Maptype condition)
{
	std::string key;
	ConStruct con;
	int state = 1;
	std::map<std::string, int (Group::*)(ConStruct)> filtr_map = {
		{"name", &Group::name_filter},
		{"dep", &Group::dep_filter},
		{"student_cout", &Group::student_cout_filter}
	};

	for (Maptype::iterator it = condition.begin(); it != condition.end(); ++it) {
		key = it->first;
		con = condition[key];
		
		state &= (this->*filtr_map[key])(con);
	}
	
	return state;
}

int Group::name_filter(ConStruct con)
{
	const char *value_tmp = con.value.c_str();

	if (con.syumbol == "=")
	{
		return !strcmp(this->name, value_tmp);
	}
	else
	{
		return strcmp(this->name, value_tmp);
	}
}

int Group::dep_filter(ConStruct con)
{
	const char *value_tmp = con.value.c_str();

	if (con.syumbol == "=")
	{
		return !strcmp(this->dep, value_tmp);
	}
	else
	{
		return strcmp(this->dep, value_tmp);
	}
	
}

int Group::student_cout_filter(ConStruct con)
{
	if (con.syumbol == "=")
	{
		return std::to_string(this->student_cout) == con.value;
	}
	else
	{
		return std::to_string(this->student_cout) != con.value;
	}
}

