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
	
	int append(Group &item);
	int append(Lecturer &item);
	int read(std::vector<Group> &list);
	int read(std::vector<Lecturer> &list);

};


