#include "lecturer.h"

Lecturer::Lecturer()
{
	
}

int Lecturer::check_key(std::string con)
{
	int error=0;
	std::string members[3] = { "first_name", "last_name", "dep" };

	for (int i = 0; i < 3; i++)
	{
		error |= (members[i] == con);
	}
	
	return !(error);
}

int Lecturer::check_condition(Maptype condition)
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

void Lecturer::set()
{
	std::cout << "Enter first name: ";
	std::cin >> this->first_name;
	std::cout << "Enter last name: ";
	std::cin >> this->last_name;
	std::cout << "Enter departament: ";
	std::cin >> this->dep;
}

void Lecturer::print()
{
	std::cout << this->first_name << " " << this->last_name << " " << this->dep << std::endl;
}

int Lecturer::filter(Maptype condition)
{
	std::string key, value;
	ConStruct con;
	int state = 1;
	std::map<std::string, int (Lecturer::*)(ConStruct)> filtr_map = {
		{"first_name", &Lecturer::first_name_filter},
		{"last_name", &Lecturer::last_name_filter},
		{"dep", &Lecturer::dep_filter}
	};

	for (Maptype::iterator it = condition.begin(); it != condition.end(); ++it) {
		key = it->first;
		con = condition[key];

		state &= (this->*filtr_map[key])(con);
	}

	return state;
}

int Lecturer::first_name_filter(ConStruct con)
{
	const char *value_tmp = con.value.c_str();

	return !strcmp(this->first_name, value_tmp);
}

int Lecturer::last_name_filter(ConStruct con)
{
	const char *value_tmp = con.value.c_str();

	return !strcmp(this->last_name, value_tmp);
}

int Lecturer::dep_filter(ConStruct con)
{
	const char *value_tmp = con.value.c_str();

	return !strcmp(this->dep, value_tmp);
}