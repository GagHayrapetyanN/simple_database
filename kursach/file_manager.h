#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "group.h"
#include "lecturer.h"
#include "config.h"


class FileManager
{
private:
	int get_file_size(std::fstream &f);

public:
	FileManager();
	
	int write(Group &item);
	int write(Lecturer &item);
	int read(std::vector<Group> &list);
	int read(std::vector<Lecturer> &list);
	int empty(std::string file_name);
	int create(std::string file_name);

};


